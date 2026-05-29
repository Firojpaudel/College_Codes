import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
from sklearn.datasets import make_blobs
from sklearn.preprocessing import StandardScaler
import warnings

# Suppress the UserWarning from KMeans regarding memory leak on Windows
warnings.filterwarnings("ignore", category=UserWarning, module="sklearn.cluster._kmeans")

def main():
    print("=" * 50)
    print(" LAB 6: CLUSTER ANALYSIS (K-MEANS) ")
    print("=" * 50)

    # 1. Dataset Generation
    X, y_true = make_blobs(n_samples=300, centers=4, cluster_std=0.60, random_state=42)
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    print(f"[INFO] Synthetic dataset generated and standardized. Shape: {X_scaled.shape}")

    # 2. Apply K-Means
    k = 4
    print(f"\n[INFO] Running K-Means with K={k}...")
    kmeans = KMeans(n_clusters=k, random_state=42, n_init=10)
    kmeans.fit(X_scaled)
    
    labels = kmeans.labels_
    centroids = kmeans.cluster_centers_

    # Print Report
    print("\n--- Model Performance ---")
    print(f"Inertia (WCSS) : {kmeans.inertia_:.4f}")
    print(f"Iterations     : {kmeans.n_iter_}")
    
    unique_labels, counts = np.unique(labels, return_counts=True)
    cluster_counts = dict(zip(unique_labels, counts))
    print(f"Cluster sizes  : {cluster_counts}")

    # 3. New Point Prediction
    print("\n[PREDICTION TEST]")
    new_point = np.array([[1.5, 2.0]])
    new_point_scaled = scaler.transform(new_point)
    predicted_cluster = kmeans.predict(new_point_scaled)[0]
    print(f"New point {new_point[0]} -> Assigned to Cluster {predicted_cluster}")

    # 4. Visualisation
    print("\n[INFO] Generating plot window. Close the plot window to exit.")
    colors = ['#e74c3c', '#3498db', '#2ecc71', '#f39c12']

    plt.figure(figsize=(9, 6))
    for cluster_id in range(k):
        mask = labels == cluster_id
        plt.scatter(X_scaled[mask, 0], X_scaled[mask, 1],
                    s=60, c=colors[cluster_id], label=f'Cluster {cluster_id}', alpha=0.7)

    plt.scatter(centroids[:, 0], centroids[:, 1],
                s=300, c='black', marker='X', zorder=5, label='Centroids')

    plt.xlabel("Scaled Feature 1")
    plt.ylabel("Scaled Feature 2")
    plt.title(f"K-Means Clustering Distribution (K={k})")
    plt.legend()
    plt.grid(True, linestyle=":", alpha=0.5)
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()
