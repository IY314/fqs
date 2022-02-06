#include <vector>

#include "token.hh"
#include "util.hh"

fqs::token::Token::Token(fqs::token::TokenType type, const fqs::pos::Pos& pos) {
    init(type, 0, pos);
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

fqs::token::Token::operator bool() const { return type != fqs::token::TT_NULL; }

bool fqs::token::Token::isKeyword(const std::string& identifier) {
    std::vector<std::string> keywords{"module", "define", "function",
                                      "return", "struct", "object"};
    return util::veccontains(keywords, identifier);
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
