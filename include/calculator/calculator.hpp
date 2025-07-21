#pragma once

#include "tokenizer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"
#include <string_view>

namespace calculator
{

  class Calculator
  {
  public:
    Calculator() = default;

    // 主計算介面
    double compute(std::string_view expression);

  private:
    Tokenizer tokenizer_;
    Parser parser_;
    Evaluator evaluator_;
  };

} // namespace calc
