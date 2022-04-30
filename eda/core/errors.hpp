#ifndef EDA_ERR_H

#define EDA_ERR_H

#define ERR_NOT_IMPLEMENTED 10000
#define ERR_ETCD_ERR 10001

#define ERR_IDX_OUT_OF_BOUND 20000
#define ERR_UNINITIALIZED_ACCESS 20001

#define ERR_FILE_NOT_EXISTS 20010

#define ERR_ILLEGAL_STATE 20020

#include <string>
using namespace std;

namespace eda_core
{
    /**
     * @brief This is the base class for all eda exceptions
     *
     */
    class EDA_Exception : std::exception
    {

    private:
        int code;
        string desc;

    public:
        EDA_Exception(int code, string const &desc) : desc{desc},
                                                      code{code}
        {
        }

        ~EDA_Exception() = default;

        bool is(int err_code) const
        {
            return this->code == err_code;
        }

        string repr()
        {
            return "[EDA_Exception]: " + desc;
        }
    };

}

#endif