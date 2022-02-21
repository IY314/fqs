#pragma once

#define TT_LENGTH 16
#define LT_LENGTH 32
#define OT_LENGTH 32

#define NULL_TOK -1

namespace fqs::tt {
enum TokenType {
    TT_INT,  // 0
    TT_FLOAT,
    TT_STRING,
    TT_LIT,
    TT_OP,
    TT_AOP,  // 5
    TT_SEMICOLON,
    TT_KEYWORD,
    TT_IDENTIFIER,
    TT_EOF,
    TT_NULL  // 10
};

enum LiteralType {
    LT_COMMENT = TT_LENGTH,  // 16
    LT_STARTMULTILINE,
    LT_RETURN,
    LT_LPAREN,
    LT_RPAREN,  // 20
    LT_LBRACKET,
    LT_RBRACKET,
    LT_LBRACE,
    LT_RBRACE,
    LT_COLON,  // 25
    LT_DOLLAR,
    LT_OCTOTHORPE  // 27
};

enum OperatorType {
    OT_DOUBLESTAR = TT_LENGTH + LT_LENGTH,  // 48
    OT_EQUALS,
    OT_NOTEQUALS,  // 50
    OT_LESSEQUALS,
    OT_GREATEREQUALS,
    OT_AND,
    OT_OR,
    OT_LSHIFT,  // 55
    OT_RSHIFT,
    OT_PLUS,
    OT_DASH,
    OT_STAR,
    OT_SLASH,  // 60
    OT_MOD,
    OT_ASSIGN,
    OT_BANG,
    OT_LANGLE,
    OT_RANGLE,  // 65
    OT_BITAND,
    OT_BITOR,
    OT_BITXOR  // 68
};

enum AssignOpType {
    AOT_LSHIFT = TT_LENGTH + LT_LENGTH + OT_LENGTH,  // 80
    AOT_RSHIFT,
    AOT_ADD,
    AOT_SUB,
    AOT_MUL,
    AOT_DIV,  // 85
    AOT_MOD,
    AOT_BITAND,
    AOT_BITOR,
    AOT_BITXOR  // 89
};

enum Keyword {
    KW_MODULE,
    KW_DEFINE,
    KW_FUNCTION,
    KW_RETURN,
    KW_STRUCT,
    KW_OBJECT
};
}  // namespace fqs::tt
