#include "eda/vfs/vfs.hpp"
#include "eda/core/errors.hpp"

#define SPLITTER '/'

using namespace std;

namespace eda
{
    Path_Tree_Node::Path_Tree_Node(string const &token) : token{token}, children{}, parent{}
    {
        parent = shared_ptr<Path_Tree_Node>(nullptr);
    }


    Path_Tree_Node::Path_Tree_Node(Path_Tree_Node const &that) noexcept
    {
        token = that.token;
        children = that.children;
        parent = that.parent;
    }

    Path_Tree_Node::~Path_Tree_Node()
    {
        this->children.~vector();
        this->token.~basic_string();
        this->parent.reset(); // Just release ownership
    }

    void Path_Tree_Node::insert_path(string const& path) {
        
    }

    
}

namespace eda
{
    VFS::VFS() : etcd_op{}
    {
    }

    VFS::~VFS() = default;

    string VFS::cd(string const &dir)
    {
        throw(ERR_NOT_IMPLEMENTED);
    }

    string VFS::pwd()
    {
        throw(ERR_NOT_IMPLEMENTED);
    }

    vector<Key> VFS::ls()
    {
        // todo: get prefix from context
        vector<string> keys = this->etcd_op.list("/");
        return aggregate(keys, "/");
    }

    bool VFS::is_dir(string const &s)
    {
        throw(ERR_NOT_IMPLEMENTED);
    }

    bool VFS::is_file(string const &s)
    {
        throw(ERR_NOT_IMPLEMENTED);
    }

    bool VFS::exists(string const &s)
    {
        throw(ERR_NOT_IMPLEMENTED);
    }

    vector<Key> aggregate(vector<string> const &keys, string const &base)
    {
        vector<Key> res;
        return res;
    }


} // namespace eds
