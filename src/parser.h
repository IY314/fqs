#ifndef parser_h
#define parser_h

#include "token.h"
#include "node.h"
#include "error.h"
#include <vector>
#include <optional>
#include <variant>
#include <functional>

namespace fqs {
    class parse_result {
        public:
        std::optional<node> nd;
        std::optional<base_error> error;

        parse_result();

        std::variant<node, token> register_(std::variant<node, parse_result, token>);

        parse_result success(node);

        parse_result failure(base_error);
    };

    class parser {
        public:
        vec_token tokens;
        int tok_idx;
        std::optional<token> current_tok;

        parser(vec_token);

        token advance();

        parse_result parse();

        parse_result expr();

        parse_result term();

        parse_result factor();

        parse_result bin_op(std::function<parse_result(parser *)>, std::vector<operator_type>);
    };
}

#endif
