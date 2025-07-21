#include "calculator/parser_util.hpp"

#include <stdexcept>

namespace calculator {

    int precedence_in_stack(const std::string& op) {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/") return 2;
        if (op == "NEG") return 3;  // 負號優先順序最高
        if (op == "(") return 0;
        throw std::runtime_error("Invalid in-stack operator: " + op);
    }

    int precedence_out_stack(const std::string& op) {
        if (op == "+" || op == "-") return 1;
        if (op == "*" || op == "/") return 2;
        if (op == "NEG") return 4;  // NEG 在出堆疊時優先順序較高
        if (op == "(") return 5;
        throw std::runtime_error("Invalid out-stack operator: " + op);
    }

    bool is_unary_minus(const std::vector<Token>& tokens, size_t index) {
        // 如果不是負號，那肯定不是一元負號
        if (tokens[index].type != TokenType::OPERATOR || tokens[index].value != "-") {
            return false;
        }
        // 特例，如果是第一個 token，則一定是一元負號，例如 "-5"
        if (index == 0) return true;
        // 看前一個 token 是否為運算子或左括號
        TokenType prev_type = tokens[index - 1].type;
        // 例如 (-3) 或 4 + -5
        return prev_type == TokenType::OPERATOR || prev_type == TokenType::LPAREN;
    }

}  // namespace calculator