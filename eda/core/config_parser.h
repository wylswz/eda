#ifndef EDA_CONFIG_PARSER_H
#define EDA_CONFIG_PARSER_H

#include<string>
#include<vector>
#include<unordered_map>


using namespace std;

namespace eda_core {

    struct Y_Object {
        
    };

    struct Y_Err : public Y_Object {

    };

    struct Y_Int : public Y_Object {
        int value();
    };

    struct Y_Float : public Y_Object {
        float value();
    };

    struct Y_String : public Y_Object {
        string value();
    };

    struct Y_Seq : public Y_Object {
        vector<Y_Object>& value();
    };

    struct Y_Map : public Y_Object {
        unordered_map<string, Y_Object>& value();
    };

    /**
     * @brief Parse yaml file and return a copy of parsed value
     * 
     * @param path 
     * @return Y_Object 
     */
    Y_Object parse_yaml(char const * path);

    struct Y_Frame {

        /*
         * if 0, expecting a key
         * if 1, expecting a value
         */
        int kv_state;

        /**
         * when lv_state == 0, the next scalar encountered is used as key
         */
        string key;
        Y_Object data;
    };


}

#endif