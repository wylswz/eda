#include "eda/core/config_parser.h"
#include "eda/core/functools.hpp"
#include "eda/config/config.hpp"
#include "eda/core/std.h"
#include <functional>

#define CONFIG_PATH "/etc/xmbsmdsj/eda/config.yaml"

using namespace std;

namespace eda_config
{

    string Config::EtcdEPs()
    {
        return eda_core::foldl(this->etcd_eps, eda_core::Folders<string>::plus);
    }

    void Config::init()
    {
        eda_core::Y_Object config = eda_core::parse_yaml(CONFIG_PATH);
    }

    Config::Config() noexcept: etcd_eps{}
    {
    };

    Config::~Config() = default;

}