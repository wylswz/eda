#include "eda/vfs/vfs.hpp"


int main(int argc, char** argv) {
    eda::VFS vfs;
    vector<string> ks = vfs.ls();
    for (auto const &k : ks) {
        cout << k << endl;
    } 
}