#include <iostream>  //debug
#include "calculator/calculator.hpp"

namespace calculator {

    // 初始化 Evaluator 時需要傳入變數表
    Calculator::Calculator() : evaluator_(variables_) {}

    const std::unordered_map<std::string, double> &Calculator::get_variables() const {
        return variables_;
    }

    // Facade Pattern
    double Calculator::compute(std::string_view expression) {
        tokenizer_.set_input(expression);
        std::vector<Token> tokens = tokenizer_.tokenize();

        for (const auto &token : tokens) {
            std::cout << token.value << ' ';
        }
        std::cout << '\n';

        parser_.set_tokens(tokens);
        std::vector<Token> postfix = parser_.to_postfix();

        for (const auto &token : postfix) {
            std::cout << token.value << ' ';
        }
        std::cout << '\n';

        evaluator_.set_postfix(postfix);
        return evaluator_.evaluate();
    }

}  // namespace calculator
