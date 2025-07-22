Write-Host "🛠 Build Options:"
Write-Host "1. Build CLI only"
Write-Host "2. Build GUI only"
Write-Host "3. Build all"
$choice = Read-Host "Select build mode"

if (-not (Test-Path "build")) {
  New-Item -ItemType Directory -Path "build" | Out-Null
}

Push-Location build

if (-not (Test-Path "CMakeCache.txt")) {
  cmake .. -G "Ninja"
}

switch ($choice) {
  "1" {
    cmake --build . --target calculator_cli
  }
  "2" {
    cmake --build . --target calculator_gui
  }
  "3" {
    cmake --build . --target calculator_cli calculator_gui
  }
  default {
    Write-Host "Invalid choice. Building all by default."
    cmake --build . --target calculator_cli calculator_gui
  }
}

Pop-Location
