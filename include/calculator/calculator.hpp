#pragma once

#include <string_view>

#include "evaluator.hpp"
#include "parser.hpp"
#include "tokenizer.hpp"

namespace calculator {

    class Calculator {
        public:
            Calculator() = default;

            // 主計算介面
            double compute(std::string_view expression);

        private:
            Tokenizer tokenizer_;
            Parser parser_;
            Evaluator evaluator_;
    };

}  // namespace calculator