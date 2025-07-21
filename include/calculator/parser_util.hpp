#pragma once

#include <string>
#include <vector>

#include "token.hpp"

namespace calculator {

    // 回傳堆疊內部的優先順序
    int precedence_in_stack(const std::string &op);

    // 回傳輸入進來的優先順序
    int precedence_out_stack(const std::string &op);

    // 檢查是否為合法運算子
    bool is_operator(const std::string &op);

    // 判斷是否是一元負號
    bool is_unary_minus(const std::vector<Token> &tokens, size_t index);

}  // namespace calculator
