#pragma once

#include "token.hpp"
#include <vector>

namespace calculator
{

  class Parser
  {
  public:
    // 預設建構子，可能用於測試或其他情況
    Parser() = default;
    // 建構子：接收 tokenizer 結果
    explicit Parser(std::vector<Token> &tokens);

    // 設定 tokens，這樣可以在測試中使用
    void set_tokens(const std::vector<Token> &tokens);

    // 回傳後綴表示法 (Postfix) 的 token list
    std::vector<Token> to_postfix();

  private:
    std::vector<Token> tokens_;
  };

} // namespace calculator
