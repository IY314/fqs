#include "lexer.h"
#include "position.h"
#include "token.h"
#include "util.h"
#include "error.h"
#include <string>
#include <vector>
#include <variant>
#include <sstream>

fqs::lexer::lexer(std::string _fn, std::string _text)
                 : fn{_fn}, text{_text} {
    pos = position(-1, 0, -1, fn, text);
    current_char = '\0';
}

void fqs::lexer::advance() {
    pos.advance();
    current_char = pos.idx < text.size() ? text[pos.idx] : '\0';
}

std::variant<std::vector<fqs::token>, fqs::base_error> fqs::lexer::make_tokens() {
    std::vector<fqs::token> tokens;

    while (current_char != '\0') {
        if (fqs::is_char_in(NUMBERS, current_char)) {
            tokens.push_back(make_number());
        } else if (fqs::is_char_in(LITERALS, current_char)) {
            tokens.push_back(make_literal());
        } else if (fqs::is_char_in(OPERATORS, current_char)) {
            tokens.push_back(make_operator());
        } else {
            position pos_start;
            pos_start = pos;
            char ch = current_char;
            advance();
            return fqs::illegal_char_error(pos_start, pos, std::string(1, ch));
        }
    }

    tokens.push_back(fqs::token(fqs::tt_eof, {}, pos, {}));
    return tokens;
}

fqs::token fqs::lexer::make_number() {
    std::stringstream ss;
    int result;
    fqs::position pos_start;
    pos_start = pos;

    while (fqs::is_char_in(NUMBERS, current_char)) {
        ss << current_char;
    }

    ss >> result;
    return fqs::token(fqs::tt_num, result, pos_start, pos);
}
