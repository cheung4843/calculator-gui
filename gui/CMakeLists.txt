# GUI 專案 CMake 子模組

# ImGui source files
set(IMGUI_SOURCES
  ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui.cpp
  ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui_draw.cpp
  ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui_widgets.cpp
  ${CMAKE_SOURCE_DIR}/third_party/imgui/imgui_tables.cpp
  ${CMAKE_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_glfw.cpp
  ${CMAKE_SOURCE_DIR}/third_party/imgui/backends/imgui_impl_opengl3.cpp
)

# ImGui headers
include_directories(
  ${CMAKE_SOURCE_DIR}/third_party/imgui
  ${CMAKE_SOURCE_DIR}/third_party/imgui/backends
)

# GUI 執行檔
add_executable(calculator_gui
  gui_main.cpp
  gui_renderer.cpp     # ✅ 加入 GUI 控制類別
  ${IMGUI_SOURCES}
)

# Include calculator headers
target_include_directories(calculator_gui PRIVATE
  ${CMAKE_SOURCE_DIR}/core/include
)

# Link required libraries
target_link_libraries(calculator_gui
  PRIVATE
    calculator_core     # ✅ 記得在 core/CMakeLists.txt 宣告此 target
    glfw
    ${CMAKE_DL_LIBS}
    opengl32            # ✅ Windows 用 OpenGL
)
