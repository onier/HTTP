//
// Created by xzh on 2020/8/1.
//

#ifndef PUPPY_CONTEXT_H
#define PUPPY_CONTEXT_H

#include <string>
#include <vector>
#include <rttr/registration.h>
#include <rttr/library.h>
#include <map>
#include "glog/logging.h"

class Context {
public:
    Context() {};

    template<typename T>
    const std::shared_ptr<T> create(std::string vendor) {
        for (auto pair:_typeMap) {
            for (auto t: pair.second) {
                if (t.is_derived_from<T>()) {
                    if (t.get_metadata("API_VENDOR").to_string() == vendor) {
                        const rttr::variant &var = t.create();
                        return var.get_value<std::shared_ptr<T>>();
                    }
                }
            }
        }
        throw std::invalid_argument("can not find api for " + vendor);
    };

    void loadLibrary(std::string libPath) {
        std::shared_ptr<rttr::library> lib = std::shared_ptr<rttr::library>(new rttr::library(libPath));

        if (!lib->load()) {
            LOG(ERROR) << "load library error " << lib->get_error_string();
        }
        {
            std::vector<rttr::type> temp;
            for (auto t : lib->get_types()) {
                if (t.is_class() && !t.is_wrapper()) {
                    LOG(INFO) << "find class " << t.get_name();
                    temp.push_back(t);
                    _types.push_back(t);
                }
            }
            _typeMap.insert({lib, temp});
        }
    };

    std::vector<rttr::type> getAllType() {
        return _types;
    }

private:
    std::map<std::shared_ptr<rttr::library>, std::vector<rttr::type>> _typeMap;
    std::vector<rttr::type> _types;
};

#endif //PUPPY_CONTEXT_H
