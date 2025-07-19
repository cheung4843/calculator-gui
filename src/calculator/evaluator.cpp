#include "calculator/evaluator.h"
#include <stack>
#include <stdexcept>

namespace calculator
{

    Evaluator::Evaluator(std::vector<Token> &postfix_tokens)
        : postfix_tokens_(postfix_tokens) {}

    void Evaluator::set_postfix(const std::vector<Token> &postfix_tokens)
    {
        postfix_tokens_ = postfix_tokens;
    }
    double Evaluator::evaluate() const
    {
        std::stack<double> num_st;

        for (const auto &token : postfix_tokens_)
        {
            if (token.type == TokenType::NUMBER)
            {
                num_st.push(std::stod(token.value));
            }
            else if (token.type == TokenType::OPERATOR)
            {
                if (num_st.size() < 2)
                {
                    throw std::runtime_error("Too few operands for operator");
                }

                double rhs = num_st.top();
                num_st.pop();
                double lhs = num_st.top();
                num_st.pop();
                double result = 0.0;

                if (token.value == "+")
                {
                    result = lhs + rhs;
                }
                else if (token.value == "-")
                {
                    result = lhs - rhs;
                }
                else if (token.value == "*")
                {
                    result = lhs * rhs;
                }
                else if (token.value == "/")
                {
                    if (rhs == 0.0)
                        throw std::runtime_error("Division by zero");
                    result = lhs / rhs;
                }
                else
                {
                    throw std::runtime_error("Unknown operator: " + token.value);
                }

                num_st.push(result);
            }
        }

        if (num_st.size() != 1)
        {
            throw std::runtime_error("Invalid postfix expression");
        }

        return num_st.top();
    }

}
