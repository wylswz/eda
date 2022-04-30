#include "eda/vfs/vfs.hpp"

int main(int argc, char **argv)
{

    try
    {
        eda_vfs::VFS vfs;
        vector<eda_vfs::Key> ks = vfs.ls();
        for (auto const &k : ks)
        {
            cout << k.key_str << endl;
        }
    }
    catch (eda_core::EDA_Exception e)
    {
        cout << e.repr() << endl;
    }
}