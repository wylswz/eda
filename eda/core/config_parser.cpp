#include "eda/core/config_parser.h"
#include "eda/core/std.h"
#include "eda/core/eda_type_traits.h"
#include <stack>
#include <yaml.h>

using namespace std;

namespace eda_core
{

    Y_Object auto_scalar_type(char *val, int len) {
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

        /*
         * if 0, expecting a key
         * if 1, expecting a value 
         */
        int kv_state = 0;
        string key;
        stack<Y_Object> stack;


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
                cout << s << endl;
                break;
            }
            case yaml_event_type_e::YAML_SEQUENCE_START_EVENT:
            cout<<"seq start"<<endl;
                break;
            case yaml_event_type_e::YAML_SEQUENCE_END_EVENT:
            cout<<"seq end"<<endl;
                break;
            case yaml_event_type_e::YAML_MAPPING_START_EVENT:
                Y_Map new_map{};
                if (stack.empty()) {
                } else {
                    if (eda_core::instance_of<Y_Seq>(stack.top())) {
                        
                        // push back an empty Y_Map
                        stack.push(new_map);
                    } else if (eda_core::instance_of<Y_Map>(stack.top())) {
                        // put to key
                    }
                }
                stack.push(new_map);
                break;
            case yaml_event_type_e::YAML_MAPPING_END_EVENT:
                stack.pop();
            cout<<"mapping end"<<endl;
                break;
            case yaml_event_type_e::YAML_DOCUMENT_END_EVENT:
                done=true;
            default:
                break;
            }
        }
    }
}