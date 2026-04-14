param (
    [Parameter(Mandatory=$true)]
    [string]$FilePath
)

# Ensure output directory exists
if (-not (Test-Path "class")) {
    New-Item -ItemType Directory -Path "class" | Out-Null
}

# Compile the specific file
Write-Host "Compiling $FilePath..." -ForegroundColor Cyan
javac -cp class -d class $FilePath

if ($LASTEXITCODE -eq 0) {
    # Normalize path: remove leading .\ or ./ and convert to dots
    $normalizedPath = $FilePath -replace '^\.[\\/]', ''
    $className = $normalizedPath -replace '\.java$', '' -replace '[\\/]', '.'
    
    # Only try to run if it has a main method
    $content = Get-Content $FilePath -Raw
    if ($content -match "public\s+static\s+void\s+main") {
        Write-Host "Running $className...`n" -ForegroundColor Green
        java -cp class $className
    } else {
        Write-Host "`nCompilation successful. No main method found in $className (Skipping execution)." -ForegroundColor Yellow
    }
} else {
    Write-Host "`nCompilation failed." -ForegroundColor Red
}
