#include "node.h"
#include "token.h"
#include <string>
#include <sstream>

std::string fqs::node::to_string() {
    return std::string("Node");
}

fqs::num_node::num_node(fqs::token _tok)
                       : tok(_tok) {}

std::string fqs::num_node::to_string() {
    return tok.to_string();
}

fqs::bin_op_node::bin_op_node(fqs::node _left, fqs::token _op_tok, fqs::node _right)
                             : left(_left), op_tok(_op_tok), right(_right) {}

std::string fqs::bin_op_node::to_string() {
    std::stringstream ss;
    ss << "(" << left.to_string() << ", " << op_tok.to_string() << ", " << right.to_string() << ")";
    return ss.str();
}

fqs::unary_op_node::unary_op_node(fqs::token _op_tok, fqs::node _nd)
                                 : op_tok(_op_tok), nd(_nd) {}

std::string fqs::unary_op_node::to_string() {
    std::stringstream ss;
    ss << "(" << op_tok.to_string() << ", " << nd.to_string() << ")";
    return ss.str();
}
