#ifndef EDA_PATH_H
#define EDA_PATH_H

#include<string>

using namespace std;

namespace eda_path {

    class P_Parser {
        private:
        string str;
        string current_token;
        size_t current;

        public:
        P_Parser(string const& str): 
        str{str}, current_token{}{
            current = 0;
        }

        bool has_next() {
            return current != str.size();
        }

        string next() {
            size_t from = this->current++;
            size_t len = 0;
            while (str[current] != '/') {
                this->current++;
                len++;
            }
            return str.substr(from, len);
        }
        
    };

}

#endif