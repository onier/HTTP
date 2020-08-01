//
// Created by xzh on 2020/8/1.
//

#ifndef PUPPY_IMPLE1API_H
#define PUPPY_IMPLE1API_H

#include <string>
#include <rttr/registration.h>
#include <ostream>

struct Parameter {
    std::string name;
    int age;

    Parameter();

    friend std::ostream &operator<<(std::ostream &os, const Parameter &parameter) {
        os << "name: " << parameter.name << " age: " << parameter.age;
        return os;
    }

RTTR_ENABLE();
};

struct Result {
    std::vector<Parameter> parameters;

    Result();

RTTR_ENABLE();
};

struct QueryPara {
    std::string name;

RTTR_ENABLE();
};

class Imple1Api {
public:
    bool addParameter(Parameter parameter);

//    std::string getParameters();
    Result getParameters();

//    std::string getParameter(std::string name);
    Parameter getParameter(QueryPara query);

    std::vector<Parameter> parameters;
};


#endif //PUPPY_IMPLE1API_H
