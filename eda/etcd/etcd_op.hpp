#ifndef ETCD_OP_H
#define ETCD_OP_H

#include "eda/config/config.hpp"
#include<vector>
#include<etcd/Client.hpp>

namespace eda {
    class ETCD_Op {
    private:
        etcd::Client client;

    public:
        ETCD_Op();
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