#include <sstream>
#include "lex.hh"
#include "util.hh"

#define DIGITS "0123456789"
#define LETTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define LITOPCHARS "+-*/%()[]{}=!<>&|^:$#"

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
        if (util::strcontains(" \t\n", currentChar))
            advance();
        else if (currentChar == ';') {
            tokens.push_back(
                fqs::token::Token(fqs::tt::TT_SEMICOLON, currentPos));
            advance();
        } else if (util::strcontains(DIGITS, currentChar))
            tokens.push_back(makeNumber());
        else if (util::strcontains("'\"", currentChar))
            tokens.push_back(makeString(currentChar));
        else if (util::strcontains(LETTERS, currentChar))
            tokens.push_back(makeIdentifier());
        else if (util::strcontains(LITOPCHARS, currentChar)) {
            const fqs::token::Token& tok = makeLiteral();
            if (!tok) {
                return fqs::err::FQSUnknownLitError(
                    tok.posStart, tok.posEnd, std::get<std::string>(tok.value));
            }
            const auto type = std::get<long>(tok.value);
            const fqs::pos::Pos start(currentPos);
            bool hasStar = false;
            switch (type) {
                case fqs::tt::LT_COMMENT:
                    while (currentChar != '\0') {
                        advance();
                        if (currentChar == '\n') {
                            advance();
                            break;
                        }
                    }
                    break;
                case fqs::tt::LT_STARTMULTILINE:
                    while (true) {
                        advance();
                        if (currentChar == '*' && !hasStar) {
                            hasStar = true;
                        } else if (currentChar == '/' && hasStar) {
                            advance();
                            break;
                        } else if (currentChar == '\0')
                            return fqs::err::FQSUnclosedCommentError(
                                start, currentPos);
                        else
                            hasStar = false;
                    }
                    break;
                default:
                    tokens.push_back(tok);
                    break;
            }
        } else {
            const fqs::pos::Pos posStart(currentPos);
            char ch = currentChar;
            advance();
            return fqs::err::FQSIllegalCharError(posStart, currentPos, {1, ch});
        }
    }

    tokens.push_back(fqs::token::Token(fqs::tt::TT_EOF, currentPos));
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
        return fqs::token::Token(fqs::tt::TT_FLOAT,
                                 std::strtod(result.str().c_str(), nullptr),
                                 posStart, currentPos);
    return fqs::token::Token(fqs::tt::TT_INT,
                             std::strtol(result.str().c_str(), nullptr, 10),
                             posStart, currentPos);
}

fqs::token::Token fqs::lex::Lexer::makeString(char quote) {
    std::ostringstream result;
    bool escaped = false;
    const fqs::pos::Pos& posStart(currentPos);

    advance();

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
        else if (currentChar == quote) {
            advance();
            break;
        } else
            result << currentChar;
        advance();
    } while (currentChar != '\0');

    advance();

    return fqs::token::Token(fqs::tt::TT_STRING, result.str(), posStart,
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
        return fqs::token::Token(fqs::tt::TT_KEYWORD, identifier, posStart,
                                 currentPos);
    return fqs::token::Token(fqs::tt::TT_IDENTIFIER, identifier, posStart,
                             currentPos);
}

fqs::token::Token fqs::lex::Lexer::makeLiteral() {
    std::ostringstream result;
    const fqs::pos::Pos& posStart(currentPos);
    fqs::pos::Pos posSnapshot(currentPos);
    long bestValue = 0;
    fqs::tt::TokenType type;
    std::vector<std::string> literals{"//", "/*", ":>", "(", ")", "[",
                                      "]",  "{",  "}",  ":", "$", "#"},
        operators{
            "**", "==", "!=", "<=", ">=", "&&", "||", "<<", ">>", "+", "-",
            "*",  "/",  "%",  "=",  "!",  "<",  ">",  "&",  "|",  "^",
        },
        assignops{
            "<<=", ">>=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=",
        };
    while (util::strcontains(LITOPCHARS, currentChar)) {
        result << currentChar;
        auto it = std::find(literals.begin(), literals.end(), result.str());
        if (it != literals.end()) {
            bestValue = TT_LENGTH + (it - literals.begin());
            posSnapshot = currentPos;
            type = fqs::tt::TT_LIT;
        } else if ((it = std::find(operators.begin(), operators.end(),
                                   result.str())) != operators.end()) {
            bestValue = TT_LENGTH + LT_LENGTH + (it - operators.begin());
            posSnapshot = currentPos;
            type = fqs::tt::TT_OP;
        } else if ((it = std::find(assignops.begin(), assignops.end(),
                                   result.str())) != assignops.end()) {
            bestValue =
                TT_LENGTH + LT_LENGTH + OT_LENGTH + (it - assignops.begin());
            posSnapshot = currentPos;
            type = fqs::tt::TT_AOP;
        }
        advance();
    }

    if (bestValue) {
        currentPos = posSnapshot;
        advance();
        return fqs::token::Token(type, bestValue, posStart, currentPos);
    } else
        return fqs::token::Token(fqs::tt::TT_NULL, result.str(), posStart,
                                 currentPos);
}
