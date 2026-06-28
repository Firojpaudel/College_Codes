param (
    [string]$TomcatPath = "C:\xampp\tomcat"
)

# Move to the script's directory
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition
Set-Location $scriptDir

# Check if Tomcat folder exists
if (-not (Test-Path $TomcatPath)) {
    Write-Warning "Tomcat not found at: $TomcatPath"
    $TomcatPath = Read-Host "Please enter the absolute path to your Apache Tomcat installation directory"
    if (-not (Test-Path $TomcatPath)) {
        Write-Error "Invalid Tomcat path. Aborting."
        exit 1
    }
}

Write-Output "Using Tomcat Path: $TomcatPath"

# Compile the servlet
Write-Output "Compiling servlet..."
javac -cp "../../lib/*" -d . EmployeeAuthServlet.java
if ($LASTEXITCODE -ne 0) {
    Write-Error "Compilation failed."
    exit 1
}

# Define deployment targets
$appDir = Join-Path $TomcatPath "webapps\employee-app"
$webInfDir = Join-Path $appDir "WEB-INF"
$classesDir = Join-Path $webInfDir "classes"
$libDir = Join-Path $webInfDir "lib"

# Create directories
Write-Output "Creating deployment directories..."
$null = New-Item -ItemType Directory -Force -Path $classesDir
$null = New-Item -ItemType Directory -Force -Path $libDir

# Copy files
Write-Output "Copying files to Tomcat..."
Copy-Item "web.xml" -Destination $webInfDir -Force
Copy-Item "login.html" -Destination $appDir -Force
Copy-Item "EmployeeAuthServlet.class" -Destination $classesDir -Force
Copy-Item "../../lib/mysql-connector-j-*.jar" -Destination $libDir -Force

# Start Tomcat
Write-Output "Starting Apache Tomcat..."
$binPath = Join-Path $TomcatPath "bin"
$startupBat = Join-Path $binPath "startup.bat"
if (Test-Path $startupBat) {
    Start-Process cmd.exe -ArgumentList "/c `"cd /d $binPath && startup.bat`"" -WindowStyle Normal
} else {
    Write-Warning "startup.bat not found in Tomcat bin/ directory."
}

# Open browser
Write-Output "Opening browser at http://localhost:8080/employee-app/"
Start-Process "http://localhost:8080/employee-app/"
