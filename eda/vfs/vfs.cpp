#include "eda/vfs/vfs.h"

namespace eda
{
    VFS::VFS() {
        ETCD_Op etcd_op;
        this->etcd_op = &etcd_op;
    }

    VFS::~VFS() {
        delete this->etcd_op;
    }

} // namespace eds
