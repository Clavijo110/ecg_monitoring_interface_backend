# Arduino ECG Simulator - Upload Script
# Simple version for Windows PowerShell

Write-Host "================================"
Write-Host "Arduino ECG Simulator Upload"
Write-Host "================================"

# Detect COM ports
Write-Host "`nDetecting COM ports..."
$ports = Get-WmiObject -Class Win32_SerialPort

if ($ports.Count -eq 0) {
    Write-Host "ERROR: No COM ports found. Check Arduino connection."
    exit 1
}

Write-Host "Found ports:"
$ports | ForEach-Object { Write-Host "  - $($_.DeviceID): $($_.Description)" }

$Port = $ports[0].DeviceID
Write-Host "Using: $Port"

# Check for Arduino CLI or IDE
Write-Host "`nChecking for Arduino CLI..."

$cliPath = "$env:LOCALAPPDATA\Arduino\arduino-cli.exe"
$idePath = "C:\Program Files\Arduino IDE\resources\app\bin\arduino-cli.exe"

if (Test-Path $cliPath) {
    Write-Host "Found Arduino CLI: $cliPath"
    $cli = $cliPath
} elseif (Test-Path $idePath) {
    Write-Host "Found Arduino IDE CLI: $idePath"
    $cli = $idePath
} else {
    Write-Host "Arduino CLI not found locally"
    Write-Host "Installing Arduino CLI..."
    
    # Create directory
    $cliDir = "$env:LOCALAPPDATA\Arduino"
    New-Item -ItemType Directory -Path $cliDir -Force | Out-Null
    
    # Download Arduino CLI
    $url = "https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Windows_64bit.zip"
    $zip = "$cliDir\arduino-cli.zip"
    
    try {
        Write-Host "Downloading from: $url"
        Invoke-WebRequest -Uri $url -OutFile $zip
        Write-Host "Downloaded successfully"
        
        Write-Host "Extracting..."
        Expand-Archive -Path $zip -DestinationPath $cliDir -Force
        Remove-Item $zip
        
        $cli = "$cliDir\arduino-cli.exe"
        Write-Host "Arduino CLI installed: $cli"
    }
    catch {
        Write-Host "ERROR: Could not download Arduino CLI"
        Write-Host "Please install Arduino IDE from: https://www.arduino.cc/en/software"
        exit 1
    }
}

# Compile
Write-Host "`nCompiling sketch..."
$sketch = "c:\Users\Alejandro\Downloads\ecg_web_node_backend\arduino_ecg_simulator.ino"

if (-not (Test-Path $sketch)) {
    Write-Host "ERROR: Sketch not found: $sketch"
    exit 1
}

& "$cli" config init --overwrite 2>$null
& "$cli" core install arduino:avr:mega2560 2>$null

Write-Host "Building..."
$build = & "$cli" compile --fqbn arduino:avr:mega2560 "$sketch" 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: Compilation failed"
    Write-Host $build
    exit 1
}

Write-Host "Compilation successful!"

# Upload
Write-Host "`nUploading to $Port..."
Write-Host "DO NOT DISCONNECT ARDUINO!"

$upload = & "$cli" upload --fqbn arduino:avr:mega2560 --port $Port "$sketch" 2>&1

if ($LASTEXITCODE -ne 0) {
    Write-Host "ERROR: Upload failed"
    Write-Host $upload
    exit 1
}

Write-Host "`n================================"
Write-Host "SUCCESS!"
Write-Host "================================"
Write-Host "Next steps:"
Write-Host "1. Open Arduino IDE Serial Monitor"
Write-Host "2. Speed: 115200 baud"
Write-Host "3. You should see: READY"
Write-Host ""
Write-Host "Then:"
Write-Host "1. Run: npm start (backend)"
Write-Host "2. Open: http://localhost:3000"
Write-Host "3. Connect from app"
