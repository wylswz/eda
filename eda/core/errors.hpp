#ifndef EDA_ERR_H

#define EDA_ERR_H

#define ERR_NOT_IMPLEMENTED 10000
#define ERR_ETCD_ERR 10001

#define ERR_IDX_OUT_OF_BOUND 20000
#define UNINITIALIZED_ACCESS 20001

#include <string>
using namespace std;

namespace eda
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
    };

}

#endif