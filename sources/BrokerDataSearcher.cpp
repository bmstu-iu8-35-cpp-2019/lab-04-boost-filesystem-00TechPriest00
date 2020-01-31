// Copyright 2019 Fedorov james.sayfer2015@yandex.ru

#include "BrokerDataSearcher.hpp"

void BrokerDataSearcher::searchBrokerData() {
    search(searchPath);

    for (const Account &account : accounts) {
        std::cout << "broker:" << account.broker
                  << " account:" << account.id
                  << " files:" << account.docsCount
                  << " lastdate:" << account.lastDate
                  << std::endl;
    }

    accounts.clear();
}

void BrokerDataSearcher::search(const bf::path &path) {
    for (const auto &entry : bf::directory_iterator{path}) {
        bf::path canon = bf::canonical(entry);

        if (bf::is_directory(canon)) {
            search(canon);
            continue;
        }

        if (bf::is_regular_file(canon)) {
            std::string filename = canon.filename().c_str();

            if (!std::regex_match(filename, pattern)) {
                continue;
            }

            std::string broker = canon.parent_path().filename().c_str();

            std::smatch m;
            std::regex_search(filename, m, regexAccount);
            std::string account_id = m[1];
            std::regex_search(filename, m, regexDate);
            std::string date = m[1];

            std::cout << broker << " " << filename << std::endl;
            onBalanceFile(broker, account_id, date);
        }
    }
}

void BrokerDataSearcher::onBalanceFile(const std::string &broker,
                                       const std::string &account_id,
                                       const std::string &date) {
    auto lambda = [&account_id](const Account &it) {
        return it.id == account_id;
    };

    auto account = std::find_if(accounts.begin(),
                                accounts.end(),
                                lambda);

    // Account already exists
    if (account != accounts.end()) {
        ++(account->docsCount);

        if (date > account->lastDate) {
            account->lastDate = date;
        }

        return;
    }

    accounts.push_back({account_id, date, broker, 1});
}
