#include "eda/vfs/vfs.hpp"
#include "eda/core/errors.hpp"

#define SPLITTER '/'

using namespace std;

namespace eda
{
    Path_Tree_Node::Path_Tree_Node(string const &token) : token{token}, children{}, parent{}
    {
    }

    Path_Tree_Node::Path_Tree_Node(string const& token, Path_Tree_Node & parent): 
    token{token}, children{}
    {
        this->parent = &parent;
    }


    Path_Tree_Node::Path_Tree_Node(Path_Tree_Node const &that) noexcept
    {
        token = that.token;
        children = that.children;
        parent = that.parent;  // We intend to do shallow copy
    }

    Path_Tree_Node::~Path_Tree_Node()
    {
        this->children.~vector();
        this->token.~basic_string();
        this->parent = nullptr;  // do not deallocate parent
    }

    void Path_Tree_Node::swap(Path_Tree_Node& that) {
        std::swap(this->token, that.token);
        std::swap(this->children, that.children);
        std::swap(this->parent, that.parent);
    }

    Path_Tree_Node& Path_Tree_Node::operator=(Path_Tree_Node const& that) noexcept {
        Path_Tree_Node tmp(that);
        swap(tmp);
        return *this;
    }

    Path_Tree_Node* Path_Tree_Node::get_parent() {
        return this->parent;
    }

    bool Path_Tree_Node::exist_child(string const& child_token) {
        for (auto const& c : this->children) {
            if (c.token == child_token) {
                return true;
            }
        }
        return false;
    }

    void Path_Tree_Node::insert_child(Path_Tree_Node &child) {
        if (!exist_child(child.token)) {
            this->children.push_back(child);
            child.parent = this;
        }
    }


    /**
     * @brief Recursively insert a path into a node
     * 
     * if Path has next, initialize one from current token and insert it
     * if token is not found in children vector, otherwise find that child.
     * 
     * Insert remaining tokens to that child recursively
     * 
     * @param p 
     * @param node 
     */
    void _do_insert(eda_path::P_Parser p, Path_Tree_Node& node) {
        
    }

    void Path_Tree_Node::insert_path(string const& path) {
        eda_path::P_Parser p(path);
        _do_insert(p, *this);
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
