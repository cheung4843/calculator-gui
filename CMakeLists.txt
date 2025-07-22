cmake_minimum_required(VERSION 3.16)
project(calculator-cli)

set(CMAKE_CXX_STANDARD 20)

# =============================
# Include paths
# =============================
include_directories(core/include)

# =============================
# Catch2 測試框架
# =============================
add_library(catch2 STATIC third_party/catch/catch_amalgamated.cpp)
target_include_directories(catch2 PUBLIC third_party/catch)

add_library(test_main OBJECT test/test_main.cpp)
target_include_directories(test_main PUBLIC third_party/catch)

# =============================
# Calculator 核心函式庫
# =============================
add_library(calculator_core STATIC
  core/src/calculator/tokenizer.cpp
  core/src/calculator/parser.cpp
  core/src/calculator/parser_util.cpp
  core/src/calculator/evaluator.cpp
  core/src/calculator/calculator.cpp
)
target_include_directories(calculator_core PUBLIC core/include)

# =============================
# CLI 主程式（REPL）
# =============================
add_executable(calculator_cli
  cli/cli_main.cpp
  cli/repl.cpp
)
target_link_libraries(calculator_cli PRIVATE calculator_core)

# =============================
# GUI 主程式（ImGui + GLFW）
# =============================
add_subdirectory(gui)
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/glfw third_party/glfw-build)

# =============================
# 單元測試
# =============================
add_executable(test_calculator
  $<TARGET_OBJECTS:test_main>
  test/test_calculator.cpp
)
target_link_libraries(test_calculator PRIVATE catch2 calculator_core)

add_executable(test_tokenizer
  $<TARGET_OBJECTS:test_main>
  test/test_tokenizer.cpp
)
target_link_libraries(test_tokenizer PRIVATE catch2 calculator_core)

add_executable(test_parser
  $<TARGET_OBJECTS:test_main>
  test/test_parser.cpp
)
target_link_libraries(test_parser PRIVATE catch2 calculator_core)

add_executable(test_evaluator
  $<TARGET_OBJECTS:test_main>
  test/test_evaluator.cpp
)
target_link_libraries(test_evaluator PRIVATE catch2 calculator_core)

# =============================
# UNIX 下 pthread
# =============================
if(UNIX)
  target_link_libraries(test_calculator pthread)
  target_link_libraries(test_tokenizer pthread)
  target_link_libraries(test_parser pthread)
  target_link_libraries(test_evaluator pthread)
endif()
