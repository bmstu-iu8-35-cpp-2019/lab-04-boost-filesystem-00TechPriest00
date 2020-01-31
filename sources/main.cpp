// Copyright 2019 Fedorov james.sayfer2015@yandex.ru

#include <BrokerDataSearcher.hpp>

int main(int argc, const char *argv[]) {
    bf::path path = bf::current_path();

    if (argc == 2) {
        path = bf::path(argv[1]);
    }

    BrokerDataSearcher(path).searchBrokerData();
    return 0;
}
