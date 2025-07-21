#pragma once

#include <string>
#include <vector>

#include "token.hpp"

namespace calculator {

    class Tokenizer {
        public:
            Tokenizer() = default;  // 預設建構子，可能用於測試或其他情況
            explicit Tokenizer(std::string_view expr);

            void set_input(std::string_view expr);
            std::vector<Token> tokenize();

        private:
            // 表達式字串，使用 std::string_view 以避免不必要的複製
            std::string_view expr_;
            // 掃描目前讀到的字元位置（像滑鼠游標）F
            size_t pos_;

            // 取得目前字元但不移動位置
            char peek() const;
            // 取得目前字元並移動位置
            char get();
            // 忽略空白，這就像掃地機器人看到空白會自動略過不清
            void skip_whitespace();
            // 解析一個「數字 token」
            Token parse_number();
    };

}  // namespace calculator
