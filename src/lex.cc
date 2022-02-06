#include <sstream>

#include "lex.hh"
#include "util.hh"

#define DIGITS "0123456789"
#define LETTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

fqs::lex::Lexer::Lexer(const std::string& fn, const std::string& text) {
    this->fn = fn;
    this->text = text;
    currentPos = fqs::pos::Pos{-1, 0, -1, fn, text};
    currentChar = '\0';
    advance();
}

std::vector<fqs::token::Token> fqs::lex::Lexer::makeTokens() {
    std::vector<fqs::token::Token> tokens;

    while (currentChar != '\0') {
        if (util::strcontains(" \t", currentChar))
            advance();
        else if (util::strcontains(DIGITS, currentChar))
            tokens.push_back(makeNumber());
        else {
            // TODO
        }
    }
}

void fqs::lex::Lexer::advance() {
    currentPos.advance(currentChar);
    currentChar = currentPos.idx < text.size() ? text[currentPos.idx] : '\0';
}

fqs::token::Token fqs::lex::Lexer::makeNumber() {
    std::ostringstream result;
    bool isFloat = false;
    fqs::pos::Pos posStart = currentPos.copy();

    while (util::strcontains(std::strcat(DIGITS, "."), currentChar)) {
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

fqs::token::Token fqs::lex::Lexer::makeString(const char& quote) {
    std::ostringstream result;
    bool escaped = false;
    fqs::pos::Pos posStart = currentPos.copy();

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
}

fqs::token::Token fqs::lex::Lexer::makeIdentifier() {
    std::ostringstream result;
    fqs::pos::Pos posStart = currentPos.copy();

    while (util::strcontains(std::strcat(std::strcat(LETTERS, DIGITS), "_"),
                             currentChar)) {
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
