# Java Programming Lab Exercises

This folder contains a collection of Java lab exercises for the 7th-semester college course. The programs cover a wide range of core Java concepts, from basic syntax and object-oriented programming to advanced topics like multithreading, file I/O, and serialization.

## Table of Contents
- [Unit 1: Core Java & I/O](#unit-1-core-java--io)
- [Unit 2: Package Management](#unit-2-package-management)
- [Resources](#resources)
- [How to Run](#how-to-run)

## Project Structure
```text
Java/
├── Unit_1/           # Core Java, Exceptions, Threads, File I/O
├── Unit_2/           # Package usage and testing
├── resources/         # Data files (txt, dat, ser) for the programs
├── class/            # Compiled .class files (auto-generated)
└── run.ps1           # PowerShell script for easy compilation/execution
```

## Key Exercises
- **StudentRecordAnalysis**: Reads CSV data and calculates highest/average marks.
- **WordSortDemo**: Manual Bubble Sort implementation for words in a file.
- **WordReplaceDemo**: Interactive find-and-replace tool for text files.
- **RaceConditionDemo**: Visualizing thread interference and synchronization.
- **FileCompareDemo**: Byte-by-byte file comparison utility.

## How to Run
We use a custom PowerShell script `run.ps1` to automate the process.

1.  Open PowerShell in the `Java/` directory.
2.  Run the script with the path to the Java file:
    ```powershell
    .\run.ps1 Unit_1\StudentRecordAnalysis.java
    ```

The script will:
- Compile the code to the `class/` folder.
- Run the program automatically if a `main` method is found.

## Features
- **Clean Code**: Redundant comments have been removed for a professional look.
- **Organized Resources**: All data files are isolated in the `resources/` folder.
- **Automated Workflow**: Easy compilation and execution.
