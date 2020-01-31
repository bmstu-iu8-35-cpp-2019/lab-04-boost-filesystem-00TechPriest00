// Copyright 2019 Fedorov james.sayfer2015@yandex.ru

#ifndef INCLUDE_ACCOUNT_HPP_
#define INCLUDE_ACCOUNT_HPP_

#include <string>

struct Account {
    std::string id;
    std::string lastDate;
    std::string broker;
    int docsCount;
};

#endif //INCLUDE_ACCOUNT_HPP_
