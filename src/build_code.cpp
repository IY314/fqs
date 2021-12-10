#include "build_code.h"
#include "lexer.h"
#include "error.h"
#include <iostream>

void fqs::run(std::string fn, std::string text) {
    fqs::lexer l(fn, text);
    fqs::lexer_result lex_result = l.make_tokens();

    // TODO: add AST tree parsing

    // TODO: add tree evaluation

    if (std::get_if<fqs::base_error>(&lex_result) != nullptr) {
        std::cout << std::get<fqs::base_error>(lex_result).to_string() << std::endl;
    } else {
        for (auto tok : std::get<fqs::vec_token>(lex_result)) {
            std::cout << tok.to_string() << std::endl;
        }
    }
}
