#pragma once

#include "calculator/token.h"
#include <string>
#include <vector>

namespace calculator
{

    class Tokenizer
    {
    public:
        Tokenizer() = default; // 預設建構子，可能用於測試或其他情況
        explicit Tokenizer(std::string &expr);

        void set_input(const std::string &expr);
        std::vector<Token> tokenize();

    private:
        // 儲存輸入的數學表達式，例如 "1 + 2"
        std::string expr_;
        // 掃描目前讀到的字元位置（像滑鼠游標）
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

} // namespace calculator
