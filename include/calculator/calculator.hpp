#pragma once

#include <string_view>

#include "evaluator.hpp"
#include "parser.hpp"
#include "tokenizer.hpp"

namespace calculator {

    class Calculator {
        public:
            Calculator(); // 要用自定義的建構子，因此不加 = default，因為還要初始化 evaluator_

            // 主計算介面
            double compute(std::string_view expression);

        private:
            std::unordered_map<std::string, double> variables_;  // symbol table
            Tokenizer tokenizer_;
            Parser parser_;
            Evaluator evaluator_;  // Evaluator 於建構子初始化
    };

}  // namespace calculator