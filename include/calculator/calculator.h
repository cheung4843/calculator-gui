#pragma once

#include <string>

namespace calculator
{

  class Calculator
  {
  public:
    Calculator() = default;
    ~Calculator() = default;

    // 傳入字串表達式，回傳數值結果
    double evaluate(const std::string &expression);
  };

} // namespace calculator
