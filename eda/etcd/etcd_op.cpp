#include "eda/etcd/etcd_op.hpp"
#include "eda/core/errors.hpp"
#include "eda/core/sink.hpp"
#include "eda/core/std.h"

using namespace std;

namespace eda {
    ETCD_Op::ETCD_Op():
    client (eda_config::Config().EtcdEPs(), "pick_first")
    {    
    }

    ETCD_Op::~ETCD_Op() {
    
    };

    vector<string> ETCD_Op::list(string const & prefix) {
        
        etcd::Response r  = this->client.ls(prefix).get();
        string s = r.value().as_string();
        
        cout<<r.value().as_string()<<endl;
        if (!r.is_ok()) {
            throw EDA_Exception(ERR_ETCD_ERR, r.error_message());
        }
        return r.keys();
    }
}