#ifndef VFS_H
#define VFS_H

#include <vector>
#include <string>
#include <eda/etcd/etcd_op.hpp>
#include "eda/vfs/path.h"

using namespace std;

namespace eda
{
    struct Key
    {    
        string key_str;
        bool is_dir;

        Key(string key_str, bool is_dir):
        key_str{key_str} {
            this->is_dir = is_dir;
        }
        
    };

    class Path_Tree_Node {
    private:
        string token;
        vector<Path_Tree_Node> children;
        shared_ptr<Path_Tree_Node> parent;
    public:
        Path_Tree_Node(string const& token);

        Path_Tree_Node(Path_Tree_Node const & that) noexcept;

        Path_Tree_Node& operator =(Path_Tree_Node const & that) noexcept;

        ~Path_Tree_Node();

        /**
         * @brief Insert a path to the tree
         * 
         * @param path full path
         */
        void insert_path(string const& path);
    };

    class VFS
    {
    private:
        ETCD_Op etcd_op;

    public:
        VFS();
        ~VFS();
        vector<Key> ls();
        string pwd();
        string cd(string const & s);
        bool is_dir(string const & s);
        bool is_file(string const & s);
        bool exists(string const & s);
    };

    vector<Key> aggregate(vector<string> const & keys, string const & base);
    
}

#endif