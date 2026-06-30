.PHONY: help install run-lab2 run-lab3 run-lab4 run-lab5a run-lab5b run-lab5c run-lab5c-viz run-lab6 test

PYTHON = .\.venv\Scripts\python.exe
PIP = .\.venv\Scripts\pip.exe
PYTEST = .\.venv\Scripts\pytest.exe

help:
	@echo "Available commands:"
	@echo "  make install        - Install all required libraries in the venv"
	@echo "  make run-lab2       - Run Lab 2: Data Cleaning"
	@echo "  make run-lab3       - Run Lab 3: Data Integration"
	@echo "  make run-lab4       - Run Lab 4: Frequent Patterns (Apriori)"
	@echo "  make run-lab5a      - Run Lab 5A: ID3 Decision Tree"
	@echo "  make run-lab5b      - Run Lab 5B: Naive Bayes Classification"
	@echo "  make run-lab5c      - Run Lab 5C: SVM (Simple)"
	@echo "  make run-lab5c-viz  - Run Lab 5C: SVM Visualization"
	@echo "  make run-lab6       - Run Lab 6: Cluster Analysis (K-Means)"
	@echo "  make test           - Run Pytest verification"

install:
	$(PIP) install -r requirements.txt

run-lab2:
	cd Lab2_DataCleaning && ..\$(PYTHON) lab2_data_cleaning.py

run-lab3:
	cd Lab3_DataIntegration && ..\$(PYTHON) lab3_data_integration.py

run-lab4:
	cd Lab4_FrequentPatterns && ..\$(PYTHON) lab4_apriori.py

run-lab5a:
	cd Lab5_Classification && ..\$(PYTHON) lab5a_id3.py

run-lab5b:
	cd Lab5_Classification && ..\$(PYTHON) lab5b_naive_bayes.py

run-lab5c:
	cd Lab5_Classification && ..\$(PYTHON) lab5c_svm_simple.py

run-lab5c-viz:
	cd Lab5_Classification && ..\$(PYTHON) lab5c_svm_visualize.py

run-lab6:
	cd Lab6_Clustering && ..\$(PYTHON) lab6_kmeans.py

test:
	$(PYTEST) tests/
