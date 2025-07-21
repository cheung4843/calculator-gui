#include <stdexcept>

#include "calculator/parser_util.hpp"

namespace calculator {

    int precedence_in_stack(const std::string &op) {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/") return 2;
        if (op == "(") return 0;
        throw std::runtime_error("Invalid in-stack operator: " + op);
    }

    int precedence_out_stack(const std::string &op) {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/") return 2;
        if (op == "(") return 3;
        throw std::runtime_error("Invalid out-stack operator: " + op);
    }

    bool is_operator(const std::string &op) {
        return op == "+" || op == "-" || op == "*" || op == "/";
    }

}  // namespace calculator
