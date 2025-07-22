#pragma once

#include <string>

#include "calculator.hpp"

namespace calculator {
    class CalculatorRepl {
        public:
            CalculatorRepl();
            void run();

        private:
            calculator::Calculator calc_;
            bool handle_command(const std::string& input);
            bool is_exit_command(const std::string& input) const;
    };

}  // namespace calculator