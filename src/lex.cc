#include <sstream>

#include "lex.hh"
#include "util.hh"

#define DIGITS "0123456789"
#define LETTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LITCHARS "+-*/%()[]{}=!<>&|^:$#"

fqs::lex::Lexer::Lexer(const std::string& fn, const std::string& text)
    : currentPos(-1, 0, -1, fn, text) {
    this->fn = fn;
    this->text = text;
    currentChar = '\0';
    advance();
}

fqs::lex::Lexer::LexerResult fqs::lex::Lexer::makeTokens() {
    std::vector<fqs::token::Token> tokens;

    while (currentChar != '\0') {
        if (util::strcontains(" \t", currentChar))
            advance();
        else if (util::strcontains(DIGITS, currentChar))
            tokens.push_back(makeNumber());
        else if (util::strcontains("'\"", currentChar))
            tokens.push_back(makeString(currentChar));
        else if (util::strcontains(LETTERS, currentChar))
            tokens.push_back(makeIdentifier());
        else if (util::strcontains(LITCHARS, currentChar)) {
            const fqs::token::Token& tok = makeLiteral();
            if (!tok) {
                return fqs::err::FQSUnknownLitError(
                    tok.posStart, tok.posEnd, std::get<std::string>(tok.value));
            }
            tokens.push_back(tok);
        } else {
            const fqs::pos::Pos& posStart(currentPos);
            char ch = currentChar;
            advance();
            return fqs::err::FQSIllegalCharError(posStart, currentPos, {1, ch});
        }
    }

    tokens.push_back(fqs::token::Token(fqs::token::TT_EOF, currentPos));
    return tokens;
}

void fqs::lex::Lexer::advance() {
    currentPos.advance(currentChar);
    currentChar = ((std::string::size_type)currentPos.idx) < text.size()
                      ? text[currentPos.idx]
                      : '\0';
}

fqs::token::Token fqs::lex::Lexer::makeNumber() {
    std::ostringstream result;
    bool isFloat = false;
    const fqs::pos::Pos& posStart(currentPos);

    while (util::strcontains({DIGITS, "."}, currentChar)) {
        if (currentChar == '.') {
            if (isFloat) break;
            isFloat = true;
        }
        result << currentChar;
        advance();
    }

    if (isFloat)
        return fqs::token::Token(fqs::token::TT_FLOAT,
                                 std::strtod(result.str().c_str(), nullptr),
                                 posStart, currentPos);
    return fqs::token::Token(fqs::token::TT_INT,
                             std::strtol(result.str().c_str(), nullptr, 10),
                             posStart, currentPos);
}

fqs::token::Token fqs::lex::Lexer::makeString(char quote) {
    std::ostringstream result;
    bool escaped = false;
    const fqs::pos::Pos& posStart(currentPos);

    do {
        if (escaped) {
            switch (currentChar) {
                case '\\':
                    result << '\\';
                    break;
                case 'n':
                    result << '\n';
                    break;
                case 't':
                    result << '\t';
                    break;
                default:
                    result << currentChar;
                    break;
            }
            escaped = false;
        } else if (currentChar == '\\')
            escaped = true;
        else
            result << currentChar;
        advance();
    } while ((currentChar != quote) || escaped);

    return fqs::token::Token(fqs::token::TT_STRING, result.str(), posStart,
                             currentPos);
}

fqs::token::Token fqs::lex::Lexer::makeIdentifier() {
    std::ostringstream result;
    const fqs::pos::Pos& posStart(currentPos);

    while (util::strcontains({LETTERS, DIGITS, "_"}, currentChar)) {
        result << currentChar;
        advance();
    }

    std::string identifier = result.str();

    if (fqs::token::Token::isKeyword(identifier))
        return fqs::token::Token(fqs::token::TT_KEYWORD, identifier, posStart,
                                 currentPos);
    return fqs::token::Token(fqs::token::TT_IDENTIFIER, identifier, posStart,
                             currentPos);
}

fqs::token::Token fqs::lex::Lexer::makeLiteral() {
    std::ostringstream result;
    const fqs::pos::Pos& posStart(currentPos);

    while (util::strcontains(LITCHARS, currentChar)) {
        result << currentChar;
        advance();
    }

    std::string literal = result.str();
    std::vector<std::string> literals{
        "+",  "-",  "*",  "/",  "%",   "(",   ")",  "[", "]",  "{",
        "}",  "=",  "+=", "-=", "*=",  "/=",  "%=", "!", "==", "!=",
        "<",  ">",  "<=", ">=", "&&",  "||",  "&",  "|", "^",  "<<",
        ">>", "&=", "|=", "^=", "<<=", ">>=", ":>", ":", "$",  "#"};
    if (util::veccontains(literals, literal)) {
        long value;
        for (auto it = literals.begin(); it != literals.end(); ++it) {
            if (literal == *it) {
                value = TT_LENGTH + (it - literals.begin());
                return fqs::token::Token(fqs::token::TT_LIT, value, posStart,
                                         currentPos);
            }
        }
    }
    return fqs::token::Token(fqs::token::TT_NULL, literal, posStart,
                             currentPos);
}
