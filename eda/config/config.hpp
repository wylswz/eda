#pragma once
#include <stdlib.h>
#include <string>

#define ENV_ETCD_EPS "ETCD_EPS"

using namespace std;

namespace eda_config
{
    class Config
    {
    private:
        string etcd_eps;
    public:
        string EtcdEPs();
        Config();
        ~Config();
    };
    
}

