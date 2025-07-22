#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <cmath>

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
            // 內建單參數函式的 function table
            // inline static 是為了避免在每次使用時都重新定義這個 map
            inline static const std::unordered_map<std::string, std::function<double(double)>>
                builtins_ = {
                    {"abs", [](double x) { return std::abs(x); }},
                    {"sqrt", [](double x) { return std::sqrt(x); }},
                    {"log", [](double x) { return std::log(x); }},
                    {"log10", [](double x) { return std::log10(x); }},
                    {"exp", [](double x) { return std::exp(x); }},
                    {"sin", [](double x) { return std::sin(x); }},
                    {"cos", [](double x) { return std::cos(x); }},
                    {"tan", [](double x) { return std::tan(x); }},
            };
    };

}  // namespace calculator