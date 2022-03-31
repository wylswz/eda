#include "eda/vfs/vfs.hpp"


int main(int argc, char** argv) {
    eda::VFS vfs;
    vector<eda::Key> ks = vfs.ls();

}