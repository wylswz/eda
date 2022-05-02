#ifndef VFS_H
#define VFS_H

#include <vector>
#include <string>
#include <filesystem>
#include <eda/etcd/etcd_op.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace eda_vfs
{

    /**
     * @brief Check whether given path is a valid absolute path
     *
     * @param path
     * @return true
     * @return false
     */
    bool validate_absolute_path(string const &path);

    /**
     * @brief Check whether given path is a valid relative path
     *
     * @param path
     * @return true
     * @return false
     */
    bool validate_relative_path(string const &path);

    /**
     * @brief Compute absolute path from relation path and current dir
     *
     * @param pwd current dir
     * @param relative_path relative path, like ../../xxx, ./xxx. xxx/yyy/zzz
     * @return string
     */
    string compute_absolute_path(string const &pwd, string const &relative_path);

    string sanitize_path(string const &path);

    class P_Parser
    {
    private:
        string str;
        string current_token;
        bool _can_peek;
        int _offset;
        // c++ 17
        fs::path p;
        fs::path::iterator it;
        fs::path root_name;
        fs::path root_dir;

    public:
        P_Parser(string const &str);
        /**
         * @brief Copy all states in P_Parser
         * 
         * @param that 
         */
        P_Parser(P_Parser const & that);

        P_Parser & operator =(P_Parser const & that);

        bool has_next();

        const string &peek();

        const string &next();

    };

    struct Key
    {
        string key_str;
        bool is_dir;

        Key();
        Key(string key_str, bool is_dir);
    };

    class Path_Tree_Node : public enable_shared_from_this<Path_Tree_Node>
    {

    private:
        /**
         * @brief Always use Create(...) method to create objects
         *
         */
        Path_Tree_Node();

        Path_Tree_Node(string const &token);

        Path_Tree_Node(string const &token, Path_Tree_Node &parent);
#ifdef UNITTEST
    public:
#else
    private:
#endif
        string token;
        bool root;
        vector<shared_ptr<Path_Tree_Node>> children;
        Path_Tree_Node *parent;

    public:
        static shared_ptr<Path_Tree_Node> Create()
        {
            return make_shared<Path_Tree_Node>(Path_Tree_Node());
        }

        static shared_ptr<Path_Tree_Node> Create(string const &token)
        {
            return make_shared<Path_Tree_Node>(Path_Tree_Node(token));
        }

        static shared_ptr<Path_Tree_Node> Create(string const &token, Path_Tree_Node &parent)
        {
            return make_shared<Path_Tree_Node>(Path_Tree_Node(token, parent));
        }

        /**
         * @brief Get the handle of this object
         *
         * @return shared_ptr<Path_Tree_Node>
         */
        shared_ptr<Path_Tree_Node> get_handle();

        Path_Tree_Node(Path_Tree_Node const &that) noexcept;

        Path_Tree_Node &operator=(Path_Tree_Node const &that) noexcept;

        ~Path_Tree_Node();

        void swap(Path_Tree_Node &that);

        /**
         * @brief Insert a path to the tree
         *
         * @param path full path
         */
        void insert_path(string const &path);

        /**
         * @brief Find the corresponding node in path tree given path
         *
         * @param path
         * @return Path_Tree_Node& NULL_PATH_NODE if not exists, or else return a reference
         */
        shared_ptr<Path_Tree_Node> find_path(string const &path);

        Path_Tree_Node *get_parent();

        shared_ptr<Path_Tree_Node> find(string const &child_token);

        void insert_child(shared_ptr<Path_Tree_Node> child);

        bool is_null_node();

        vector<string> list_children_token();

        vector<shared_ptr<Path_Tree_Node>> list_children();

        string get_token();
    };

    class VFS
    {
    private:
        eda::ETCD_Op etcd_op;
        string _pwd;

    public:
        VFS(eda::ETCD_Op etcd_op);
        ~VFS();
        vector<Key> ls();
        string pwd();
        string cd(string const &s);
        bool is_dir(string const &s);
        bool is_file(string const &s);
        bool exists(string const &s);
    };

    vector<Key> aggregate(vector<string> const &keys, string const &base);

}

#endif