#include <stack>
#include <stdexcept>
#include <cmath>

#include "calculator/evaluator.hpp"

namespace calculator {

    Evaluator::Evaluator(std::unordered_map<std::string, double> &variables)
        : variables_(variables) {}

    void Evaluator::set_postfix(const std::vector<Token> &postfix_tokens) {
        postfix_tokens_ = postfix_tokens;
    }

    double Evaluator::evaluate() const {
        std::stack<double> num_st;

        for (size_t i = 0; i < postfix_tokens_.size(); ++i) {
            const auto &token = postfix_tokens_[i];

            if (token.type == TokenType::NUMBER) {
                num_st.push(std::stod(token.value));

            } else if (token.type == TokenType::IDENTIFIER) {
                // x = 3 => 3 x STORE
                // 🔍 判斷是否為 STORE 的目標（即下一個 token 是 STORE）
                bool is_store_target = (i + 1 < postfix_tokens_.size()) &&
                                       (postfix_tokens_[i + 1].type == TokenType::OPERATOR) &&
                                       (postfix_tokens_[i + 1].value == "STORE");

                if (is_store_target) {
                    // 是賦值目標（左值），不需要查表，讓 STORE 處理
                    continue;
                }

                // 查找變數表
                // 如果變數不存在，則拋出錯誤
                auto it = variables_.find(token.value);
                if (it == variables_.end()) {
                    throw std::runtime_error("Undefined variable: " + token.value);
                }
                num_st.push(it->second);

            } else if (token.type == TokenType::FUN) {
                if (num_st.empty()) throw std::runtime_error("Missing argument for function");
                double arg = num_st.top();
                num_st.pop();

                auto it = builtins_.find(token.value);
                if (it == builtins_.end()) {
                    throw std::runtime_error("Unknown function: " + token.value);
                }

                double result = it->second(arg);
                num_st.push(result);
            } else if (token.type == TokenType::OPERATOR) {
                if (token.value == "NEG") {
                    if (num_st.empty()) {
                        throw std::runtime_error("NEG operator missing operand (e.g., '-x')");
                    }
                    double operand = num_st.top();
                    num_st.pop();
                    num_st.push(-operand);

                } else if (token.value == "STORE") {
                    if (num_st.empty()) {
                        throw std::runtime_error("STORE missing value");
                    }

                    double value = num_st.top();
                    num_st.pop();

                    // 確保前一個是 IDENTIFIER
                    if (i < 1 || postfix_tokens_[i - 1].type != TokenType::IDENTIFIER) {
                        throw std::runtime_error("STORE must follow a variable");
                    }

                    auto varname = postfix_tokens_[i - 1].value;
                    variables_[varname] = value;

                    num_st.push(value);  // 賦值結果也回傳
                    // ❗ 注意 : 目前僅支援一層賦值，例如 x = 5 或 y = x + 3
                    // 像 x = y = 4 這種右結合賦值不支援
                    // 若要支援需改為：4 y STORE x STORE 的 postfix，需額外設計 parser 遞迴處理
                } else {
                    if (num_st.size() < 2) {
                        throw std::runtime_error("Too few operands for operator");
                    }

                    double rhs = num_st.top();
                    num_st.pop();
                    double lhs = num_st.top();
                    num_st.pop();
                    double result = 0.0;

                    if (token.value == "+") {
                        result = lhs + rhs;
                    } else if (token.value == "-") {
                        result = lhs - rhs;
                    } else if (token.value == "*") {
                        result = lhs * rhs;
                    } else if (token.value == "/") {
                        if (rhs == 0.0) throw std::runtime_error("Division by zero");
                        result = lhs / rhs;
                    } else {
                        throw std::runtime_error("Unknown operator: " + token.value);
                    }

                    num_st.push(result);
                }
            }
        }

        if (num_st.size() != 1) {
            throw std::runtime_error("Invalid postfix expression");
        }

        return num_st.top();
    }

}  // namespace calculator
