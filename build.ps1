$buildDir = "build"

# 提問：是否有修改 CMakeLists.txt？
$answer = Read-Host "是否有修改 CMakeLists.txt？(y/n)"

if ($answer -eq "y" -or $answer -eq "Y") {
  # 刪除整個 build 目錄
  if (Test-Path $buildDir) {
    Write-Host "刪除 build 資料夾..."
    Remove-Item -Recurse -Force $buildDir
  }

  # 重新建立 build 目錄
  Write-Host "建立新的 build 資料夾..."
  New-Item -ItemType Directory -Path $buildDir | Out-Null

  # 進入 build 並執行 cmake
  Set-Location $buildDir
  Write-Host "執行 cmake .."
  cmake .. -G "MinGW Makefiles"

} elseif ($answer -eq "n" -or $answer -eq "N") {
  if (-Not (Test-Path $buildDir)) {
    Write-Host "找不到 build 資料夾，將自動建立並執行 cmake .."
    New-Item -ItemType Directory -Path $buildDir | Out-Null
    Set-Location $buildDir
    cmake ..
  } else {
    Set-Location $buildDir
    Write-Host "執行 mingw32-make clean"
    mingw32-make clean
  }

} else {
  Write-Host "無效輸入，請輸入 y 或 n。"
  exit 1
}

# 最後進行 build
Write-Host "`n開始編譯..."
mingw32-make

Write-Host "`n✅ 編譯完成！"

# 返回專案根目錄
Set-Location ..
