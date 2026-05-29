from sklearn import svm
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
import numpy as np

def main():
    print("=" * 50)
    print(" LAB 5C: SUPPORT VECTOR MACHINE (SIMPLE) ")
    print("=" * 50)

    # 1. Dataset Setup
    X = np.array([[1, 2], [2, 3], [3, 4], [8, 9], [9, 10], [10, 11]])
    y = np.array([0, 0, 0, 1, 1, 1])

    print("[INFO] Synthetic binary dataset created.")
    
    # 2. Train-Test Split
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.3, random_state=42
    )

    # 3. Model Training
    print("[INFO] Training Linear SVM model...")
    clf = svm.SVC(kernel='linear')
    clf.fit(X_train, y_train)

    # 4. Evaluation
    y_pred = clf.predict(X_test)
    print(f"\n[RESULT] Accuracy Score: {accuracy_score(y_test, y_pred):.2f}")

    # 5. Prediction
    new_samples = np.array([[5, 6], [1, 1]])
    predictions = clf.predict(new_samples)
    
    print("\n[PREDICTION TEST]")
    for sample, pred in zip(new_samples, predictions):
        print(f"Sample {sample} -> Class {pred}")

if __name__ == "__main__":
    main()
