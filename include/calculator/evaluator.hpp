#pragma once

#include <vector>
#include <unordered_map>

#include "token.hpp"

namespace calculator {
    class Evaluator {
        public:
            Evaluator() = default;
            explicit Evaluator(std::unordered_map<std::string, double> &variables);

            void set_postfix(const std::vector<Token> &postfix_tokens);  // 在 compute() 中設
            double evaluate() const;

        private:
            std::vector<Token> postfix_tokens_;
            // 存放變數的的 symbol table，由外部傳入
            std::unordered_map<std::string, double> &variables_;
    };

}  // namespace calculator