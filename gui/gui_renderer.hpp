// gui_renderer.hpp
#pragma once

#include "calculator/calculator.hpp"

#include <string>
  // 引入計算核心類別

class GuiRenderer {
 public:
  explicit GuiRenderer(calculator::Calculator& calculator);  // 建構子，注入 Calculator

  // 每一幀呼叫此函式進行繪製
  void render();

 private:
  calculator::Calculator& calculator_;        // 計算邏輯的核心
  std::string input_;             // 使用者目前輸入的表達式
  double last_result_ = 0;        // Ans：上一個計算結果
  bool just_evaluated_ = false;   // 是否剛剛按下 =

  // 處理按鈕被點擊的事件
  void handle_button(const char* label);

  // 運算並更新 Ans
  void evaluate_expression();

  // 清除目前輸入
  void clear_input();
};
