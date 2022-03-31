#include "eda/vfs/vfs.hpp"
#include "eda/core/errors.hpp"

#define SPLITTER '/'

using namespace std;


namespace eda {
    Path_Tree_Node::Path_Tree_Node(string const& token):
    token{token},children{},parent{} {
        parent = nullptr;
    }
}


namespace eda
{
    VFS::VFS():
    etcd_op {} {
    }

    VFS::~VFS() = default;

    string VFS::cd(string const & dir) {
        throw (ERR_NOT_IMPLEMENTED);
    }

    string VFS::pwd() {
        throw (ERR_NOT_IMPLEMENTED);
    }

    vector<Key> VFS::ls() {
        //todo: get prefix from context
        vector<string> keys = this->etcd_op.list("/");
        return aggregate(keys, "/");
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

    vector<Key> aggregate(vector<string> const & keys, string const & base) {
        string new_base(base);
        if (!*base.end() == SPLITTER) {
            new_base.push_back(SPLITTER);
        }
        vector<Key> res;
        for (auto const & k : keys) {
            if (k == new_base) {
                continue;
            }
        }
        return res;
    }


} // namespace eds
