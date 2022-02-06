#ifndef FQS_TOKEN_HH
#define FQS_TOKEN_HH

#include <string>
#include <variant>

#include "pos.hh"

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
    TT_EOF
};

enum LiteralType {
    LT_PLUS = 16,
    LT_DASH,
    LT_STAR,
    LT_SLASH,
    LT_MOD,
    LT_LPAREN,
    LT_RPAREN,
    LT_LBRACKET,
    LT_RBRACKET,
    LT_LBRACE,
    LT_RBRACE,
    LT_ASSIGN,
    LT_ADDASSIGN,
    LT_SUBASSIGN,
    LT_MULASSIGN,
    LT_DIVASSIGN,
    LT_MODASSIGN,
    LT_BANG,
    LT_EQUALS,
    LT_NOTEQUALS,
    LT_LESSTHAN,
    LT_GREATERTHAN,
    LT_LESSEQUALS,
    LT_GREATEREQUALS,
    LT_AND,
    LT_OR,
    LT_BITAND,
    LT_BITOR,
    LT_BITXOR,
    LT_LSHIFT,
    LT_RSHIFT,
    LT_RETURN,
    LT_COLON,
    LT_REFDEF
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

    static bool isKeyword(const std::string& identifier);

   private:
    void setValues(TokenType type, const TokenValue& value,
                   const pos::Pos& posStart);

    void init(TokenType type, const TokenValue& value, const pos::Pos& pos);

    void init(TokenType type, const TokenValue& value, const pos::Pos& posStart,
              const pos::Pos& posEnd);
};
}  // namespace fqs::token

#endif /* FQS_TOKEN_HH */
