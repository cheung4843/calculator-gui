// gui_renderer.cpp
#include "gui_renderer.hpp"
#include <imgui.h>
#include <cstring>

GuiRenderer::GuiRenderer(calculator::Calculator& calculator) : calculator_(calculator) {}

void GuiRenderer::render() {
    constexpr float button_w = 80.0f;
    constexpr float button_h = 60.0f;
    constexpr int button_per_row = 4;
    constexpr int button_rows = 5;

    float width = button_per_row * button_w + (button_per_row - 1) * 10.0f + 20;
    float height = button_rows * button_h + 150.0f;

    // 貼齊畫面左上角
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);

    // 移除標題列、邊框、拖曳功能
    ImGui::Begin("Calculator", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoScrollbar);

    ImGui::Text("Ans = %.2f", last_result_);

    static char input_buf[256];
    std::strncpy(input_buf, input_.c_str(), sizeof(input_buf));
    input_buf[sizeof(input_buf) - 1] = '\0';

    if (ImGui::InputText("##display", input_buf, sizeof(input_buf))) {
        input_ = input_buf;
        just_evaluated_ = false;
    }

    const std::vector<const char*> buttons = {"7", "8", "9", "+", "4", "5", "6", "-",  "1",
                                              "2", "3", "*", "0", ".", "=", "/", "CE", "Ans"};

    int i = 0;
    for (const char* label : buttons) {
        if (ImGui::Button(label, ImVec2(button_w, button_h))) {
            handle_button(label);
        }
        if ((++i) % button_per_row != 0) {
            ImGui::SameLine();
        }
    }

    ImGui::End();
}

void GuiRenderer::handle_button(const char* label) {
    std::string lbl(label);

    if (lbl == "=") {
        evaluate_expression();
    } else if (lbl == "CE") {
        clear_input();
    } else if (lbl == "Ans") {
        input_ += std::to_string(last_result_);
        just_evaluated_ = false;
    } else if (lbl == "+" || lbl == "-" || lbl == "*" || lbl == "/") {
        if (just_evaluated_) {
            input_ = std::to_string(last_result_);
            just_evaluated_ = false;
        }
        input_ += lbl;
    } else {
        if (just_evaluated_) {
            input_.clear();
            just_evaluated_ = false;
        }
        input_ += lbl;
    }
}

void GuiRenderer::evaluate_expression() {
    try {
        last_result_ = calculator_.compute(input_);
        input_ = std::to_string(last_result_);
        just_evaluated_ = true;
    } catch (...) {
        input_ = "Error";
    }
}

void GuiRenderer::clear_input() {
    input_.clear();
    just_evaluated_ = false;
}
