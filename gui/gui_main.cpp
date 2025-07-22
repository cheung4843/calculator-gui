// gui_main.cpp
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "calculator/calculator.hpp"
#include "gui_renderer.hpp"

int main() {
    // 初始化 GLFW
    if (!glfwInit()) return -1;

    // 指定 OpenGL 版本與 Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 計算 GUI 大小（與 gui_renderer.cpp 中一致）
    constexpr int button_w = 80;
    constexpr int button_h = 60;
    constexpr int cols = 4;
    constexpr int rows = 5;
    constexpr int padding = 10;

    int gui_width = cols * button_w + (cols - 1) * padding + 20;
    int gui_height = rows * button_h + 200;

    // 建立與 GUI 尺寸一致的 GLFW 視窗
    GLFWwindow* window = glfwCreateWindow(gui_width, gui_height, "Calculator", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // 啟用 VSync

    // 初始化 ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // 初始化 Calculator 與 GUI
    calculator::Calculator calculator;
    GuiRenderer gui(calculator);

    // 主迴圈
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        gui.render();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // 結束清理
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}