# Step 1: 檢查是否修改 CMakeLists.txt
$changed = Read-Host "是否有修改 CMakeLists.txt？(y/n)"

if ($changed -eq "y") {
  Write-Host "🔄 重新設定 CMake..."
  if (Test-Path build) {
    Remove-Item -Recurse -Force build
  }
  mkdir build | Out-Null
  cd build
  cmake ..
  if ($LASTEXITCODE -ne 0) {
    Write-Host "❌ CMake configure 失敗"
    exit 1
  }
}
else {
  Write-Host "🚀 執行增量編譯"
  cd build
}

# Step 2: 選擇要編譯的目標
Write-Host ""
Write-Host "🎯 請選擇要編譯的目標（可直接按 Enter 編譯全部）"
Write-Host "  [1] 全部目標"
Write-Host "  [2] calculator"
Write-Host "  [3] test_calculator"
Write-Host "  [4] test_tokenizer"
Write-Host "  [5] test_parser"
Write-Host "  [6] test_evaluator"

$choice = Read-Host "請輸入選項編號（1-6）"

switch ($choice) {
  "2" { $target = "calculator" }
  "3" { $target = "test_calculator" }
  "4" { $target = "test_tokenizer" }
  "5" { $target = "test_parser" }
  "6" { $target = "test_evaluator" }
  default { $target = "" }
}

# Step 3: 執行編譯
Write-Host ""
Write-Host "📦 開始編譯..."
if ($target -eq "") {
  mingw32-make -j8
}
else {
  mingw32-make -j8 $target
}

if ($LASTEXITCODE -eq 0) {
  Write-Host "`n✅ 編譯成功！"
}
else {
  Write-Host "`n❌ 編譯失敗，請檢查錯誤訊息。"
}

# 返回專案根目錄
Set-Location ..