#include "Imple1Api.h"

RTTR_PLUGIN_REGISTRATION {
    rttr::registration::class_<Parameter>("Parameter")
            .

                    constructor<>()(
                    rttr::policy::ctor::as_object
            )

            .property("age", &Parameter::age)
            .property("name", &Parameter::name);

    rttr::registration::class_<Result>("Result")
            .

                    constructor<>()(
                    rttr::policy::ctor::as_object
            )

            .property("parameters", &Result::parameters);

    rttr::registration::class_<QueryPara>("QueryPara")
            .

                    constructor<>()(
                    rttr::policy::ctor::as_object
            )

            .property("name", &QueryPara::name);



    rttr::registration::class_<Imple1Api>("Imple1Api")
            (
                    rttr::metadata("API_VENDOR", "Imple1Api"),
                    rttr::metadata("API_VERSION", "v1"),
                    rttr::metadata("API_TYPE", "RESTAPI")
            )
            .

                    constructor<>()

//            .method("addPara",
//                    rttr::select_overload<std::string(Parameter)>(&Imple1Api::addParameter)
//            ).
//            method("lsParas",
//                     rttr::select_overload<std::string()>(&Imple1Api::getParameters)
//            ).
//    method("getPara",
//           rttr::select_overload<std::string(std::string)>(&Imple1Api::getParameter)
//    );
            .method("addPara",
                    rttr::select_overload<bool(Parameter)>(&Imple1Api::addParameter)
            ).
                    method("lsParas",
                           rttr::select_overload<Result()>(&Imple1Api::getParameters)
            ).
                    method("getPara",
                           rttr::select_overload<Parameter(QueryPara)>(&Imple1Api::getParameter)
            );
};