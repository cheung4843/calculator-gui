#include "calculator/calculator.hpp"

#include "catch_amalgamated.hpp"

using namespace calculator;

TEST_CASE("Valid numeric expression", "[Calculator]") {
    Calculator calc;
    REQUIRE(calc.compute("3.14") == Catch::Approx(3.14));
}

TEST_CASE("Invalid expression throws", "[Calculator]") {
    Calculator calc;
    REQUIRE_THROWS_AS(calc.compute("Shawn is handsome"), std::runtime_error);
}
