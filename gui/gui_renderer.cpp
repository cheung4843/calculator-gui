// gui_renderer.cpp
#include "gui_renderer.hpp"
#include <imgui.h>
#include <cstring>
#include <unordered_set>
#include <GLFW/glfw3.h>
#include <sstream>
#include <iomanip>

GuiRenderer::GuiRenderer(calculator::Calculator& calculator) : calculator_(calculator) {}

void GuiRenderer::render() {
    constexpr float button_w = 80.0f;
    constexpr float button_h = 60.0f;
    constexpr int button_per_row = 4;

    float width = button_per_row * button_w + (button_per_row - 1) * 10.0f + 20;
    float height = 8 * button_h + 150.0f;

    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);

    ImGui::Begin("Calculator", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoScrollbar);

    ImGui::Text("Ans = %.6f", last_result_);

    static char input_buf[256];
    std::strncpy(input_buf, input_.c_str(), sizeof(input_buf));
    input_buf[sizeof(input_buf) - 1] = '\0';

    if (ImGui::InputText("##display", input_buf, sizeof(input_buf))) {
        input_ = input_buf;
        just_evaluated_ = false;
    }

    // 鍵盤快捷鍵支援
    ImGuiIO& io = ImGui::GetIO();
    if (ImGui::IsWindowFocused()) {
        if (ImGui::IsKeyPressed(ImGuiKey_Enter) || ImGui::IsKeyPressed(ImGuiKey_KeypadEnter)) {
            evaluate_expression();
        } else if (ImGui::IsKeyPressed(ImGuiKey_Backspace)) {
            if (!input_.empty()) input_.pop_back();
        } else if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
            clear_input();
        }
    }

    // 函式與括號按鈕
    const std::vector<const char*> extra_buttons = {"(",   ")",   "sin",   "cos",
                                                    "tan", "log", "log10", "sqrt"};

    int i = 0;
    for (const char* label : extra_buttons) {
        if (ImGui::Button(label, ImVec2(button_w, button_h))) {
            handle_button(label);
        }
        if ((++i) % button_per_row != 0) {
            ImGui::SameLine();
        }
    }

    // 數字與運算子按鈕
    const std::vector<const char*> buttons = {"7", "8", "9", "+", "4", "5", "6",  "-",   "1",  "2",
                                              "3", "*", "0", ".", "=", "/", "CE", "Ans", "del"};

    i = 0;
    for (const char* label : buttons) {
        std::string lbl(label);
        if (lbl == "=") {
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.20f, 0.70f, 0.30f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.30f, 0.85f, 0.40f, 1.00f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.10f, 0.60f, 0.20f, 1.00f));
        }

        if (ImGui::Button(label, ImVec2(button_w, button_h))) {
            handle_button(label);
        }

        if (lbl == "=") {
            ImGui::PopStyleColor(3);
        }

        if ((++i) % button_per_row != 0) {
            ImGui::SameLine();
        }
    }

    ImGui::End();
}

std::string format_result(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << value;
    return oss.str();
}

void GuiRenderer::handle_button(const char* label) {
    static const std::unordered_set<std::string> functions = {"sin", "cos",   "tan",
                                                              "log", "log10", "sqrt"};

    std::string lbl(label);

    if (lbl == "=") {
        evaluate_expression();
    } else if (lbl == "CE") {
        clear_input();
    } else if (lbl == "Ans") {
        input_ += std::to_string(last_result_);
        just_evaluated_ = false;
    } else if (lbl == "del") {
        if (!input_.empty()) {
            input_.pop_back();
        }
    } else if (lbl == "+" || lbl == "-" || lbl == "*" || lbl == "/") {
        if (just_evaluated_) {
            input_ = format_result(last_result_);
            just_evaluated_ = false;
        }
        input_ += lbl;
    } else if (functions.count(lbl)) {
        input_ += lbl + "(";
        just_evaluated_ = false;
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
        input_ = format_result(last_result_);
        just_evaluated_ = true;
    } catch (...) {
        input_ = "Error";
    }
}

void GuiRenderer::clear_input() {
    input_.clear();
    just_evaluated_ = false;
}
