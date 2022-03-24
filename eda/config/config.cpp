#include "eda/config/config.hpp"
#include<iostream>
using namespace std;


namespace eda {
    string Config::EtcdEPs() {
        return "http://127.0.0.1:2380";
    }

    Config::Config(): etcd_eps() {

    }

    Config::~Config() = default;

}