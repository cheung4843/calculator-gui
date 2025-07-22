#include <iostream>

#include <calculator/repl.hpp>
#include <calculator/calculator.hpp>

namespace calculator {
    void CalculatorRepl::run() {
        std::cout << "Welcome to calculator-repl! tpye '.vars' to show all variables\n";
        std::cout << "Type an expression (e.g., 4 + 8 * (4 - 3)) or type 'exit' to quit.\n";

        Calculator calc;
        std::string input;

        while (true) {
            std::cout << "\n> ";
            std::getline(std::cin, input);

            if (!handle_input(input)) {
                break;
            }
            // 顯示所有變數
            if (input == ".vars") {
                const auto& vars = calc.get_variables();
                if (vars.empty()) {
                    std::cout << "(no variables defined)\n";
                } else {
                    std::cout << "Variables:\n";
                    for (const auto& [name, value] : vars) {
                        std::cout << name << " = " << value << "\n";
                    }
                }
                continue;
            }

            try {
                double result = calc.compute(input);
                std::cout << result << "\n";
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        }
    }

    bool CalculatorRepl::handle_input(const std::string& input) const {
        if (input == "exit" || input == "quit") {
            std::cout << "Goodbye!\n";
            return false;
        }
        return true;
    }

}  // namespace calculator