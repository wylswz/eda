#include <stdlib.h>
#include <string>

#define ENV_ETCD_EPS "ETCD_EPS"

using namespace std;

namespace eda
{
    class Config
    {
    private:
        string etcd_eps;
    public:
        Config(/* args */);
        ~Config();
        string EtcdEPs();
    };
    
    Config::Config(/* args */)
    {
       this->etcd_eps = "";
    }
    
    Config::~Config()
    {
    }

    string Config::EtcdEPs() {
        if (this->etcd_eps.length() == 0) {
            this->etcd_eps = getenv(ENV_ETCD_EPS);
        }
        return this->etcd_eps;
    }
    
    extern Config config();
}
