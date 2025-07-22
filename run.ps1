# 確保進入 build 資料夾
if (-Not (Test-Path build)) {
  Write-Host "❌ 尚未建立 build 資料夾，請先執行 build.ps1 並完成 CMake 設定"
  exit 1
}
cd build

# 編譯 calculator target
Write-Host "🔧 正在編譯 calculator..."
mingw32-make -j8 calculator

if ($LASTEXITCODE -ne 0) {
  Write-Host "❌ 編譯失敗，請檢查錯誤訊息"
  exit 1
}

# 執行主程式
Write-Host "`n🚀 執行 calculator.exe"
./calculator.exe

# 返回專案根目錄
Set-Location ..
