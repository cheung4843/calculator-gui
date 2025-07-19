# test.ps1
Write-Host "`n🚀 執行所有單元測試..."

$buildDir = "build"
$testPrefix = "test_"

# 確認 build 資料夾存在
if (-Not (Test-Path $buildDir)) {
  Write-Host "❌ 找不到 build/ 資料夾，請先執行 build.ps1。" -ForegroundColor Red
  exit 1
}

# 切換到 build 目錄
Set-Location $buildDir

# 取得所有 test_ 開頭的執行檔
$testBinaries = Get-ChildItem -Filter "$testPrefix*.exe"

if ($testBinaries.Count -eq 0) {
  Write-Host "⚠️ 找不到任何測試執行檔，請先確認測試是否成功建置。" -ForegroundColor Yellow
  exit 1
}

$hasError = $false

# 執行每個測試
foreach ($test in $testBinaries) {
  Write-Host "`n🧪 執行測試: $($test.Name)"
  & .\$($test.Name)
  if ($LASTEXITCODE -ne 0) {
    Write-Host "❌ 測試 $($test.Name) 失敗。" -ForegroundColor Red
    $hasError = $true
  } else {
    Write-Host "✅ 測試 $($test.Name) 通過。" -ForegroundColor Green
  }
}

# 返回專案根目錄
Set-Location ..

# 總結
if ($hasError) {
  Write-Host "`n❗ 有測試未通過，請檢查錯誤訊息。" -ForegroundColor Yellow
  exit 1
} else {
  Write-Host "`n🎉 所有測試通過！" -ForegroundColor Cyan
}
