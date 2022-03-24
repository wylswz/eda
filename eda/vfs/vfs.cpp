#include "eda/vfs/vfs.hpp"
#include "eda/core/errors.hpp"

using namespace std;

namespace eda
{
    VFS::VFS():
    etcd_op() {
    }

    VFS::~VFS() = default;

    string VFS::cd(string const & dir) {
        throw (ERR_NOT_IMPLEMENTED);
    }

    string VFS::pwd() {
        throw (ERR_NOT_IMPLEMENTED);
    }

    vector<string> VFS::ls() {
        return this->etcd_op->list("/");
    }

    bool VFS::is_dir(string const & s) {
        throw (ERR_NOT_IMPLEMENTED);
    }

    bool VFS::is_file(string const & s) {
        throw (ERR_NOT_IMPLEMENTED);
    }

    bool VFS::exists(string const & s) {
        throw (ERR_NOT_IMPLEMENTED);
    }


} // namespace eds
