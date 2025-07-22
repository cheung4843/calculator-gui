#pragma once

#include <string>
#include "calculator/calculator.hpp"

namespace cli {
    class CalculatorRepl {
        public:
            CalculatorRepl();
            void run();

        private:
            calculator::Calculator calc_;
            bool handle_command(const std::string& input);
            bool is_exit_command(const std::string& input) const;
    };
}  // namespace cli
