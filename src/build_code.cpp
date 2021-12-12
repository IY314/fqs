#include "build_code.h"
#include "lexer.h"
#include "error.h"
#include "parser.h"
#include "node.h"
#include <variant>
#include <optional>
#include <utility>
#include <iostream>

std::pair<std::optional<fqs::node>, std::optional<fqs::base_error>> fqs::run(std::string fn, std::string text) {
    fqs::lexer l(fn, text);
    fqs::lexer_result lex_result = l.make_tokens();
    if (std::get_if<fqs::base_error>(&lex_result) != nullptr) {
        return {{}, std::get<fqs::base_error>(lex_result)};
    }

    fqs::parser p(std::get<fqs::vec_token>(lex_result));
    fqs::parse_result parse_result = p.parse();

    // TODO: add tree evaluation

    return {parse_result.nd, parse_result.error};
}
