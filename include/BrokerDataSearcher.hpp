// Copyright 2019 Fedorov james.sayfer2015@yandex.ru

#ifndef INCLUDE_BROKERDATASEARCHER_HPP_
#define INCLUDE_BROKERDATASEARCHER_HPP_

#include <string>
#include <iostream>
#include <regex>
#include <boost/filesystem.hpp>
#include <utility>
#include <vector>
#include "Account.hpp"

namespace bf = boost::filesystem;


class BrokerDataSearcher {
public:
    explicit BrokerDataSearcher(bf::path path) : searchPath(std::move(path)) {}

    void searchBrokerData();

private:
    void search(const bf::path &path);

    void onBalanceFile(const std::string &broker, const std::string &account_id,
                       const std::string &date);

    std::regex pattern = std::regex("balance_[0-9]{8}_[0-9]{8}\\.txt");
    std::regex regexAccount = std::regex("balance_([0-9]{8})_[0-9]{8}\\.txt");
    std::regex regexDate = std::regex("balance_[0-9]{8}_([0-9]{8})\\.txt");

    std::vector<Account> accounts;
    const bf::path searchPath;
};


#endif // INCLUDE_BROKERDATASEARCHER_HPP_
