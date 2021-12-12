#ifndef token_h
#define token_h

#define NUMBERS "0123456789"
#define LITERALS "()"
#define OPERATORS "+-*/"

#include "position.h"
#include <variant>
#include <string>
#include <vector>
#include <optional>

namespace fqs {
    class token;

    typedef std::vector<token> vec_token;
    
    enum token_type {
        tt_num,
        tt_lit,
        tt_op,
        tt_eof
    };

    enum literal_type {
        lt_lparen,
        lt_rparen
    };

    enum operator_type {
        ot_plus,
        ot_minus,
        ot_mul,
        ot_div
    };

    typedef std::optional<std::variant<int, std::string, literal_type, operator_type>> token_value;

    class token {
        public:
        token_type type;
        token_value value;
        position pos_start, pos_end;

        token(token_type, token_value, position, std::optional<position>);
        std::string to_string();
    };
}

#endif
