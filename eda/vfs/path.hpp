#ifndef EDA_PATH_H
#define EDA_PATH_H

#include<string>
#include "eda/core/errors.hpp"

using namespace std;

namespace eda_path {

    class P_Parser {
        private:
        string str;
        string current_token;
        size_t current;
        bool _can_peek;

        public:
        P_Parser(string const& str): 
        str{str}, current_token{}{
            current = 1;
        }

        bool has_next() {
            return current < str.size();
        }

        const string& peek() {
            if (this->_can_peek) {
                return this->current_token;
            }
            throw eda::EDA_Exception(UNINITIALIZED_ACCESS, "Cannot peed a parser before first next() invocation");
        }

        const string& next() {
            size_t from = this->current;
            size_t len = 0;
            while (this->current < str.size() && str[this->current] != '/') {
                this->current++;
                len++;
            }
            // Move the point forward to slash or pass the string boundary
            this->current ++;
            this->current_token = str.substr(from, len);
            this->_can_peek = true;
            return this->current_token;
        }
        
    };

}

#endif