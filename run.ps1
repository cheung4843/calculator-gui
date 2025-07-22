Write-Host "🚀 Run Options:"
Write-Host "1. Run CLI"
Write-Host "2. Run GUI"
$choice = Read-Host "Select run mode"

$cli = ".\\build\\calculator_cli.exe"
$gui = ".\\build\\gui\\calculator_gui.exe"

switch ($choice) {
  "1" {
    if (Test-Path $cli) {
      & $cli
    } else {
      Write-Host "CLI not built. Please run build.ps1 first."
    }
  }
  "2" {
    if (Test-Path $gui) {
      & $gui
    } else {
      Write-Host "GUI not built. Please run build.ps1 first."
    }
  }
  default {
    Write-Host "Invalid choice."
  }
}
