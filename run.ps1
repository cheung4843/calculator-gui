# run_main.ps1

$buildDir = "build"
$exeName = "calculator.exe"
$exePath = "$buildDir\$exeName"

# 檢查 build 資料夾是否存在
if (-Not (Test-Path $buildDir)) {
  Write-Host "🔧 尚未執行 cmake，開始初始化 build 資料夾..." -ForegroundColor Yellow
  cmake -S . -B $buildDir
}

# 編譯主程式 target
Write-Host "`n🔨 編譯主程式..." -ForegroundColor Cyan
cmake --build $buildDir --target calculator

# 檢查是否成功產生可執行檔
if (-Not (Test-Path $exePath)) {
  Write-Host "❌ 找不到 $exePath，可能編譯失敗。" -ForegroundColor Red
  exit 1
}

# 執行主程式
Write-Host "`n🚀 執行 calculator.exe..." -ForegroundColor Green
& $exePath
