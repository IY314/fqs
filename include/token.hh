#pragma once

#include <string>
#include <variant>

#include "pos.hh"

#define TT_LENGTH 16
#define LT_LENGTH 64

#define NULL_TOK -1

namespace fqs::token {
enum TokenType {
    TT_INT,
    TT_FLOAT,
    TT_STRING,
    TT_CHAR,
    TT_LIT,
    TT_SEMICOLON,
    TT_KEYWORD,
    TT_IDENTIFIER,
    TT_EOF,
    TT_NULL
};

enum LiteralType {
    LT_LSHIFTASSIGN = TT_LENGTH,  // 16
    LT_RSHIFTASSIGN,
    LT_ADDASSIGN,
    LT_SUBASSIGN,
    LT_DOUBLESTAR,  // 20
    LT_MULASSIGN,
    LT_COMMENT,
    LT_STARTMULTILINE,
    LT_DIVASSIGN,
    LT_MODASSIGN,  // 25
    LT_EQUALS,
    LT_NOTEQUALS,
    LT_LESSEQUALS,
    LT_GREATEREQUALS,
    LT_AND,  // 30
    LT_OR,
    LT_BITANDASSIGN,
    LT_BITORASSIGN,
    LT_BITXORASSIGN,
    LT_LSHIFT,  // 35
    LT_RSHIFT,
    LT_RETURN,
    LT_PLUS,
    LT_DASH,
    LT_STAR,  // 40
    LT_SLASH,
    LT_MOD,
    LT_LPAREN,
    LT_RPAREN,
    LT_LBRACKET,  // 45
    LT_RBRACKET,
    LT_LBRACE,
    LT_RBRACE,
    LT_ASSIGN,
    LT_BANG,  // 50
    LT_LANGLE,
    LT_RANGLE,
    LT_BITAND,
    LT_BITOR,
    LT_BITXOR,  // 55
    LT_COLON,
    LT_DOLLAR,
    LT_OCTOTHORPE  // 58
};

enum Keyword {
    KW_MODULE,
    KW_DEFINE,
    KW_FUNCTION,
    KW_RETURN,
    KW_STRUCT,
    KW_OBJECT
};

typedef std::variant<std::string, long, double> TokenValue;

struct Token {
   public:
    TokenType type;
    TokenValue value;
    pos::Pos posStart, posEnd;

    Token(TokenType type, const pos::Pos& pos);

    Token(TokenType type, const TokenValue& value, const pos::Pos& pos);

    Token(TokenType type, const TokenValue& value, const pos::Pos& posStart,
          const pos::Pos& posEnd);

    std::string str() const;

    operator bool() const;

    static bool isKeyword(const std::string& identifier);

   private:
    void setValues(TokenType type, const TokenValue& value,
                   const pos::Pos& posStart);

    void init(TokenType type, const TokenValue& value, const pos::Pos& pos);

    void init(TokenType type, const TokenValue& value, const pos::Pos& posStart,
              const pos::Pos& posEnd);
};
}  // namespace fqs::token
