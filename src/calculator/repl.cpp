#include <iostream>

#include <calculator/repl.hpp>
#include <calculator/calculator.hpp>

namespace calculator {

    CalculatorRepl::CalculatorRepl() : calc_() {}
    void CalculatorRepl::run() {
        std::cout << "Welcome to calculator-repl! tpye '.vars' to show all variables\n";
        std::cout << "Type an expression (e.g., 4 + 8 * (4 - 3)) or type 'exit' to quit.\n";

        std::string input;

        while (true) {
            std::cout << "\n> ";
            std::getline(std::cin, input);

            if (is_exit_command(input)) {
                std::cout << "Goodbye!\n";
                break;
            }

            if (handle_command(input)) {
                continue;  // 已處理特殊指令 .vars, .clear, .help
            }

            try {
                double result = calc_.compute(input);
                std::cout << result << "\n";
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << "\n";
            }
        }
    }

    bool CalculatorRepl::handle_command(const std::string& input) {
        if (input == ".help") {
            std::cout << "Calculator REPL Help\n"
                      << "Type any expression to evaluate, such as:\n"
                      << "  3 + 5 * (2 - 1)\n"
                      << "Use variables:\n"
                      << "  x = 5\n"
                      << "  y = sqrt(x)\n"
                      << "Special commands:\n"
                      << "  .vars    Show all variables\n"
                      << "  .clear   Clear all variables\n"
                      << "  .help    Show this help message\n"
                      << "  exit     Exit the program\n";
            return true;
        }

        if (input == ".vars") {
            const auto& vars = calc_.get_variables();
            if (vars.empty()) {
                std::cout << "(no variables defined)\n";
            } else {
                std::cout << "Variables:\n";
                for (const auto& [name, value] : vars) {
                    std::cout << name << " = " << value << "\n";
                }
            }
            return true;
        }

        if (input == ".clear") {
            calc_.clear_variables();
            std::cout << "All variables cleared.\n";
            return true;
        }

        return false;  // 非指令
    }
    bool CalculatorRepl::is_exit_command(const std::string& input) const {
        return input == "exit" || input == "quit";
    }

}  // namespace calculator