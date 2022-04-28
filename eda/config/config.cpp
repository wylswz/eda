#include "eda/core/config_parser.h"
#include "eda/core/functools.hpp"
#include "eda/config/config.hpp"
#include "eda/core/std.h"
#include "eda/core/errors.hpp"
#include <functional>

#define CONFIG_PATH "/etc/xmbsmdsj/eda/config.yaml"
#define ETCD_DEFAULT_EP "http://127.0.0.1:2380"

#define CONFIG_KEY_ETCD_EPS "etcd-endpoints"

using namespace std;

namespace eda_config
{


    vector<string> extract_etcd_eps(eda_core::Y_Object & obj) {
        eda_core::Y_Object seq = *eda_core::Y_Map{obj}.get(CONFIG_KEY_ETCD_EPS);
        function<string(shared_ptr<eda_core::Y_Object> const &) > mapper = [](shared_ptr<eda_core::Y_Object> const& ptr ) {return (*ptr).token;};
        return eda_core::map_to<shared_ptr<eda_core::Y_Object>, string>(seq.seq, mapper);
    }

    string Config::EtcdEPs()
    {
        return eda_core::foldl(this->etcd_eps, eda_core::Folders<string>::plus);
    }


    void Config::init()
    {
        try {
            eda_core::Y_Object config = eda_core::parse_yaml(CONFIG_PATH);

        } catch (eda_core::EDA_Exception e) {
            if (e.is(ERR_FILE_NOT_EXISTS)) {
                // Config file is not found, using default endpoint
                this->etcd_eps = vector<string>{ETCD_DEFAULT_EP};
            } else {
                throw e;
            }
        }
    }

    Config::Config() noexcept: etcd_eps{}
    {
    };

    Config::~Config() = default;

}