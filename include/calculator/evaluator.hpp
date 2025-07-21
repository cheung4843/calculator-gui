#pragma once
#include <vector>

#include "token.hpp"

namespace calculator {
    class Evaluator {
        public:
            Evaluator() = default;
            explicit Evaluator(std::vector<Token> &postfix_tokens);

            void set_postfix(const std::vector<Token> &postfix_tokens);
            double evaluate() const;

        private:
            std::vector<Token> postfix_tokens_;
    };

}  // namespace calculator