cls
Write-Host "Arduino ECG Simulator - Upload" -ForegroundColor Cyan
$Port = "COM4"
$HexFile = "C:\Users\Alejandro\Downloads\ecg_web_node_backend\arduino_ecg_simulator.hex"
$AvrDude = "C:\Users\Alejandro\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17\bin\avrdude.exe"
$AvrConf = "C:\Users\Alejandro\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17\etc\avrdude.conf"

if (-not (Test-Path $HexFile)) {
    Write-Host "ERROR: hex file not found" -ForegroundColor Red
    exit 1
}

Write-Host "DISCONNECT Arduino from USB now" -ForegroundColor Yellow
Write-Host "Then press ENTER" -ForegroundColor Yellow
[void][System.Console]::ReadLine()

Write-Host "CONNECT Arduino to USB now" -ForegroundColor Yellow
Write-Host "Then press ENTER" -ForegroundColor Yellow
[void][System.Console]::ReadLine()

Start-Sleep -Seconds 2

Write-Host "Uploading..." -ForegroundColor Cyan
$cmd = @(
    "-C", $AvrConf,
    "-v",
    "-p", "atmega328p",
    "-c", "arduino",
    "-P", $Port,
    "-b", "115200",
    "-D",
    "-U", "flash:w:$HexFile:i"
)

& $AvrDude @cmd

if ($LASTEXITCODE -eq 0) {
    Write-Host "SUCCESS!" -ForegroundColor Green
}
else {
    Write-Host "FAILED - check port and connections" -ForegroundColor Red
}
