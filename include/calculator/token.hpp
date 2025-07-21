#pragma once

#include <string>

namespace calculator {

    // Token 的類型：數字、運算子、括號
    enum class TokenType {
        NUMBER,    // 例如：12, 3.14
        OPERATOR,  // 例如：+, -, *, /, NEG(由 - 轉換而來，在 Parser 中生成), STORE(在 Parser
                   // 中生成)
        LPAREN,      // (
        RPAREN,      // )
        IDENTIFIER,  // 變數
        ASSIGN,      // 賦值運算子，例如：=

    };

    // 表示一個 token 單位
    struct Token {
            TokenType type;
            std::string value;

            Token(TokenType t, const std::string &v) : type(t), value(v) {}
    };

}  // namespace calculator
