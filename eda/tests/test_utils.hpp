#include <vector>
#include <iostream>
using namespace std;
template<typename T>
void print_vec(vector<T> v) {
    for (auto const& i : v) {
        cout << i << ", ";
    }
    cout << endl;
}