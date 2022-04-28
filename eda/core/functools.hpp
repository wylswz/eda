#ifndef EDA_FUNCTOOLS_H
#define EDA_FUNCTOOLS_H

#include <vector>
#include <functional>
#include <cassert>

using namespace std;

namespace eda_core
{
    template <typename U, typename V>
    vector<V> map_to(vector<U> src, function<V(U &)> mapper)
    {
        vector<V> res(src.size());
        for (int i = 0; i < src.size(); ++i)
        {
            res[i] = mapper(src[i]);
        }
        return res;
    }

    template <typename T>
    T foldl(vector<T> src, function<T(T const &, T const &)> folder)
    {
        assert(src.size() > 0);
        T res = src[0];
        for (int i = 1; i < src.size(); ++i)
        {
            res = folder(res, src[i]);
        }
        return res;
    }

    template<typename T>
    struct Folders{
        static function<T(T const&, T const&)> plus;
    };

    template<typename T>
    function<T(T const&, T const&)> Folders<T>::plus = [](T const& t1, T const& t2) {return t1 + t2;};
}

#endif