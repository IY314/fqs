#include "parser.h"
#include "token.h"
#include "node.h"
#include "util.h"
#include <vector>
#include <variant>
#include <optional>
#include <functional>

fqs::parse_result::parse_result()
                               : nd({}), error({}) {}

std::variant<fqs::node, fqs::token> fqs::parse_result::register_(std::variant<fqs::node, fqs::parse_result, fqs::token> res) {
    if (std::get_if<fqs::parse_result>(&res) != nullptr) {
        fqs::parse_result pr_res = std::get<fqs::parse_result>(res);
        if (pr_res.error) {
            error = pr_res.error;
        }
        if (pr_res.nd) return pr_res.nd.value();
    }
    if (std::get_if<fqs::node>(&res) == nullptr) {
        return std::get<fqs::token>(res);
    } else {
        return std::get<fqs::node>(res);
    }
}

fqs::parse_result fqs::parse_result::success(fqs::node node) {
    nd = node;
    return *this;
}

fqs::parse_result fqs::parse_result::failure(fqs::base_error err) {
    error = err;
    return *this;
}

fqs::parser::parser(fqs::vec_token _tokens)
                   : tokens(_tokens), tok_idx(-1), current_tok({}) {
    advance();
}

fqs::token fqs::parser::advance() {
    tok_idx++;
    if (tok_idx < tokens.size()) {
        current_tok = tokens[tok_idx];
    }

    return current_tok.value();
}

fqs::parse_result fqs::parser::parse() {
    fqs::parse_result res = expr();

    if (!res.error && current_tok.value().type != tt_eof) {
        return res.failure(invalid_syntax_error(
            current_tok.value().pos_start, current_tok.value().pos_end,
            "Expected '+', '-', '*', or '/'"
        ));
    }

    return res;
}

fqs::parse_result fqs::parser::bin_op(std::function<fqs::parse_result(fqs::parser *)> func, std::vector<fqs::operator_type> ops) {
    fqs::parse_result res;
    fqs::node left = std::get<fqs::node>(res.register_(func(this)));
    if (res.error) return res;

    while (current_tok && current_tok.value().value && fqs::is_elem_in<fqs::operator_type>(ops, std::get<fqs::operator_type>(current_tok.value().value.value()))) {
        fqs::token op_tok = current_tok.value();
        res.register_(advance());
        fqs::node right = std::get<fqs::node>(res.register_(func(this)));
        if (res.error) return res;
        left = fqs::bin_op_node(left, op_tok, right);
    }

    return res.success(left);
}

fqs::parse_result fqs::parser::expr() {
    return bin_op(&fqs::parser::term, std::vector{fqs::ot_plus, fqs::ot_minus});
}

fqs::parse_result fqs::parser::term() {
    return bin_op(&fqs::parser::factor, std::vector{fqs::ot_mul, fqs::ot_div});
}

fqs::parse_result fqs::parser::factor() {
    fqs::parse_result res;
    fqs::token tok = current_tok.value();

    if (tok.type == fqs::tt_op && fqs::is_elem_in<fqs::operator_type>(std::vector(fqs::ot_plus, fqs::ot_minus), std::get<fqs::operator_type>(tok.value.value()))) {
        res.register_(advance());
        fqs::node factor_node = std::get<fqs::node>(res.register_(factor()));
        if (res.error) return res;
        return res.success(fqs::unary_op_node(tok, factor_node));
    } else if (tok.type == fqs::tt_num) {
        res.register_(advance());
        return res.success(fqs::num_node(tok));
    } else if (tok.type == fqs::tt_lit && std::get<fqs::literal_type>(tok.value.value()) == fqs::lt_lparen) {
        res.register_(advance());
        fqs::node expr_node = std::get<fqs::node>(res.register_(expr()));
        if (res.error) return res;
        if (current_tok.value().type == fqs::tt_lit && std::get<fqs::literal_type>(current_tok.value().value.value()) == fqs::lt_rparen) {
            res.register_(advance());
            return res.success(expr_node);
        } else {
            return res.failure(invalid_syntax_error(
                current_tok.value().pos_start, current_tok.value().pos_end,
                "Expected ')'"
            ));
        }
    } else {
        return res.failure(invalid_syntax_error(
            tok.pos_start, tok.pos_end,
            "Expected number"
        ));
    }
}
