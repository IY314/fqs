#include "token.h"
#include "position.h"
#include <optional>
#include <string>
#include <sstream>

fqs::token::token(fqs::token_type _type, fqs::token_value _value, fqs::position _pos_start, std::optional<fqs::position> _pos_end)
                 : type{_type}, value{_value}, pos_start{_pos_start} {
    if (_pos_end.has_value()) {
        pos_end = _pos_end.value();
    } else {
        pos_end = pos_start;
        pos_end.advance();
    }
}

std::string fqs::token::to_string() {
    std::stringstream ss;
    switch (type) {
        case tt_num:
        ss << "NUM:" << get<int>(value.value());
        break;
        case tt_lit:
        ss << "LIT:" << get<fqs::literal_type>(value.value());
        break;
        case tt_op:
        ss << "OP:" << get<fqs::operator_type>(value.value());
        break;
        case tt_eof:
        ss << "EOF";
        break;
        default:
        break;
    }
    return ss.str();
}
