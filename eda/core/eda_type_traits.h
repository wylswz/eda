#ifndef EDA_TYPE_TRAITS_H
#define EDA_TYPE_TRAITS_H

#include <stdlib.h>
#include <type_traits>

namespace eda_core
{

    template <typename Base, typename U>
    bool instance_of(U const *val)
    {
        return std::is_base_of<Base, U>::value;
    }

    template <typename Base, typename U>
    inline bool p_instance_of (U const *ptr)
    {
        return dynamic_cast<Base const *>(ptr) != nullptr;
    }
}

#endif