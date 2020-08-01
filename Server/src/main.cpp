#include <JSON.h>
#include "Context.h"
#include "httplib.h"

void initWebServer(std::vector<rttr::type> types, httplib::Server &svr) {
    for (int i = 0; i < types.size(); ++i) {
        if (types[i].get_metadata("API_TYPE") == "RESTAPI") {
            std::string version = types[i].get_metadata("API_VERSION").to_string();
            auto obj2 = types[i].create();
            auto ms = types[i].get_methods();
            for (auto m:ms) {
                std::string methodName = m.get_name().data();
                std::string url = "/" + version + "/" + methodName;
                LOG(INFO) << url;
                rttr::array_range<rttr::parameter_info> infos = m.get_parameter_infos();
                if (infos.size() > 1) {
                    LOG(ERROR) << "web api only support one json object";
                    continue;
                }
                svr.Post(url.data(), [infos, obj2, m](const httplib::Request &req, httplib::Response &res) {
                    if (infos.size() == 1) {
                        rttr::variant var = infos.begin()->get_type().create();
                        std::string text = req.body;
                        puppy::common::JSON::parseJSON(text, var);//请参照官方代码的jsondemo
                        std::vector<rttr::argument> args{var};
                        rttr::variant result = m.invoke_variadic(obj2, args);
                        //请参照官方代码的转为json的demo
                        res.set_content(puppy::common::JSON::toJSONString(result), "application/json");
                    } else {
                        rttr::variant result = m.invoke(obj2);
                        std::string text = puppy::common::JSON::toJSONString(result);
                        LOG(INFO) << " response " << text;
                        res.set_content(text, "application/json");
                    }

                });
            }
        }
    }
}

/**
 * http://192.168.0.107:8080/v1/addPara
 * Content-Type application/json
 * {
 * "name":"test1",
 * "age":123
 * }
 *
 *
 * @return
 */
int main() {
    httplib::Server svr;
    Context context;
    context.loadLibrary(
            "../lib/libHttpApi1.so");
//    context.loadLibrary(
//            "libImpl2API.so");

    initWebServer(context.getAllType(), svr);

    svr.set_error_handler([](const httplib::Request & /*req*/, httplib::Response &res) {
        const char *fmt = "<p>Error Status: <span style='color:red;'>%d</span></p>";
        char buf[BUFSIZ];
        snprintf(buf, sizeof(buf), fmt, res.status);
        res.set_content(buf, "text/html");
    });

    svr.listen("0.0.0.0", 8080);

    return 0;
}