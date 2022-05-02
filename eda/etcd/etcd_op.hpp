#ifndef ETCD_OP_H
#define ETCD_OP_H

#include "eda/config/config.hpp"
#include<vector>
#include<etcd/Client.hpp>

namespace eda {
    class ETCD_Op {
    private:
        etcd::Client client;
        string etcd_ep;

    public:
        ETCD_Op(string const & etcd_ep);
        ETCD_Op(ETCD_Op const & that);
        ~ETCD_Op();
        /**
         * @brief List all keys with prefix
         * 
         * @param key 
         * @return vector<string> 
         */
        vector<string> list(string const & prefix);
    };

}

#endif