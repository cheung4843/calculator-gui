#include "catch_amalgamated.hpp"
#include "calculator/tokenizer.hpp"

using namespace calculator;

TEST_CASE("Tokenizer returns expected tokens", "[Tokenizer]")
{
    std::string expr = "12 + 3.5 * (2 - 4)";
    Tokenizer tokenizer(expr);
    auto tokens = tokenizer.tokenize();

    REQUIRE(tokens.size() == 9);
    REQUIRE(tokens[0].type == TokenType::NUMBER);
    REQUIRE(tokens[0].value == "12");
    REQUIRE(tokens[1].type == TokenType::OPERATOR);
    REQUIRE(tokens[1].value == "+");
    REQUIRE(tokens[2].value == "3.5");
    REQUIRE(tokens[3].value == "*");
    REQUIRE(tokens[4].type == TokenType::LPAREN);
}
