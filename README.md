# 🧮 calculator-cli

一個用現代 C++ 開發的命令列計算機，支援基本四則運算。  
採用模組化設計（Tokenizer / Parser / Evaluator），並使用 Catch2 進行單元測試。

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
git clone https://github.com/cheung4843/calculator-cli.git
cd calculator-cli
```

2. 執行建置腳本：

```powershell
./build.ps1
```

3. 執行主程式：

```bash
./build/calculator.exe
```

---

## 🧪 單元測試

執行所有測試：

```powershell
./test.ps1
```

或手動執行特定測試：

```bash
./build/test_calculator.exe
./build/test_tokenizer.exe
```

---

## 📁 專案結構

```
calculator-cli/
├── app/                # 主程式入口 main.cpp
├── include/            # 公開的 header 檔案
│   └── calculator/
├── src/                # 各模組的實作檔
│   └── calculator/
├── test/               # 單元測試
├── third_party/        # Catch2 單檔測試框架
├── build.ps1           # 智慧建構腳本（有判斷 CMakeLists.txt 是否變動）
├── test.ps1            # 自動執行所有測試
├── run.ps1             # 只建構並執行主程式(不執行測試)
├── CMakeLists.txt      # CMake 設定
├── README.md
└── docs/
    └── UML.md          # 類別結構圖（Mermaid 格式）
```

---

## 📐 設計理念

- **模組分離**：Tokenizer / Parser / Evaluator 分工清楚，易於維護與測試
- **可重複使用**：類別皆非 singleton，可透過 `set_expression()` 等方式重複使用
- **使用現代 C++**：幾乎皆用 `auto` 推導與 STL 容器
- **嚴謹測試**：每個模組都具備獨立單元測試

---

## ✨ 未來改進

- 支援函式、負號、浮點精度更高的運算
- 加入中序表示法直接求值
- 改為 REPL 模式
- 支援科學記號或更多 operator

---

## 🙌 作者

Created with 💻 by Cheung4843
