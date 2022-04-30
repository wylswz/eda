#ifndef VFS_H
#define VFS_H

#include <vector>
#include <string>
#include <eda/etcd/etcd_op.hpp>
#include "eda/vfs/path.hpp"

using namespace std;

namespace eda_vfs
{
    struct Key
    {
        string key_str;
        bool is_dir;

        Key();
        Key(string key_str, bool is_dir);
    };

    class Path_Tree_Node
    {
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

        Path_Tree_Node();

        Path_Tree_Node(string const &token);

        Path_Tree_Node(string const &token, Path_Tree_Node &parent);

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
        shared_ptr<Path_Tree_Node> find_path(string const& path);

        Path_Tree_Node *get_parent();

        shared_ptr<Path_Tree_Node> find(string const &child_token);

        void insert_child(Path_Tree_Node &child);

        bool is_null_node();

        vector<string> list_children_token();

        vector<shared_ptr<Path_Tree_Node>> list_children();

        string get_token();
    };

    class VFS
    {
    private:
        eda::ETCD_Op etcd_op;

    public:
        VFS();
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