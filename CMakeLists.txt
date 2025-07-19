cmake_minimum_required(VERSION 3.16)
project(calculator-cli)

set(CMAKE_CXX_STANDARD 20)

# =============================
# Include paths
# =============================

# 讓你可以寫 #include "calculator/xxx.h"
include_directories(include)

# =============================
# Catch2 靜態函式庫（編譯一次）
# =============================
add_library(catch2 STATIC third_party/catch_amalgamated.cpp)
target_include_directories(catch2 PUBLIC third_party)

# =============================
# 測試共用主入口（定義 CATCH_CONFIG_MAIN）
# =============================
add_library(test_main OBJECT test/test_main.cpp)
target_include_directories(test_main PUBLIC third_party)

# =============================
# 主程式
# =============================
add_executable(calculator
  app/main.cpp
  src/calculator/tokenizer.cpp
  src/calculator/parser.cpp
  src/calculator/parser_util.cpp
  src/calculator/evaluator.cpp
  src/calculator/calculator.cpp
)

# =============================
# 單元測試：Calculator
# =============================
add_executable(test_calculator
  $<TARGET_OBJECTS:test_main>
  test/test_calculator.cpp
  src/calculator/tokenizer.cpp
  src/calculator/parser.cpp
  src/calculator/parser_util.cpp
  src/calculator/evaluator.cpp
  src/calculator/calculator.cpp
)
target_link_libraries(test_calculator PRIVATE catch2)

# =============================
# 單元測試：Tokenizer
# =============================
add_executable(test_tokenizer
  $<TARGET_OBJECTS:test_main>
  test/test_tokenizer.cpp
  src/calculator/tokenizer.cpp
)
target_link_libraries(test_tokenizer PRIVATE catch2)

# =============================
# 單元測試：Parser
# =============================
add_executable(test_parser
  $<TARGET_OBJECTS:test_main>
  test/test_parser.cpp
  src/calculator/tokenizer.cpp
  src/calculator/parser.cpp
  src/calculator/parser_util.cpp
)
target_link_libraries(test_parser PRIVATE catch2)

# =============================
# 單元測試：Evaluator
# =============================
add_executable(test_evaluator
  $<TARGET_OBJECTS:test_main>
  test/test_evaluator.cpp
  src/calculator/evaluator.cpp
)
target_link_libraries(test_evaluator PRIVATE catch2)

# =============================
# UNIX 系統下可能需要 pthread
# =============================
if(UNIX)
  target_link_libraries(test_calculator pthread)
  target_link_libraries(test_tokenizer pthread)
  target_link_libraries(test_parser pthread)
  target_link_libraries(test_evaluator pthread)
endif()
