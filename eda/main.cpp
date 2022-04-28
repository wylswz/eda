#include "eda/vfs/vfs.hpp"

int main(int argc, char **argv)
{

    try
    {
        eda::VFS vfs;
        vector<eda::Key> ks = vfs.ls();
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