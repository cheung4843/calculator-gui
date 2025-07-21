#include "calculator/tokenizer.hpp"
#include <cctype>
#include <stdexcept>

namespace calculator
{

    Tokenizer::Tokenizer(std::string_view expr)
        : expr_(expr), pos_(0) {}

    void Tokenizer::set_input(const std::string_view expr)
    {
        expr_ = expr;
        pos_ = 0;
    }
    char Tokenizer::peek() const
    {
        if (pos_ < expr_.length())
            return expr_[pos_];
        return '\0';
    }

    char Tokenizer::get()
    {
        return pos_ < expr_.length() ? expr_[pos_++] : '\0';
    }

    void Tokenizer::skip_whitespace()
    {
        while (std::isspace(peek()))
            get();
    }

    Token Tokenizer::parse_number()
    {
        // 記下數字開始的位置
        size_t start = pos_;
        bool has_dot = false;
        // std::isdigit(peek()) 表是數字就繼續吃
        while (std::isdigit(peek()) || (!has_dot && peek() == '.'))
        {
            // 第一次遇到 . 允許，第二次就不允許
            if (peek() == '.')
                has_dot = true;
            get();
        }
        // 取出整段數字作為一個 Token，留意要將 string_view 轉換成 std::string
        return Token(TokenType::NUMBER, std::string(expr_.substr(start, pos_ - start)));
    }

    // 掃描整個表達式，把一連串字元分割成一顆顆 Token，方便後面分析與運算
    std::vector<Token> Tokenizer::tokenize()
    {
        std::vector<Token> tokens;
        // 只要還沒讀到字串結尾，就繼續掃描
        while (peek() != '\0')
        {
            // 跳過空白字元（空格、Tab、換行）
            skip_whitespace();
            // 取得目前字元
            char c = peek();

            //
            if (std::isdigit(c) || c == '.')
            {
                // 如果是數字或小數點
                tokens.push_back(parse_number());
            }
            else if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                // 如果是運算子，直接建立一個 OPERATOR Token
                // get() 把這個字元拿掉並前進
                // std::string(1, get()) → 把字元變成字串（因為 Token value 是 string）
                tokens.emplace_back(TokenType::OPERATOR, std::string(1, get()));
            }
            else if (c == '(')
            {
                get();
                tokens.emplace_back(TokenType::LPAREN, "(");
            }
            else if (c == ')')
            {
                get();
                tokens.emplace_back(TokenType::RPAREN, ")");
            }
            else if (c == '\0')
            {
                break;
            }
            else
            {
                // 若不是上述類型（數字、運算子、括號），就丟出錯誤（例如 $、#、中文等）
                throw std::runtime_error(std::string("Unknown character: ") + c);
            }
        }

        // 準備給 Parser
        return tokens;
    }

} // namespace calculator
