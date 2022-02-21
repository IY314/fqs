#pragma once

#include <string>
#include <variant>

#include "pos.hh"
#include "tt.hh"

namespace fqs::token {
typedef std::variant<std::string, long, double> TokenValue;

struct Token {
   public:
    tt::TokenType type;
    TokenValue value;
    pos::Pos posStart, posEnd;

    Token(tt::TokenType type, const pos::Pos& pos);

    Token(tt::TokenType type, const TokenValue& value, const pos::Pos& pos);

    Token(tt::TokenType type, const TokenValue& value, const pos::Pos& posStart,
          const pos::Pos& posEnd);

    std::string str() const;

    operator bool() const;

    static bool isKeyword(const std::string& identifier);

   private:
    void setValues(tt::TokenType type, const TokenValue& value,
                   const pos::Pos& posStart);

    void init(tt::TokenType type, const TokenValue& value, const pos::Pos& pos);

    void init(tt::TokenType type, const TokenValue& value,
              const pos::Pos& posStart, const pos::Pos& posEnd);
};
}  // namespace fqs::token
