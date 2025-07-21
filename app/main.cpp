#include <iostream>
#include <string>

#include "calculator/calculator.hpp"

using namespace calculator;

int main() {
    std::cout << "Welcome to calculator-cli!\n";
    std::cout << "Type an expression (e.g., 3 + 5 * (2 - 1)) or type 'exit' to "
                 "quit.\n";

    Calculator calc;
    std::string input;

    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, input);

        if (input == "exit" || input == "quit") {
            std::cout << "Goodbye!\n";
            break;
        }

        try {
            double result = calc.compute(input);  // ← 改成只呼叫 compute()
            std::cout << "Result = " << result << "\n";
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}
