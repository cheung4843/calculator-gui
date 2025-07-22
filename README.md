# 🧮 calculator-repl

一個用現代 C++ 開發的命令列科學計算機，支援變數、函式、REPL 模式與完整單元測試。  
採用模組化設計（Tokenizer / Parser / Evaluator / Calculator），並使用 Catch2 進行單元測試。

此版本基於 [calculator-cli](https://github.com/cheung4843/calculator-cli) 進行重構與擴展，並加入 REPL 功能。

---

## 🚀 快速開始

### 系統需求

- C++20 編譯器（如 GCC 11+ / MSVC 2022+ / Clang 13+）
- CMake 3.16+
- PowerShell（建議用於開發腳本）
- MinGW (若在 Windows 開發)

---

### 📦 安裝與建置

1. 先 clone 專案：

```bash
git clone https://github.com/cheung4843/calculator-repl.git
cd calculator-repl
```

2. 執行建置腳本（支援增量編譯與目標選擇）：

```powershell
./build.ps1
```

3. 執行主程式（REPL 模式）：

```powershell
./run.ps1
```

---

## 💡 支援語法與功能

- 四則運算：`+`, `-`, `*`, `/`
- 括號處理：`(2 + 3) * 4`
- 科學記號：`1.2e5`, `3E-8`
- 一元負號：`-5`, `x = -3`
- 變數儲存與呼叫：`x = 5`, `x + 2`
- 單參數函式：`sqrt(x)`, `abs(x)`, `log(x)`, `sin(x)`...
- REPL 指令：
  - `.vars`：顯示目前變數表
  - `.clear`：清除所有變數
  - `.help`：顯示說明
  - `exit` / `quit`：離開程式

---

## 🧪 單元測試

所有模組皆具備 Catch2 單元測試，並已涵蓋：
- Tokenizer：數字、運算子、括號、錯誤字元
- Parser：中序轉後序、括號錯誤處理、函式
- Evaluator：後序求值、變數、函式、例外
- Calculator：整合測試、錯誤拋出

執行所有測試：

```powershell
./test.ps1
```

或手動執行特定測試：

```powershell
./build/test_tokenizer.exe
./build/test_calculator.exe
```

---

## 📁 專案結構

```
calculator-repl/
├── app/                # 主程式入口 main.cpp
├── include/            # 公開 header（calculator_core 封裝）
├── src/                # Tokenizer / Parser / Evaluator / REPL 實作
├── test/               # Catch2 單元測試
├── third_party/        # Catch2 單檔框架
├── build.ps1           # 建構腳本（支援增量與互動選單）
├── run.ps1             # 快速編譯並執行 calculator 主程式
├── test.ps1            # 自動執行所有測試
├── CMakeLists.txt      # 專案建構設定
└── docs/
    └── UML.md          # 類別結構圖（Mermaid 格式）
```

📘 [View UML Diagram](docs/UML.md)

---

## 📐 設計理念

- **模組分離**：Tokenizer / Parser / Evaluator / Calculator 分工清楚，易於維護與測試
- **REPL 包裝**：使用 Calculator 作為門面類別，整合 Tokenizer/Parser/Evaluator 與變數表
- **函式庫重用**：核心邏輯抽出為 `calculator_core`，REPL / GUI 皆可共用
- **現代 C++ 實作**：`auto`, `string_view`, `unordered_map`, `std::function`
- **測試導向**：每個模組皆具備單元測試與錯誤處理測試

---

## ✨ 下一步規劃

- 支援多參數函式：如 `pow(x, y)`
- 自定函式與函式別名：`f(x) = x * 2`
- `.save` / `.load`：儲存與還原變數環境
- GUI/Web 版封裝：使用 calculator_core

---

## 🙌 作者

Created with 💻 by [Cheung4843](https://github.com/cheung4843)
