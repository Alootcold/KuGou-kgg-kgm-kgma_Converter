# KuGouConverter Deploy Script

$releaseDir = "D:\Users\Lenovo\Desktop\KuGou kgg,kgm,kgma_converter\KuGouConverter\release"
$qtDir = "C:\Qt\6.10.2\msvc2022_64\bin"

Set-Location $releaseDir

if (Test-Path "KuGouConverter.exe") {
    Write-Host "Running windeployqt..."
    & "$qtDir\windeployqt.exe" --release KuGouConverter.exe
    Write-Host "Deploy completed!"
} else {
    Write-Host "Error: KuGouConverter.exe not found"
    Write-Host "Please build Release version first"
}

Read-Host "Press Enter to exit"
