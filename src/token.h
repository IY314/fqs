#ifndef token_h
#define token_h

#include "position.h"
#include <variant>
#include <string>

namespace fqs {
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

    typedef std::variant<nullptr_t, int, std::string, literal_type, operator_type> token_value;

    class token {
        public:
        token_type type;
        token_value value;
        position pos_start, pos_end;

        token(token_type, token_value);
        std::string to_string();
    };
}

#endif
