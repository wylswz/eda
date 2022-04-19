#ifndef EDA_TYPE_TRAITS_H
#define EDA_TYPE_TRAITS_H

#include<stdlib.h>
#include<type_traits>

namespace eda_core
{
    template <typename T, typename U>
    bool instance_of(U val) {
        return std::is_base_of<T, U>::value;
    }
}


#endif