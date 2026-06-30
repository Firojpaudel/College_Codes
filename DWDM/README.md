# Data Warehousing & Data Mining (DWDM) Lab Suite

This directory contains the codebase, datasets, and report-generation utilities for the DWDM labs.

## Directory Structure
- `Lab2_DataCleaning/`: Code and dirty datasets for preprocessing.
- `Lab3_DataIntegration/`: Integration codebase for Retail transactions.
- `Lab4_FrequentPatterns/`: Apriori rule mining implementation.
- `Lab5_Classification/`: ID3 Decision Tree, Naive Bayes, and SVM code.
- `Lab6_Clustering/`: K-Means clustering analysis.
- `plots/`: Automatically generated diagram plots (`svm_plot.png`, `kmeans_plot.png`).
- `screenshots/`: Modern PowerShell-styled terminal execution outputs.
- `app.py`: Streamlit main dashboard application.
- `generate_doc.py`: Automatic Word report generator.
- `run.ps1`: Interactive terminal script runner.

---

## Getting Started

### 1. Set Up Python Interpreter (Fix Editor Red Squiggles)
If you see red squiggles under imports like `numpy` or `matplotlib` in VS Code, it is because your editor is using the global Python interpreter instead of the project's virtual environment.
To fix this:
1. Open the Command Palette (`Ctrl + Shift + P`).
2. Type and select `Python: Select Interpreter`.
3. Choose the interpreter located inside the `.venv/` directory (e.g. `.\.venv\Scripts\python.exe`).

### 2. Run the Labs via PowerShell
You can use the custom runner to execute any lab with colored terminal wrappers:
```powershell
# Run Lab 2 (Data Preprocessing)
.\run.ps1 lab2

# Run Lab 5A (ID3 Decision Tree)
.\run.ps1 lab5a

# Launch Streamlit app
.\.venv\Scripts\streamlit.exe run app.py
```

---

## Generating the Lab Report

To generate the final `.docx` submission report containing the code, plots, and terminal screenshots, run the generator script using the virtual environment:

```powershell
# Run the report generator
.\.venv\Scripts\python.exe generate_doc.py
```

### Generator Notes:
- **No Front Page:** The report starts directly from Lab 2.
- **Normal Code Text:** Code is rendered as normal text inside the document using the **Consolas** font without block tables.
- **Embedded Screenshots & Plots:** Renders realistic modern black PowerShell terminal outputs and inserts them alongside the classification/clustering plots under the output sections.
- **Page Breaks:** Each lab experiment starts automatically on a new page.
- **File Overwrite Protection:** If the file `LABS_QUESTIONS_AND_ANSWERS.docx` is open in Microsoft Word, the script will automatically save the new output with a random suffix (e.g. `LABS_QUESTIONS_AND_ANSWERS_741.docx`) to prevent crashes. Close MS Word to allow it to overwrite the main document.
