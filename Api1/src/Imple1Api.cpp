//
// Created by xzh on 2020/8/1.
//

#include <JSON.h>
#include "Imple1Api.h"

bool Imple1Api::addParameter(Parameter parameter) {
    parameters.push_back(parameter);
    return true;
}

Result Imple1Api::getParameters() {
    Result result;
    result.parameters = parameters;
//    return puppy::common::JSON::toJSONString(result);
    return result;
}

Parameter Imple1Api::getParameter(QueryPara query) {
    for (auto &p :parameters) {
        if (p.name == query.name) {
            return p;
//            return puppy::common::JSON::toJSONString(p);
        }
    }
    throw "error name ";
}

Parameter::Parameter() {
    name = "NAME1";
    age = 111;
}

Result::Result() {

}
