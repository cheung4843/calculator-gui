#include "calculator/calculator.hpp"

#include "catch_amalgamated.hpp"

using namespace calculator;

TEST_CASE("Variable assignment and usage", "[Calculator]") {
    Calculator calc;
    REQUIRE(calc.compute("x = 10") == Catch::Approx(10.0));
    REQUIRE(calc.compute("x + 5") == Catch::Approx(15.0));
}

TEST_CASE("Function calls in expression", "[Calculator]") {
    Calculator calc;
    REQUIRE(calc.compute("sqrt(16) + cos(0)") == Catch::Approx(5.0));
}
