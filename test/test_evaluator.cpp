#include "catch_amalgamated.hpp"
#include "calculator/evaluator.h"
#include "calculator/token.h"

using namespace calculator;

TEST_CASE("Evaluator basic operations", "[Evaluator]")
{

    SECTION("10 2 *")
    {
        std::vector<Token> tokens = {
            {TokenType::NUMBER, "10"},
            {TokenType::NUMBER, "2"},
            {TokenType::OPERATOR, "*"}};
        Evaluator evaluator(tokens);
        REQUIRE(evaluator.evaluate() == Catch::Approx(20.0));
    }

    SECTION("3 5 +")
    {
        std::vector<Token> tokens = {
            {TokenType::NUMBER, "3"},
            {TokenType::NUMBER, "5"},
            {TokenType::OPERATOR, "+"}};
        Evaluator evaluator(tokens);
        REQUIRE(evaluator.evaluate() == Catch::Approx(8.0));
    }

    SECTION("7 2 -")
    {
        std::vector<Token> tokens = {
            {TokenType::NUMBER, "7"},
            {TokenType::NUMBER, "2"},
            {TokenType::OPERATOR, "-"}};
        Evaluator evaluator(tokens);
        REQUIRE(evaluator.evaluate() == Catch::Approx(5.0));
    }

    SECTION("Division by zero")
    {
        std::vector<Token> tokens = {
            {TokenType::NUMBER, "8"},
            {TokenType::NUMBER, "0"},
            {TokenType::OPERATOR, "/"}};
        Evaluator evaluator(tokens);
        REQUIRE_THROWS_AS(evaluator.evaluate(), std::runtime_error);
    }
}
