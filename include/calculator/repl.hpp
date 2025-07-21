#pragma once

#include <string>

namespace calculator {
    class CalculatorRepl {
        public:
            void run();

        private:
            bool handle_input(const std::string& input) const;
    };

}  // namespace calculator