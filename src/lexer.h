#ifndef lexer_h
#define lexer_h

#include "position.h"
#include "token.h"
#include <string>
#include <vector>
#include <variant>

namespace fqs {
    class lexer {
        public:
        lexer(std::string, std::string);
        std::variant<std::vector<token>> make_tokens();

        private:
        std::string fn, text;
        position pos;
        char current_char;

        void advance();
        token make_number();
        token make_literal();
        token make_operator();
    };
}

#endif
