#include "calculator/calculator.h"
#include <stdexcept>
#include <string>
#include <sstream>

// 目前未整合入程式碼中，因為 main 直接串接三大模組了
namespace calculator
{

    double Calculator::evaluate(const std::string &expression)
    {
        // ⚠️ 簡化版本：只做字串轉 double
        // 之後會改為解析表達式（例如四則運算）
        std::stringstream ss(expression);
        double value;
        ss >> value;

        if (ss.fail() || !ss.eof())
        {
            throw std::runtime_error("Invalid expression (parser not implemented yet)");
        }

        return value;
    }

} // namespace calculator
