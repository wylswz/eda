#include<etcd/Client.hpp>
#include "eda/config/config.hpp"
#include<vector>

namespace eda {
    extern Config config;

    class ETCD_Op {
    private:
        etcd::Client* c;

    public:
        ETCD_Op();
        ~ETCD_Op();
    };

    ETCD_Op::ETCD_Op() {
        etcd::Client c(config.EtcdEPs());
        this->c = &c;
    }

    ETCD_Op::~ETCD_Op() {
        delete this->c;
    }

}