#ifndef node_h
#define node_h

#include "token.h"
#include <string>

namespace fqs {
    class node {
        public:
        virtual std::string to_string();
    };

    class num_node : public node {
        public:
        token tok;

        num_node(token);
        std::string to_string();
    };

    class bin_op_node : public node {
        public:
        node left;
        token op_tok;
        node right;

        bin_op_node(node, token, node);
        std::string to_string();
    };

    class unary_op_node : public node {
        public:
        token op_tok;
        node nd;
        unary_op_node(token, node);
        std::string to_string();
    };
}

#endif
