#pragma once

#include <string>
#include <variant>
#include <vector>

#include "errors.hh"
#include "token.hh"

namespace fqs::lex {
struct Lexer {
   public:
    typedef std::variant<std::vector<token::Token>, fqs::err::FQSError>
        LexerResult;
    Lexer(const std::string& fn, const std::string& text);

    LexerResult makeTokens();

   private:
    std::string fn, text;
    pos::Pos currentPos;
    char currentChar;
    void advance();

    token::Token makeNumber();
    token::Token makeString(char quote);
    token::Token makeIdentifier();
    token::Token makeLiteral();
};
}  // namespace fqs::lex
