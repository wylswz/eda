#ifndef EDA_TYPE_TRAITS_H
#define EDA_TYPE_TRAITS_H

#include <stdlib.h>
#include <type_traits>

namespace eda_core
{

    /**
     * @brief Perform a strict instance_of
     * 
     * @tparam Base base class
     * @tparam U Derived class
     * @param val 
     * @return true  if the class of val is subclasses Base, or is just Base itself
     * @return false 
     */
    template <typename Base, typename U>
    bool instance_of(U const *val)
    {
        return std::is_base_of<Base, U>::value;
    }

    /**
     * @brief Perform a polymorphic instance_of operation.
     * 
     * @tparam Base base class
     * @tparam U class of object
     * @param ptr 
     * @return true if the object is an instance if Base. 
     * @return false 
     */
    template <typename Base, typename U>
    inline bool p_instance_of (U const *ptr)
    {
        return dynamic_cast<Base const *>(ptr) != nullptr;
    }
}

#endif