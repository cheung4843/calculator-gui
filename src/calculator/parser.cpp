#include "calculator/parser.h"
#include "calculator/parser_util.h"
#include <stack>
#include <stdexcept>

namespace calculator
{

    Parser::Parser(std::vector<Token> &tokens)
        : tokens_(tokens) {}

    void Parser::set_tokens(const std::vector<Token> &tokens)
    {
        tokens_ = tokens;
    }
    std::vector<Token> Parser::to_postfix()
    {
        std::vector<Token> output;
        std::stack<Token> op_st;

        for (const auto &token : tokens_)
        {
            if (token.type == TokenType::NUMBER)
            {
                // 數字直接輸出
                output.push_back(token);
            }
            else if (token.type == TokenType::OPERATOR)
            {
                // 持續彈出 stack 中的運算子，直到遇到優先級較低的運算子或左括號
                while (!op_st.empty() && precedence_out_stack(token.value) <= precedence_in_stack(op_st.top().value))
                {
                    output.push_back(op_st.top());
                    op_st.pop();
                }
                op_st.push(token); // 新運算子進 stack
            }
            else if (token.type == TokenType::LPAREN)
            {
                op_st.push(token);
            }
            else if (token.type == TokenType::RPAREN)
            {
                // 將 stack 頂運算子彈出直到遇到左括號
                while (!op_st.empty() && op_st.top().type != TokenType::LPAREN)
                {
                    output.push_back(op_st.top());
                    op_st.pop();
                }

                if (op_st.empty())
                {
                    throw std::runtime_error("Mismatched parentheses: missing '('");
                }

                op_st.pop(); // 丟掉左括號
            }
        }

        // 將剩下的運算子彈出
        while (!op_st.empty())
        {
            if (op_st.top().type == TokenType::LPAREN || op_st.top().type == TokenType::RPAREN)
            {
                // 如果 stack 中還有括號，表示括號不匹配
                throw std::runtime_error("Mismatched parentheses");
            }

            output.push_back(op_st.top());
            op_st.pop();
        }

        return output;
    }

} // namespace calculator
