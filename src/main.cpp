/*
#include <iostream>
#include <vector>
#include <string>
#include <variant>
#include <sstream>
#include <optional>

using namespace std;

bool char_in(const char *str, char ch) {
    return string(str).find(ch) != string::npos;
}

class position {
    public:
    int idx, ln, col;
    string fn, ftxt;

    position(int _idx, int _ln, int _col, string _fn, string _ftxt)
            : idx{_idx}, ln{_ln}, col{_col}, fn{_fn}, ftxt{_ftxt} {}
    
    position() = default;

    void advance(char current_char = '\0') {
        idx++;
        col++;

        if (current_char == '\n') {
            ln++;
            col = 0;
        }
    }

    void operator=(position pos) {
        idx = pos.idx;
        ln = pos.ln;
        col = pos.col;
        fn = pos.fn;
        ftxt = pos.ftxt;
    }
};

enum token_type {
    tt_num,
    tt_lit,
    tt_op,
    tt_eof
};

enum literal_type {
    lt_lparen,
    lt_rparen
};

enum operator_type {
    ot_plus,
    ot_minus,
    ot_mul,
    ot_div
};

typedef variant<nullptr_t, int, string, literal_type, operator_type> token_value;

class token {
    public:
    token_type type;
    token_value value;
    position pos_start, pos_end;

    token(token_type type, token_value value, position pos_start, optional<position> pos_end) {
        this->type = type;
        this->value = value;
        this->pos_start = pos_start;
        this->pos_end = pos_start;
        this->pos_end.advance();
        if (pos_end.has_value()) {
            this->pos_end = pos_end.value();
        }
    }

    string to_string() {
        stringstream ss;
        switch (type) {
            case tt_num:
            ss << "NUM:" << get<int>(value);
            break;
            case tt_lit:
            ss << "LIT:" << get<char>(value);
            break;
            case tt_op:
            ss << "OP:" << get<string>(value);
            break;
            case tt_eof:
            ss << "EOF";
            break;
            default:
            break;
        }
        return ss.str();
    }
};

class lexer {
    public:
    lexer(string _fn, string _text)
         : fn{_fn}, text{_text} {
        pos = position(-1, 0, -1, fn, text);
        current_char = '\0';
        advance();
    }

    vector<token> make_tokens() {
        vector<token> tokens;

        while (current_char != '\0') {
            if (char_in(NUMBERS, current_char)) {
                tokens.push_back(make_number());
            } else if (char_in(LITERALS, current_char)) {
                tokens.push_back(make_literal());
            }
        }

        return tokens;
    }

    private:
    string fn, text;
    position pos;
    char current_char;

    static inline const char *NUMBERS = "0123456789";
    static inline const char *LITERALS = "()";
    static inline const char *OPERATORS = "+-*\";

    void advance() {
        pos.advance();
        current_char = pos.idx < text.size() ? text[pos.idx] : '\0';
    }

    token make_number() {
        stringstream ss;
        int result;
        position pos_start;
        pos_start = pos;

        while (current_char != '\0' && char_in(NUMBERS, current_char)) {
            ss << current_char;
        }

        ss >> result;
        return token(tt_num, result, pos_start, pos);
    }

    token make_literal() {
        stringstream ss;
        string result;
        position pos_start;
        pos_start = pos;

        while (current_char != '\0' && char_in(LITERALS, current_char)) {
            ss << current_char;
        }

        result = ss.str();
        if (result == "(") {
            return token(tt_lit, lt_lparen, pos_start, {});
        } else if (result == ")") {
            return token(tt_lit, lt_rparen, pos_start, {});
        }
    }
};
*/

#include "build_code.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::cout << "fqs > ";
    std::string text;
    std::getline(std::cin, text);
    fqs::run(std::string("<stdin>"), text);
}
