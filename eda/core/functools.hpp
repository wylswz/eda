#ifndef EDA_FUNCTOOLS_H
#define EDA_FUNCTOOLS_H

#include <vector>
#include <functional>

using namespace std;

namespace eda_core
{
    template <typename U, typename V>
    vector<V> map_to(vector<U> src, function<V (U&)> mapper)
    {
        vector<V> res(src.size());
        for (int i=0; i<src.size(); ++i) {
            res[i] = mapper(src[i]);
        }
        return res;
    }
}


#endif