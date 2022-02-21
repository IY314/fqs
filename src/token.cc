#include <sstream>
#include <vector>

#include "token.hh"
#include "util.hh"

fqs::token::Token::Token(fqs::token::TokenType type, const fqs::pos::Pos& pos) {
    init(type, NULL_TOK, pos);
}

fqs::token::Token::Token(fqs::token::TokenType type,
                         const fqs::token::TokenValue& value,
                         const fqs::pos::Pos& pos) {
    init(type, value, pos);
}

fqs::token::Token::Token(fqs::token::TokenType type,
                         const fqs::token::TokenValue& value,
                         const fqs::pos::Pos& posStart,
                         const fqs::pos::Pos& posEnd) {
    init(type, value, posStart, posEnd);
}
std::string fqs::token::Token::str() const {
    std::ostringstream result;
    result << type;
    if (const auto* v = std::get_if<long>(&value)) {
        if (*v == NULL_TOK) {
            return result.str();
        } else {
            result << ':' << *v;
            return result.str();
        }
    } else if (const auto* v = std::get_if<std::string>(&value)) {
        result << ':' << *v;
        return result.str();
    } else if (const auto* v = std::get_if<double>(&value)) {
        result << ':' << *v;
        return result.str();
    } else {
        return "";
    }
}

fqs::token::Token::operator bool() const { return type != fqs::token::TT_NULL; }

bool fqs::token::Token::isKeyword(const std::string& identifier) {
    return util::veccontains(
        {"module", "define", "function", "return", "struct", "object"},
        identifier);
}

void fqs::token::Token::setValues(fqs::token::TokenType type,
                                  const fqs::token::TokenValue& value,
                                  const fqs::pos::Pos& posStart) {
    this->type = type;
    this->value = value;
    this->posStart = posStart;
}

void fqs::token::Token::init(fqs::token::TokenType type,
                             const fqs::token::TokenValue& value,
                             const fqs::pos::Pos& pos) {
    setValues(type, value, pos);
    posEnd = pos;
    posEnd.advance();
}

void fqs::token::Token::init(fqs::token::TokenType type,
                             const fqs::token::TokenValue& value,
                             const fqs::pos::Pos& posStart,
                             const pos::Pos& posEnd) {
    setValues(type, value, posStart);
    this->posEnd = posEnd;
}
