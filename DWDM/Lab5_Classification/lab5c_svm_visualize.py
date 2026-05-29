import numpy as np
import matplotlib.pyplot as plt
from sklearn import svm

def main():
    print("=" * 50)
    print(" LAB 5C: SVM DECISION BOUNDARY VISUALIZATION ")
    print("=" * 50)

    # 1. Two-class synthetic data
    X = np.array([[1, 2], [2, 3], [3, 3], [4, 4],   # Class 0
                  [6, 7], [7, 8], [8, 7], [9, 9]])  # Class 1
    y = np.array([0, 0, 0, 0, 1, 1, 1, 1])

    # 2. Train linear SVM
    print("[INFO] Training SVM model...")
    clf = svm.SVC(kernel='linear')
    clf.fit(X, y)

    print(f"\nNumber of support vectors: {len(clf.support_vectors_)}")
    print(f"Support vector coordinates:\n{clf.support_vectors_}")

    # 3. Visualization Setup
    print("\n[INFO] Generating plot window. Close the plot window to exit.")
    
    fig, ax = plt.subplots(figsize=(8, 6))
    scatter = ax.scatter(X[:,0], X[:,1], c=y, s=100, cmap='viridis', edgecolors='k', zorder=3)

    # Meshgrid generation
    xlim, ylim = ax.get_xlim(), ax.get_ylim()
    xx = np.linspace(xlim[0], xlim[1], 50)
    yy = np.linspace(ylim[0], ylim[1], 50)
    YY, XX = np.meshgrid(yy, xx)
    
    Z = clf.decision_function(np.c_[XX.ravel(), YY.ravel()]).reshape(XX.shape)

    # Decision boundaries and margins
    ax.contour(XX, YY, Z, colors='k', levels=[-1, 0, 1],
               linestyles=['--', '-', '--'], alpha=0.6)

    # Highlight support vectors
    ax.scatter(clf.support_vectors_[:,0], clf.support_vectors_[:,1],
               s=220, facecolors='none', edgecolors='red', linewidths=1.5,
               label='Support Vectors')

    ax.set_xlabel("Feature X1")
    ax.set_ylabel("Feature X2")
    ax.set_title("SVM Optimization: Decision Boundary & Margins")
    ax.legend(loc='lower right')
    plt.colorbar(scatter, ax=ax, label='Class Label')
    plt.grid(True, linestyle=":", alpha=0.4)
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()
