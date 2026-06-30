# PowerShell Lab Runner for DWDM Labs
param (
    [string]$lab = "help"
)

$PythonPath = ".\.venv\Scripts\python.exe"
$PipPath = ".\.venv\Scripts\pip.exe"
$PytestPath = ".\.venv\Scripts\pytest.exe"

function Show-Help {
    Write-Host "==========================================================" -ForegroundColor Cyan
    Write-Host "                DWDM LAB RUNNER SCRIPT                    " -ForegroundColor Cyan
    Write-Host "==========================================================" -ForegroundColor Cyan
    Write-Host "Usage: .\run.ps1 <command>"
    Write-Host ""
    Write-Host "Available commands:"
    Write-Host "  install     - Install dependencies from requirements.txt"
    Write-Host "  lab2        - Run Lab 2: Data Preprocessing (Cleaning)"
    Write-Host "  lab3        - Run Lab 3: Data Preprocessing (Integration)"
    Write-Host "  lab4        - Run Lab 4: Frequent Patterns (Apriori)"
    Write-Host "  lab5a       - Run Lab 5A: ID3 Decision Tree"
    Write-Host "  lab5b       - Run Lab 5B: Naive Bayes Classification"
    Write-Host "  lab5c       - Run Lab 5C: SVM (Simple)"
    Write-Host "  lab5cviz    - Run Lab 5C: SVM Visualization"
    Write-Host "  lab6        - Run Lab 6: Cluster Analysis (K-Means)"
    Write-Host "  test        - Run verification tests with Pytest"
    Write-Host "==========================================================" -ForegroundColor Cyan
}

function Run-PythonLab {
    param (
        [string]$Directory,
        [string]$Script,
        [string]$Name
    )
    Write-Host "`n========================================================" -ForegroundColor Cyan
    Write-Host " Running: $Name" -ForegroundColor Cyan
    Write-Host "========================================================" -ForegroundColor Cyan
    Push-Location $Directory
    try {
        & "..\$PythonPath" $Script
    } finally {
        Pop-Location
    }
    Write-Host "========================================================`n" -ForegroundColor Cyan
}

if ($lab -eq "help" -or -not $lab) {
    Show-Help
    exit
}

if (-not (Test-Path $PythonPath)) {
    Write-Error "Virtual environment not found! Please create it using 'python -m venv .venv' first."
    exit 1
}

switch ($lab.ToLower()) {
    "install" {
        Write-Host "Installing dependencies..." -ForegroundColor Green
        Start-Process -FilePath $PipPath -ArgumentList "install -r requirements.txt" -NoNewWindow -Wait
    }
    "lab2" {
        Run-PythonLab -Directory "Lab2_DataCleaning" -Script "lab2_data_cleaning.py" -Name "Lab 2: Data Preprocessing (Data Cleaning)"
    }
    "lab3" {
        Run-PythonLab -Directory "Lab3_DataIntegration" -Script "lab3_data_integration.py" -Name "Lab 3: Data Preprocessing (Data Integration)"
    }
    "lab4" {
        Run-PythonLab -Directory "Lab4_FrequentPatterns" -Script "lab4_apriori.py" -Name "Lab 4: Frequent Patterns (Apriori)"
    }
    "lab5a" {
        Run-PythonLab -Directory "Lab5_Classification" -Script "lab5a_id3.py" -Name "Lab 5A: ID3 Decision Tree"
    }
    "lab5b" {
        Run-PythonLab -Directory "Lab5_Classification" -Script "lab5b_naive_bayes.py" -Name "Lab 5B: Naive Bayes Classification"
    }
    "lab5c" {
        Run-PythonLab -Directory "Lab5_Classification" -Script "lab5c_svm_simple.py" -Name "Lab 5C: SVM (Simple)"
    }
    "lab5cviz" {
        Run-PythonLab -Directory "Lab5_Classification" -Script "lab5c_svm_visualize.py" -Name "Lab 5C: SVM Decision Boundary Visualization"
    }
    "lab6" {
        Run-PythonLab -Directory "Lab6_Clustering" -Script "lab6_kmeans.py" -Name "Lab 6: Cluster Analysis (K-Means)"
    }
    "test" {
        Write-Host "Running validation tests..." -ForegroundColor Green
        & $PytestPath tests/
    }
    default {
        Write-Host "Unknown command: $lab" -ForegroundColor Red
        Show-Help
    }
}
