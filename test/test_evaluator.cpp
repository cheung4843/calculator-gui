
#include <unordered_map>

#include "calculator/evaluator.hpp"
#include "calculator/token.hpp"

#include "catch_amalgamated.hpp"

using namespace calculator;

TEST_CASE("Evaluator basic operations", "[Evaluator]") {
    std::unordered_map<std::string, double> variables;
    Evaluator evaluator(variables);
    SECTION("10 2 *") {
        std::vector<Token> tokens = {
            {TokenType::NUMBER, "10"}, {TokenType::NUMBER, "2"}, {TokenType::OPERATOR, "*"}};
        evaluator.set_postfix(tokens);
        REQUIRE(evaluator.evaluate() == Catch::Approx(20.0));
    }

    SECTION("3 5 +") {
        std::vector<Token> tokens = {
            {TokenType::NUMBER, "3"}, {TokenType::NUMBER, "5"}, {TokenType::OPERATOR, "+"}};
        evaluator.set_postfix(tokens);
        REQUIRE(evaluator.evaluate() == Catch::Approx(8.0));
    }

    SECTION("7 2 -") {
        std::vector<Token> tokens = {
            {TokenType::NUMBER, "7"}, {TokenType::NUMBER, "2"}, {TokenType::OPERATOR, "-"}};
        evaluator.set_postfix(tokens);
        REQUIRE(evaluator.evaluate() == Catch::Approx(5.0));
    }

    SECTION("Division by zero") {
        std::vector<Token> tokens = {
            {TokenType::NUMBER, "8"}, {TokenType::NUMBER, "0"}, {TokenType::OPERATOR, "/"}};
        evaluator.set_postfix(tokens);
        REQUIRE_THROWS_AS(evaluator.evaluate(), std::runtime_error);
    }

    SECTION("Handles variables correctly") {
        variables["x"] = 2.0;
        std::vector<Token> tokens = {
            {TokenType::IDENTIFIER, "x"}, {TokenType::NUMBER, "3"}, {TokenType::OPERATOR, "*"}};
        evaluator.set_postfix(tokens);
        REQUIRE(evaluator.evaluate() == Catch::Approx(6.0));
    }

    SECTION("Assignment operation") {
        variables["y"] = 0.0;
        std::vector<Token> tokens = {
            {TokenType::NUMBER, "5"}, {TokenType::IDENTIFIER, "y"}, {TokenType::OPERATOR, "STORE"}};
        evaluator.set_postfix(tokens);
        REQUIRE(evaluator.evaluate() == Catch::Approx(5.0));
        REQUIRE(variables["y"] == Catch::Approx(5.0));
    }

    SECTION("Function evaluation") {
        std::vector<Token> tokens = {{TokenType::NUMBER, "9"}, {TokenType::FUN, "sqrt"}};
        evaluator.set_postfix(tokens);
        REQUIRE(evaluator.evaluate() == Catch::Approx(3.0));
    }
}
