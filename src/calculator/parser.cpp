#include <stack>
#include <stdexcept>

#include "calculator/parser.hpp"
#include "calculator/parser_util.hpp"

namespace calculator {

    Parser::Parser(std::vector<Token> &tokens) : tokens_(tokens) {}

    void Parser::set_tokens(const std::vector<Token> &tokens) {
        tokens_ = tokens;
    }
    std::vector<Token> Parser::to_postfix() {
        std::vector<Token> output;
        std::stack<Token> op_st;

        // 支援變數賦值
        bool is_assignment = false;
        std::string assign_var;

        for (size_t i = 0; i < tokens_.size(); ++i) {
            const Token &token = tokens_[i];
            if (token.type == TokenType::NUMBER) {
                // 數字直接輸出
                output.push_back(token);
            } else if (token.type == TokenType::IDENTIFIER) {
                // 如果下一個 token 是 `=`，那就是賦值
                // 所以變數與賦值運算子是一起處理的
                if (i + 1 < tokens_.size() && tokens_[i + 1].type == TokenType::ASSIGN) {
                    is_assignment = true;      // 表示使用者輸入的是賦值運算式
                    assign_var = token.value;  // 把變數名記下來
                    ++i;                       // 跳過 `=`
                    continue;
                }
                // 否則就只是變數的參照
                output.push_back(token);
            } else if (token.type == TokenType::OPERATOR) {
                // 檢查是否為一元負號
                const Token &curr_token =
                    is_unary_minus(tokens_, i) ? Token(TokenType::OPERATOR, "NEG") : token;

                // 持續 pop 出 stack 中的運算子，直到遇到優先級較低的運算子或左括號
                while (!op_st.empty() && precedence_out_stack(curr_token.value) <=
                                             precedence_in_stack(op_st.top().value)) {
                    output.push_back(op_st.top());
                    op_st.pop();
                }
                op_st.push(curr_token);  // 新運算子進 stack
            } else if (token.type == TokenType::LPAREN) {
                op_st.push(token);
            } else if (token.type == TokenType::RPAREN) {
                // 將 stack 頂的運算子 pop 出直到遇到左括號
                while (!op_st.empty() && op_st.top().type != TokenType::LPAREN) {
                    output.push_back(op_st.top());
                    op_st.pop();
                }

                if (op_st.empty()) {
                    throw std::runtime_error("Mismatched parentheses: missing '('");
                }

                op_st.pop();  // 丟掉左括號
            }
        }

        // 將剩下的運算子 pop 出來
        while (!op_st.empty()) {
            if (op_st.top().type == TokenType::LPAREN || op_st.top().type == TokenType::RPAREN) {
                // 如果 stack 中還有括號，表示括號不匹配
                throw std::runtime_error("Mismatched parentheses");
            }

            output.push_back(op_st.top());
            op_st.pop();
        }

        // 若是變數賦值，加上 assign_var 與 OPERATOR STORE(只在 Parser 與 Evaluator 中使用)
        // 行為說明，例如 x = 3 + 4，Parser 會暫存 x，並跳過 =
        // 剩下的 3 + 4 照舊轉為 postfix: 3 4 +
        // 最後加上 x STORE，結果為: 3 4 + x STORE
        // 非賦值時 x + 2，直接當成變數參照處理
        if (is_assignment) {
            output.emplace_back(TokenType::IDENTIFIER, assign_var);
            output.emplace_back(TokenType::OPERATOR, "STORE");
        }

        return output;
    }

}  // namespace calculator
