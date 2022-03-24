#ifndef EDA_ERR_H

#define EDA_ERR_H

#define ERR_NOT_IMPLEMENTED 10000
#define ERR_ETCD_ERR 10001

#include <string>
using namespace std;

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

#endif