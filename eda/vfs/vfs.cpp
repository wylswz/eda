#include "eda/vfs/vfs.hpp"
#include "eda/core/errors.hpp"
#include "eda/core/functools.hpp"

#define SPLITTER '/'

using namespace std;

namespace eda_vfs
{

    Key::Key() : key_str{}, is_dir{false} {}
    Key::Key(string key_str, bool is_dir) : key_str{key_str}, is_dir{is_dir}
    {
    }

    shared_ptr<Path_Tree_Node> Path_Tree_Node::get_handle() {
        return this->shared_from_this();
    }

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

    shared_ptr<Path_Tree_Node> Path_Tree_Node::find(string const &child_token)
    {
        for (auto &c : this->children)
        {
            if (c->token == child_token)
            {
                return c;
            }
        }
        return nullptr;
    }

    shared_ptr<Path_Tree_Node> _do_find_path(Path_Tree_Node *node, eda_vfs::P_Parser parser)
    {
        if (parser.has_next())
        {
            string token = parser.next();
            shared_ptr<Path_Tree_Node> child = node->find(token);
            if (child == nullptr)
            {
                return nullptr;
            }
            return _do_find_path(child.get(), parser);
        }
        else
        {
            try
            {
                if (parser.peek() == node->get_token())
                {
                    return node->get_handle();
                }
                else
                {
                    return nullptr;
                }
            }
            catch(eda_core::EDA_Exception const &e) {
                if (e.is(ERR_UNINITIALIZED_ACCESS)) {
                    // Finding root node
                    return node->get_handle();
                } else {
                    return nullptr;
                }
            }
        }
    }

    /**
     * @brief Find the node given corresponding path
     * 
     * @param path 
     * @return shared_ptr<Path_Tree_Node> nullptr if not found
     */
    shared_ptr<Path_Tree_Node> Path_Tree_Node::find_path(string const &path)
    {
        eda_vfs::P_Parser parser(path);

        return _do_find_path(this, parser);
    }

    bool Path_Tree_Node::is_null_node()
    {
        return token == ".!~";
    }

    void Path_Tree_Node::insert_child(shared_ptr<Path_Tree_Node> child)
    {
        if (this->find(child->token) == nullptr)
        {
            this->children.push_back(child);
            child->parent = this;
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
    void _do_insert(eda_vfs::P_Parser p, Path_Tree_Node *into)
    {
        if (p.has_next())
        {
            string token = p.next();
            shared_ptr<Path_Tree_Node> node = Path_Tree_Node::Create(token);
            shared_ptr<Path_Tree_Node> child = into->find(token);

            if (child == nullptr)
            {
                // Not found
                // Create a child and insert if not exists
                shared_ptr<Path_Tree_Node> _tmp = Path_Tree_Node::Create(token);
                into->insert_child(_tmp);
                // Need to find again because
                return _do_insert(p, into->find(token).get());
            }
            return _do_insert(p, child.get());
        }
        else
        {
            return;
        }
    }

    void Path_Tree_Node::insert_path(string const &path)
    {
        eda_vfs::P_Parser p(path);
        _do_insert(p, this);
    }

    string Path_Tree_Node::get_token()
    {
        return this->token;
    }

    vector<string> Path_Tree_Node::list_children_token()
    {
        function<string(shared_ptr<Path_Tree_Node>)> token_getter = [](shared_ptr<Path_Tree_Node> n)
        { return n->get_token(); };
        return eda_core::map_to<shared_ptr<Path_Tree_Node>, string>(this->children, token_getter);
    }

    vector<shared_ptr<Path_Tree_Node>> Path_Tree_Node::list_children()
    {
        return this->children;
    }

}

namespace eda_vfs
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

    shared_ptr<Path_Tree_Node> construct_path_tree(vector<string> path)
    {
        shared_ptr<Path_Tree_Node> root = Path_Tree_Node::Create();
        for (string const &s : path)
        {
            root->insert_path(s);
        }
        return root;
    }

    vector<Key> VFS::ls()
    {
        // todo: get prefix from context
        vector<string> keys = this->etcd_op.list("/");
        shared_ptr<Path_Tree_Node> n = construct_path_tree(keys);
        function<Key(shared_ptr<Path_Tree_Node>)> mapper = [](shared_ptr<Path_Tree_Node> n)
        {
            Key k(n->get_token(), n->list_children().size() > 0);
            return k;
        };
        return eda_core::map_to<shared_ptr<Path_Tree_Node>, Key>(n->list_children(), mapper);
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
