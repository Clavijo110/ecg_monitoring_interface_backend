# Check Arduino Serial Communication
$port = "COM4"
$baudRate = 115200
$timeout = 3000  # 3 segundos

Write-Host "Conectando a $port @ $baudRate baud..." -ForegroundColor Cyan

try {
    $serial = New-Object System.IO.Ports.SerialPort($port, $baudRate)
    $serial.Open()
    
    Write-Host "✅ Conectado!" -ForegroundColor Green
    Write-Host "`nLeyendo datos del Arduino (timeout: ${timeout}ms)..." -ForegroundColor Yellow
    
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    $dataReceived = $false
    $allData = @()
    
    while ($stopwatch.ElapsedMilliseconds -lt $timeout) {
        if ($serial.BytesToRead -gt 0) {
            $line = $serial.ReadLine()
            if ($line) {
                Write-Host "RX: $line" -ForegroundColor Green
                $allData += $line
                $dataReceived = $true
            }
        }
        Start-Sleep -Milliseconds 10
    }
    
    $serial.Close()
    
    if ($dataReceived) {
        Write-Host "`n✅ Arduino está CORRIENDO!" -ForegroundColor Green
        Write-Host "`nÚltimos datos recibidos:" -ForegroundColor Cyan
        $allData | Select-Object -Last 5 | ForEach-Object { Write-Host "  $_" }
        
        # Analizar datos
        if ($allData -contains "READY") {
            Write-Host "`n✅ Simulador ECG inicializado (READY recibido)" -ForegroundColor Green
        }
        
        $dataLines = $allData | Where-Object { $_ -like "DATA,*" }
        if ($dataLines.Count -gt 0) {
            Write-Host "✅ Datos ECG siendo generados ($($dataLines.Count) paquetes)" -ForegroundColor Green
        }
    }
    else {
        Write-Host "`n⚠️  No hay datos siendo recibidos" -ForegroundColor Yellow
        Write-Host "   Posibles causas:" -ForegroundColor Yellow
        Write-Host "   1. El código no se cargó correctamente" -ForegroundColor Gray
        Write-Host "   2. Arduino no tiene poder" -ForegroundColor Gray
        Write-Host "   3. Cable USB desconectado" -ForegroundColor Gray
    }
}
catch {
    Write-Host "❌ Error: $_" -ForegroundColor Red
}
