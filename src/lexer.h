#ifndef lexer_h
#define lexer_h

#include "position.h"
#include "token.h"
#include "error.h"
#include <string>
#include <vector>
#include <variant>

namespace fqs {
    typedef std::vector<token> vec_token;
    typedef std::variant<vec_token, base_error> lexer_result;

    class lexer {
        public:
        lexer(std::string, std::string);
        std::variant<std::vector<token>, base_error> make_tokens();

        private:
        std::string fn, text;
        position pos;
        char current_char;

        void advance();
        token make_number();
        std::variant<token, base_error> make_literal();
        std::variant<token, base_error> make_operator();
    };
}

#endif
