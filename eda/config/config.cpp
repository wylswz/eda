#include "eda/config/config.hpp"

namespace eda {
    string Config::EtcdEPs() {
        if (this->etcd_eps.length() == 0) {
            this->etcd_eps = getenv(ENV_ETCD_EPS);
        }
        return this->etcd_eps;
    }

    Config::Config(): etcd_eps() {

    }

    Config::~Config() = default;

}