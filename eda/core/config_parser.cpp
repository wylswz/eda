#include "eda/core/config_parser.h"
#include "eda/core/std.h"
#include "eda/core/eda_type_traits.h"
#include <stack>
#include <yaml.h>

using namespace std;

namespace eda_core
{

    Y_Object::Y_Object():seq{}, map{}, token{} {

    }

    /**
     * @brief String
     * 
     * @return string 
     */
    string Y_String::value() {
        return this->token;
    }

    Y_String::Y_String(string token):Y_Object() {
        this->token = token;
    }


    /**
     * @brief Map
     * 
     * @return unordered_map<string, Y_Object>& 
     */
    unordered_map<string, shared_ptr<Y_Object>>& Y_Map::value() {
        return this->map;
    }
    Y_Map::Y_Map():Y_Object(){}
    Y_Map::Y_Map(Y_Object& src):Y_Object(src) {}
    Y_Map::Y_Map(Y_Object&& src):Y_Object(src){}


    /**
     * @brief Sequence
     * 
     * @return vector<Y_Object>& 
     */
    vector<shared_ptr<Y_Object>>& Y_Seq::value() {
        return this->seq;
    }

    Y_Seq::Y_Seq():Y_Object() {}
    Y_Seq::Y_Seq(Y_Object& src):Y_Object(src){}
    Y_Seq::Y_Seq(Y_Object&& src):Y_Object(src){}

    Y_Object auto_scalar_type(char *val, int len)
    {
        return Y_Object{};
    }

    Y_Object parse_yaml(char const *path)
    {
        FILE *input = fopen(path, "rb");
        yaml_parser_t parser;
        yaml_event_t event;
        int done = 0;
        yaml_parser_initialize(&parser);

        yaml_parser_set_input_file(&parser, input);

        stack<Y_Frame> stk;
        Y_Frame last_pop;

        while (!done)
        {
            if (!yaml_parser_parse(&parser, &event))
            {
                return Y_Err{};
            }
            switch (event.type)
            {
            case yaml_event_type_e::YAML_SCALAR_EVENT:
            {
                /* code */
                yaml_char_t *v = event.data.scalar.value;
                int len = event.data.scalar.length;
                string s(v, v + len);
                stk.top().next_token(s);
                break;
            }
            case yaml_event_type_e::YAML_SEQUENCE_START_EVENT:
                break;
            case yaml_event_type_e::YAML_SEQUENCE_END_EVENT:
                break;

            /**
             * @brief When a map is encountered, a new Y_Map is created and add to current container
             * - if current container is sequence, then push to back
             * - if current container is map, then put to corresponding key
             *
             * As a container, the new map should be pushed to stack
             */
            case yaml_event_type_e::YAML_MAPPING_START_EVENT:
            {
                Y_Frame frame{0, "", std::make_shared<Y_Map>(Y_Map{})};
                if (stk.empty())
                {
                }
                else
                {
                    if (eda_core::p_instance_of<Y_Seq>(stk.top().data.get()))
                    {

                        // push back an empty Y_Map
                        stk.top().data.get()->seq.push_back(frame.data);
                        
                    }
                    else if (eda_core::p_instance_of<Y_Map>(stk.top().data.get()))
                    {
                        // put to key
                        stk.top().data.get()->map.emplace(stk.top().key, frame.data);
                    }
                }
                stk.push(frame);
                break;
            }

            case yaml_event_type_e::YAML_MAPPING_END_EVENT:
                last_pop = stk.top();
                stk.pop();
                break;
            case yaml_event_type_e::YAML_DOCUMENT_END_EVENT:
                done = true;
            default:
                break;
            }
        }
        return *(last_pop.data.get());
    }

    void Y_Frame::next_token(string token)
    {

        if (eda_core::p_instance_of<Y_Map>(this->data.get()))
        {
            if (this->expecting_key())
            {
                // expecting a key, so set the token as key
                cout<<"Setting key: "<<key<<endl;
                this->key = token;
            }
            else
            {
                // expecting a value
                cout<<"Puting: "<<key << " -> " << token << endl;;
                this->data.get()->map.emplace(key, make_shared<Y_String>(Y_String{token}));
            }
        }

        if (eda_core::p_instance_of<Y_Map>(this->data.get()))
        {
            // Only flip when current frame is map container
            this->kv_state = 1 - this->kv_state;
        }
    }

    bool Y_Frame::expecting_key()
    {
        return this->kv_state;
    }
}