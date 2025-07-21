#include "calculator/calculator.hpp"

namespace calculator {

double Calculator::compute(std::string_view expression) {
  tokenizer_.set_input(expression);
  std::vector<Token> tokens = tokenizer_.tokenize();

  parser_.set_tokens(tokens);
  std::vector<Token> postfix = parser_.to_postfix();

  evaluator_.set_postfix(postfix);
  return evaluator_.evaluate();
}

}  // namespace calculator
