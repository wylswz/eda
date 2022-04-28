#ifndef EDA_CONFIG_H
#define EDA_CONFIG_H

#include "eda/core/std.h"

#define ENV_ETCD_EPS "ETCD_EPS"

using namespace std;

namespace eda_config
{
    class Config
    {
    private:
        vector<string> etcd_eps;

    public:
        /**
         * @brief etcd endpoints separated by comma
         *
         * @return string
         */
        string EtcdEPs();
        void init();
        Config() noexcept;
        ~Config();
    };

}

#endif
