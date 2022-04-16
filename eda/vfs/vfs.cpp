#include "eda/vfs/vfs.hpp"
#include "eda/core/errors.hpp"
#include "eda/core/functools.hpp"

#define SPLITTER '/'

using namespace std;

namespace eda
{

    Key::Key(): key_str{}, is_dir{false} {}
    Key::Key(string key_str, bool is_dir ) : key_str{key_str}, is_dir{is_dir}
    {
    }

    /**
     * @brief Indicates null node
     *
     */
    Path_Tree_Node NULL_PATH_NODE(".!~");

    /**
     * @brief Construct a root node
     *
     */
    Path_Tree_Node::Path_Tree_Node() : token{}, children{}, parent{nullptr}, root{true}
    {
    }

    Path_Tree_Node::Path_Tree_Node(string const &token) : token{token}, children{}, parent{}, root{false}
    {
    }

    Path_Tree_Node::Path_Tree_Node(string const &token, Path_Tree_Node &parent) : token{token}, children{}, root{false}
    {
        this->parent = &parent;
    }

    /**
     * @brief Copy constructor
     *
     * @param that
     */
    Path_Tree_Node::Path_Tree_Node(Path_Tree_Node const &that) noexcept
    {
        token = that.token;
        children = that.children;
        parent = that.parent; // We intend to do shallow copy
        root = that.root;
    }

    Path_Tree_Node::~Path_Tree_Node()
    {
        this->parent = nullptr; // do not deallocate parent
    }

    void Path_Tree_Node::swap(Path_Tree_Node &that)
    {
        std::swap(this->token, that.token);
        std::swap(this->children, that.children);
        std::swap(this->parent, that.parent);
        std::swap(this->root, that.root);
    }

    /**
     * @brief Copy operator
     *
     * @param that
     * @return Path_Tree_Node&
     */
    Path_Tree_Node &Path_Tree_Node::operator=(Path_Tree_Node const &that) noexcept
    {
        Path_Tree_Node tmp(that);
        swap(tmp);
        return *this;
    }

    Path_Tree_Node *Path_Tree_Node::get_parent()
    {
        return this->parent;
    }

    Path_Tree_Node &Path_Tree_Node::find(string const &child_token)
    {
        for (auto &c : this->children)
        {
            if (c.token == child_token)
            {
                return c;
            }
        }
        return NULL_PATH_NODE;
    }

    bool Path_Tree_Node::is_null_node()
    {
        return token == ".!~";
    }

    void Path_Tree_Node::insert_child(Path_Tree_Node &child)
    {
        if (this->find(child.token).is_null_node())
        {
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
    void _do_insert(eda_path::P_Parser p, Path_Tree_Node &into)
    {
        if (p.has_next())
        {
            string token = p.next();
            Path_Tree_Node node(token);
            Path_Tree_Node &child = into.find(token);

            if (child.is_null_node())
            {
                // Not found
                // Create a child and insert if not exists
                Path_Tree_Node _tmp(token);
                into.insert_child(_tmp);
                // Need to find again because
                return _do_insert(p, into.find(token));
            }
            return _do_insert(p, child);
        }
        else
        {
            return;
        }
    }

    void Path_Tree_Node::insert_path(string const &path)
    {
        eda_path::P_Parser p(path);
        _do_insert(p, *this);
    }

    string Path_Tree_Node::get_token() {
        return this->token;
    }

    vector<string> Path_Tree_Node::list_children_token() {
        function<string (eda::Path_Tree_Node&)> token_getter = [](Path_Tree_Node& n) {return n.get_token();};
        return eda_core::map_to(this->children, token_getter);
    }

    vector<Path_Tree_Node> Path_Tree_Node::list_children() {
        return this->children;
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

    Path_Tree_Node construct_path_tree(vector<string> path) {
        Path_Tree_Node root;
        for (string const & s : path) {
            root.insert_path(s);
        }
        return root;
    }

    vector<Key> VFS::ls()
    {
        // todo: get prefix from context
        vector<string> keys = this->etcd_op.list("/");
        Path_Tree_Node n = construct_path_tree(keys);
        function<Key (Path_Tree_Node&)> mapper = [](Path_Tree_Node& n) {
            Key k(n.get_token(), n.list_children().size() > 0);
            return k;
        };
        return eda_core::map_to(n.list_children(), mapper);
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

} // namespace eds
