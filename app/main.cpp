#include "calculator/tokenizer.h"
#include "calculator/parser.h"
#include "calculator/evaluator.h"

#include <iostream>
#include <string>

using namespace calculator;

int main()
{
  std::cout << "Welcome to calculator-cli!\n";
  std::cout << "Type an expression (e.g., 3 + 5 * (2 - 1)) or type 'exit' to quit.\n";

  std::string input;
  Tokenizer tokenizer;
  Parser parser;
  Evaluator evaluator;

  while (true)
  {
    std::cout << "\n> ";
    std::getline(std::cin, input);

    if (input == "exit" || input == "quit")
    {
      std::cout << "Goodbye! \n";
      break;
    }

    try
    {
      tokenizer.set_input(input);
      auto tokens = tokenizer.tokenize();

      parser.set_tokens(tokens);
      auto postfix = parser.to_postfix();

      evaluator.set_postfix(postfix);
      double result = evaluator.evaluate();

      std::cout << "Result = " << result << "\n";
    }
    catch (const std::exception &e)
    {
      std::cerr << "Error: " << e.what() << "\n";
    }
  }

  return 0;
}
