#include "eda/etcd/etcd_op.hpp"
#include "eda/core/errors.hpp"
#include "eda/core/sink.hpp"
#include "eda/core/std.h"

using namespace std;

namespace eda {
    ETCD_Op::ETCD_Op(string const &etcd_ep):
    etcd_ep{etcd_ep},
    client (etcd_ep, "pick_first")
    {
        cout<<"Using etcd: "<<eda_config::Config().EtcdEPs()<<endl;    
    }

    ETCD_Op::ETCD_Op(ETCD_Op const& that): 
    etcd_ep{that.etcd_ep},
    client {etcd_ep, "pick_first"} {

    }

    ETCD_Op::~ETCD_Op() = default;

    vector<string> ETCD_Op::list(string const & prefix) {
        
        etcd::Response r  = this->client.ls(prefix).get();
        string s = r.value().as_string();
        
        cout<<r.value().as_string()<<endl;
        if (!r.is_ok()) {
            throw eda_core::EDA_Exception(ERR_ETCD_ERR, r.error_message());
        }
        return r.keys();
    }
}