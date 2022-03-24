#include "eda/etcd/etcd_op.hpp"
#include "eda/core/errors.hpp"
#include "eda/core/sink.hpp"

namespace eda {
    ETCD_Op::ETCD_Op():
    client {Config().EtcdEPs()}
    {
    }

    ETCD_Op::~ETCD_Op() {
    
    };

    vector<string> ETCD_Op::list(string const & prefix) {
        pplx::task<etcd::Response> t = this ->client.ls(prefix);
        etcd::Response r = t.get();
        if (!r.is_ok()) {
            throw EDA_Exception(ERR_ETCD_ERR, r.error_message());
        }
        return r.keys();
    }
}