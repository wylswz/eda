#include "eda/config/config.hpp"
#include<iostream>
#include<yaml.h>
using namespace std;


namespace eda_config {
    string Config::EtcdEPs() {
        return "http://127.0.0.1:2380";
    }

    Config::Config(): etcd_eps() {

    }

    Config::~Config() = default;

}