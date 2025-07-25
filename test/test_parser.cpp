#include <string>
#include <vector>

#include "calculator/parser.hpp"
#include "calculator/tokenizer.hpp"

#include "catch_amalgamated.hpp"

using namespace calculator;

// 輔助函式：把 Token list 的 value 拿出來組成字串陣列
std::vector<std::string> extract_values(const std::vector<Token> &tokens) {
    std::vector<std::string> result;
    for (const auto &token : tokens) {
        result.push_back(token.value);
    }
    return result;
}

TEST_CASE("Infix to Postfix: 3 + 4 * 2 / ( 1 - 5 )", "[Parser]") {
    std::string expr = "3 + 4 * 2 / ( 1 - 5 )";
    Tokenizer tokenizer(expr);
    auto tokens = tokenizer.tokenize();

    Parser parser(tokens);
    auto postfix = parser.to_postfix();

    auto values = extract_values(postfix);
    std::vector<std::string> expected = {"3", "4", "2", "*", "1", "5", "-", "/", "+"};

    REQUIRE(values == expected);
}

TEST_CASE("Infix to Postfix: ( 2 + 3 ) * 4", "[Parser]") {
    std::string expr = "(2 + 3) * 4";
    Tokenizer tokenizer(expr);
    auto tokens = tokenizer.tokenize();

    Parser parser(tokens);
    auto postfix = parser.to_postfix();

    auto values = extract_values(postfix);
    std::vector<std::string> expected = {"2", "3", "+", "4", "*"};

    REQUIRE(values == expected);
}

TEST_CASE("Mismatched parentheses throws", "[Parser]") {
    std::string expr = "(1 + 2";
    Tokenizer tokenizer(expr);
    auto tokens = tokenizer.tokenize();

    Parser parser(tokens);
    REQUIRE_THROWS_AS(parser.to_postfix(), std::runtime_error);
}

TEST_CASE("Function call is handled", "[Parser]") {
    std::string expr = "sin(1)";
    Tokenizer tokenizer(expr);
    auto tokens = tokenizer.tokenize();
    Parser parser(tokens);
    auto postfix = parser.to_postfix();
    auto values = extract_values(postfix);
    std::vector<std::string> expected = {"1", "sin"};
    REQUIRE(values == expected);
}

TEST_CASE("Unary minus, varibables and Function", "[Parser]") {
    std::string expr = "y = -sin(x)";
    Tokenizer tokenizer(expr);
    auto tokens = tokenizer.tokenize();
    Parser parser(tokens);
    auto postfix = parser.to_postfix();
    auto values = extract_values(postfix);
    std::vector<std::string> expected = {"x", "sin", "NEG", "y", "STORE"};
    REQUIRE(values == expected);
}
