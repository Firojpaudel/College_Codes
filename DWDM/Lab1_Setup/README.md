# Lab 1: Setting Up the DWDM Environment

## Objective

Set up the complete development environment required for all DWDM lab experiments.

## Steps

### Step 1 — Install Oracle 19c EE / MySQL Standard Edition DB

**Oracle 19c Express Edition (Free):**
1. Download from [oracle.com](https://www.oracle.com/database/technologies/xe-downloads.html)
2. Run the installer and follow on-screen instructions
3. Note the **SYS** and **SYSTEM** passwords you set during installation
4. Verify installation by opening **SQL*Plus**:
   ```sql
   sqlplus / as sysdba
   SELECT * FROM v$version;
   ```

**OR MySQL Standard Edition:**
1. Download from [mysql.com](https://dev.mysql.com/downloads/mysql/)
2. Install MySQL Server and MySQL Workbench
3. Verify:
   ```bash
   mysql -u root -p
   SHOW DATABASES;
   ```

### Step 2 — Install Python and Create a Virtual Environment

```bash
# Check if Python is already installed
python --version

# Install virtualenv
pip install virtualenv

# Create a virtual environment named '.venv' (or 'dwdm_env')
python -m venv .venv

# Activate the environment
# On Windows:
.venv\Scripts\activate
# On macOS/Linux:
source .venv/bin/activate

# Install required packages for all labs
pip install pandas numpy matplotlib scikit-learn mlxtend streamlit openpyxl pytest
```

### Step 3 — Install VS Code Editor

1. Download from [code.visualstudio.com](https://code.visualstudio.com/)
2. Install the **Python extension** by Microsoft
3. Install the **Pylance** extension for IntelliSense
4. Set your Python interpreter to the virtual environment:
   - Press `Ctrl+Shift+P` → "Python: Select Interpreter" → choose `.venv`

### Verification Checklist

- [x] Database (Oracle/MySQL) running and accessible
- [x] Python virtual environment activated
- [x] All packages installed without errors
- [x] VS Code recognizes the Python interpreter