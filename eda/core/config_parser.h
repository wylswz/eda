#ifndef EDA_CONFIG_PARSER_H
#define EDA_CONFIG_PARSER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

namespace eda_core
{

    class Y_Object
    {
    public:
        // References are shared between stacks
        vector<shared_ptr<Y_Object>> seq;
        unordered_map<string, shared_ptr<Y_Object>> map;
        string token;

        Y_Object();
        virtual ~Y_Object() = default;

    };

    class Y_Err : public Y_Object
    {
    };

    class Y_Int : public Y_Object
    {
    public:
        int value();
    };

    class Y_Float : public Y_Object
    {
    public:
        float value();
    };

    class Y_String : public Y_Object
    {
    public:
        string value();
        Y_String(string s);
    };

    class Y_Seq : public Y_Object
    {
    public:
        vector<shared_ptr<Y_Object>> &value();
        Y_Seq(Y_Object &src);
        Y_Seq(Y_Object &&src);
        Y_Seq();
    };

    class Y_Map : public Y_Object
    {
    public:
        unordered_map<string, shared_ptr<Y_Object>> &value();
        Y_Map(Y_Object &src);
        Y_Map(Y_Object &&src);
        Y_Map();

        /**
         * @brief Put val to map as a shared pointer and return the shared pointer
         * 
         * @param key 
         * @param val 
         */
        shared_ptr<Y_Object> put(string const& key, Y_Object& val);

        /**
         * @brief Rval reference version of put. Move the rval ref, then invoke normal put
         * 
         * @param key 
         * @param val 
         * @return shared_ptr<Y_Object> 
         */
        shared_ptr<Y_Object> put(string const& key, Y_Object&& val);

        /**
         * @brief Get a value by key
         * 
         * @param key 
         * @return shared_ptr<Y_Object> shared_prt(nullptr) is returned if not found
         */
        shared_ptr<Y_Object> get(string const& key);
    };

    /**
     * @brief Parse yaml file and return a copy of parsed value
     *
     * @param path
     * @return Y_Object
     */
    Y_Object parse_yaml(char const *path);

    struct Y_Frame
    {

        /*
         * if 0, expecting a key
         * if 1, expecting a value
         */
        int kv_state;

        /**
         * when lv_state == 0, the next scalar encountered is used as key
         */
        string key;
        shared_ptr<Y_Object> data;

        void next_token(string token);
        bool expecting_key();
    };

}

#endif