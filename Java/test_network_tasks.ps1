<#
.SYNOPSIS
Automated Test Runner for Network-based Advanced Java Lab Tasks.

.DESCRIPTION
This script compiles the Java network code, launches the Server component
in a separate popup terminal window, waits for it to initialize, and then runs 
the Client component in the current terminal to verify communication.
#>

param (
    [ValidateSet('TCP', 'UDP', 'FileTransfer', 'RMI', 'All')]
    [string]$Test = 'All'
)

# Ensure we're running from the script's directory (the 'Java' folder)
Set-Location $PSScriptRoot

Write-Host "Compiling network components..." -ForegroundColor Cyan
javac -cp "class;lib/*" -d class Lab/Q2_TCP/*.java Lab/Q3_UDP/*.java Lab/Q4_FileTransfer/*.java Lab/Q16_RMI/*.java

function Run-NetworkTest {
    param (
        [string]$ServerClass,
        [string]$ClientClass,
        [string]$TestName
    )
    Write-Host "`n========================================================" -ForegroundColor Cyan
    Write-Host " Running Test: $TestName" -ForegroundColor Cyan
    Write-Host "========================================================" -ForegroundColor Cyan
    
    Write-Host "[Server] Spawning server in a new window..." -ForegroundColor DarkGray
    
    # Launch server in a separate background window and capture its Process ID
    $serverCommand = "java -cp class $ServerClass; Write-Host '`nServer finished.'; Start-Sleep -Seconds 5"
    $serverProc = Start-Process pwsh -WorkingDirectory $PSScriptRoot -ArgumentList "-WindowStyle Normal -Command `"& { $serverCommand }`"" -PassThru
    
    Write-Host "Waiting 3 seconds for server ports to bind & open..." -ForegroundColor DarkGray
    Start-Sleep -Seconds 3
    
    Write-Host "[Client] Launching client in current terminal...`n" -ForegroundColor Green
    
    # Run the client in the current terminal!
    java -cp class $ClientClass
    
    Write-Host "`nWaiting 2 seconds before cleaning up server..." -ForegroundColor DarkGray
    Start-Sleep -Seconds 2
    
    # Cleanup background server process if it didn't auto-close
    if (-not $serverProc.HasExited) {
        Write-Host "Stopping background server process..." -ForegroundColor Yellow
        Stop-Process -Id $serverProc.Id -Force -ErrorAction SilentlyContinue
    }
    Write-Host "Test '$TestName' Completed Successfully." -ForegroundColor Green
}

if ($Test -in @('TCP', 'All')) { Run-NetworkTest "TCPServer" "TCPClient" "Q2: TCP Communication" }
if ($Test -in @('UDP', 'All')) { Run-NetworkTest "UDPServer" "UDPClient" "Q3: UDP Communication" }
if ($Test -in @('FileTransfer', 'All')) { Run-NetworkTest "FileServer" "FileClient" "Q4: File Transfer" }
if ($Test -in @('RMI', 'All')) { Run-NetworkTest "RMIServer" "RMIClient" "Q16: Remote Method Invocation (RMI)" }
