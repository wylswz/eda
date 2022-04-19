#include "eda/core/config_parser.h"
#include "eda/core/std.h"
#include <yaml.h>

using namespace std;

namespace eda_core
{

    Y_Object parse_yaml(char const *path)
    {
        FILE *input = fopen(path, "rb");
        yaml_parser_t parser;
        yaml_event_t event;
        int done = 0;
        yaml_parser_initialize(&parser);

        yaml_parser_set_input_file(&parser, input);

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
                break;
            case yaml_event_type_e::YAML_SEQUENCE_END_EVENT:
                break;
            case yaml_event_type_e::YAML_MAPPING_START_EVENT:
                break;
            case yaml_event_type_e::YAML_MAPPING_END_EVENT:
                break;
            case yaml_event_type_e::YAML_DOCUMENT_END_EVENT:
                done=true;
            default:
                break;
            }
        }
    }
}