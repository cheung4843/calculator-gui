#pragma once

#include <string>

namespace calculator
{

  // Token 的類型：數字、運算子、括號
  enum class TokenType
  {
    NUMBER,   // 例如：12, 3.14
    OPERATOR, // 例如：+ - * /
    LPAREN,   // (
    RPAREN    // )
  };

  // 表示一個 token 單位
  struct Token
  {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string &v)
        : type(t), value(v) {}
  };

} // namespace calculator
