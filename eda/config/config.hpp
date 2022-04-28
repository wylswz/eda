#ifndef EDA_CONFIG_H
#define EDA_CONFIG_H

#include "eda/core/std.h"
#include "eda/core/config_parser.h"

#define ENV_ETCD_EPS "ETCD_EPS"

using namespace std;

namespace eda_config
{

    vector<string> extract_etcd_eps(eda_core::Y_Object & obj);

    class Config
    {
    private:
        vector<string> etcd_eps;
        bool initialized = false;

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
