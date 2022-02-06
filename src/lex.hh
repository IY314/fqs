#ifndef FQS_LEX_HH
#define FQS_LEX_HH

#include <string>
#include <vector>

#include "token.hh"

namespace fqs::lex {
struct Lexer {
   public:
    Lexer(const std::string& fn, const std::string& text);

    std::vector<token::Token> makeTokens();

   private:
    std::string fn, text;
    pos::Pos currentPos;
    char currentChar;
    void advance();

    token::Token makeNumber();
    token::Token makeString(const char& quote);
    token::Token makeIdentifier();
    token::Token makeLiteral();
};
}  // namespace fqs::lex

#endif /* FQS_LEX_HH */
