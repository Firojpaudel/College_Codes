# Setup and Interactive Lab Runner for Java Programming Labs

# Ensure we're in the script's directory
Set-Location $PSScriptRoot

# Check if Java is installed
function Check-Java {
    $javaPath = Get-Command java -ErrorAction SilentlyContinue
    if ($javaPath) {
        Write-Host "Java is installed: $(java -version 2>&1 | Select-Object -First 1)" -ForegroundColor Green
        return $true
    } else {
        Write-Warning "Java is not installed on this system."
        return $false
    }
}

# Install Java via Winget
function Install-Java {
    Write-Host "Installing Eclipse Temurin OpenJDK 17 via Windows Package Manager (winget)..." -ForegroundColor Cyan
    winget install --id EclipseAdoptium.Temurin.17.JDK --silent --accept-package-agreements --accept-source-agreements
    if ($LASTEXITCODE -eq 0) {
        Write-Host "Java installed successfully! Please restart your terminal for environment changes to take effect." -ForegroundColor Green
    } else {
        Write-Error "Winget installation failed. Please download and install JDK manually from https://adoptium.net/"
    }
}

# Compile and Run simple console tasks
function Run-ConsoleTask {
    param (
        [string]$FilePath,
        [string]$ClassName
    )
    Write-Host "`n--- Running $ClassName ---" -ForegroundColor Cyan
    if (-not (Test-Path "class")) {
        New-Item -ItemType Directory -Path "class" -Force | Out-Null
    }
    
    # Compile
    javac -d class $FilePath
    if ($LASTEXITCODE -eq 0) {
        # Run
        java -cp class $ClassName
    } else {
        Write-Error "Failed to compile $FilePath"
    }
    Write-Host "-------------------------------------"
    Read-Host "Press Enter to continue..."
}

# Run Servlet / JSP launcher
function Launch-WebTask {
    param (
        [string]$QuestionFolder
    )
    $deployScript = Join-Path "Lab" "$QuestionFolder\deploy.ps1"
    if (Test-Path $deployScript) {
        Write-Host "Launching deploy script for $QuestionFolder..." -ForegroundColor Cyan
        & $deployScript
    } else {
        Write-Error "Deploy script not found at $deployScript"
    }
}

# Interactive Menu Loop
do {
    Clear-Host
    Write-Host "=============================================" -ForegroundColor Yellow
    Write-Host "         Java Lab Exercises Runner           " -ForegroundColor Yellow
    Write-Host "=============================================" -ForegroundColor Yellow
    Write-Host "1. Check Java (JDK) Installation Status"
    Write-Host "2. Install Java JDK 17 (Automated via Winget)"
    Write-Host "3. Run Core Java Lab: Frequency Counter (Unit 1)"
    Write-Host "4. Run Core Java Lab: Remove Duplicates (Unit 1)"
    Write-Host "5. Run Advanced Java Lab: Basic Servlet (Q9)"
    Write-Host "6. Run Advanced Java Lab: Hello Servlet GET (Q10)"
    Write-Host "7. Run Advanced Java Lab: Student Registration Servlet (Q11)"
    Write-Host "8. Run Advanced Java Lab: Login Servlet (Q12)"
    Write-Host "9. Run Advanced Java Lab: Employee CRUD & Session (Q13)"
    Write-Host "10. Run Advanced Java Lab: JSP Registration (Q14)"
    Write-Host "11. Run Advanced Java Lab: Online Exam JSP (Q15)"
    Write-Host "12. Run Advanced Java Lab: RMI Application (Q16)"
    Write-Host "13. Exit"
    Write-Host "=============================================" -ForegroundColor Yellow
    
    $choice = Read-Host "Select an option (1-13)"
    
    switch ($choice) {
        "1" { Check-Java; Read-Host "Press Enter to continue..." }
        "2" { Install-Java; Read-Host "Press Enter to continue..." }
        "3" { Run-ConsoleTask "Unit_1\FrequencyCounter.java" "Unit_1.FrequencyCounter" }
        "4" { Run-ConsoleTask "Unit_1\RemoveDuplicates.java" "Unit_1.RemoveDuplicates" }
        "5" { Launch-WebTask "Q9_BasicServlet" }
        "6" { Launch-WebTask "Q10_ServletGET" }
        "7" { Launch-WebTask "Q11_ServletRegistration" }
        "8" { Launch-WebTask "Q12_ServletLogin" }
        "9" { Launch-WebTask "Q13_EmployeeSession" }
        "10" { Launch-WebTask "Q14_JSPRegistration" }
        "11" { Launch-WebTask "Q15_OnlineExam" }
        "12" {
            # Compile and start RMI server and client
            Write-Host "Compiling RMI files..." -ForegroundColor Cyan
            javac Lab/Q16_RMI/*.java
            if ($LASTEXITCODE -eq 0) {
                Write-Host "Starting RMI registry and server in background..." -ForegroundColor Cyan
                Start-Process java -ArgumentList "-cp Lab/Q16_RMI RMIServer" -NoNewWindow
                Start-Sleep -Seconds 2
                Write-Host "Running RMI Client..." -ForegroundColor Green
                java -cp Lab/Q16_RMI RMIClient
            }
            Read-Host "Press Enter to continue..."
        }
        "13" { break }
        default { Write-Host "Invalid option. Please choose 1-13." -ForegroundColor Red; Start-Sleep -Seconds 2 }
    }
} while ($choice -ne "13")
