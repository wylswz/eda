#include <vector>
#include <string>
#include <eda/etcd/etcd_op.h>
#include "eda/vfs/path.h"

using namespace std;

namespace eda
{
    class Key
    {
    };

    class VFS
    {
    private:
        ETCD_Op *etcd_op;

    public:
        VFS();
        ~VFS();
        vector<Key> ls();
        Key pwd();
        Key cd(string const & s);
        bool is_dir(string const & s);
        bool is_file(string const & s);
        bool exists(string const & s);
    };
}
