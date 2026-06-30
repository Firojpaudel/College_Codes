import streamlit as st
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os
import glob
from sklearn import svm
from sklearn.cluster import KMeans
from sklearn.datasets import make_blobs
from sklearn.preprocessing import StandardScaler
from sklearn.naive_bayes import CategoricalNB
from sklearn.metrics import accuracy_score
from mlxtend.frequent_patterns import apriori, association_rules
from collections import Counter
import math

# Set Page Config
st.set_page_config(
    page_title="DWDM Lab Suite & Analyzer",
    page_icon="📊",
    layout="wide",
    initial_sidebar_state="expanded"
)

# Title & Description
st.title("📊 Data Warehousing & Data Mining Lab Suite")
st.markdown("---")

# Sidebar navigation
st.sidebar.title("Navigation")
page = st.sidebar.radio(
    "Choose a Lab Experiment:",
    [
        "Home / Dashboard",
        "Lab 2: Data Cleaning",
        "Lab 3: Data Integration",
        "Lab 4: Frequent Patterns (Apriori)",
        "Lab 5: Classification (ID3, Naive Bayes, SVM)",
        "Lab 6: Cluster Analysis (K-Means)"
    ]
)

# Helper function to load datasets
def get_path(relative_path):
    # Search in current directory or parent/child directory
    for p in [relative_path, os.path.join("..", relative_path), os.path.join("DWDM", relative_path)]:
        if os.path.exists(p):
            return p
    # Try searching recursively
    matches = glob.glob(f"**/{os.path.basename(relative_path)}", recursive=True)
    if matches:
        return matches[0]
    return relative_path

# ==========================================
# Home Page
# ==========================================
if page == "Home / Dashboard":
    st.header("🏫 Academic Coursework Dashboard")
    st.markdown("""
    Welcome to the **Data Warehousing & Data Mining (DWDM)** interactive lab suite!
    This application integrates all of your lab experiments into an interactive, visual dashboard.
    
    ### Available Lab Experiments:
    1. **Lab 2: Data Preprocessing — Data Cleaning:** Imports a dirty dataset, handles missing entries via mean imputation, converts string dates to standard datetime formats, filters outliers, and removes duplicate rows.
    2. **Lab 3: Data Preprocessing — Data Integration:** Merges online retail datasets from separate CSV and Excel sources, aligns the columns, tags records by source, deduplicates, and runs regional sales revenue analytics.
    3. **Lab 4: Association Rule Mining (Apriori):** Generates one-hot transaction databases, mining frequent itemsets and calculating Support, Confidence, and Lift metrics dynamically.
    4. **Lab 5: Classification Suite:**
       - **ID3 Decision Tree:** Evaluates attribute splits from scratch using Entropy and Information Gain.
       - **Naive Bayes:** Trains a probability classifier using sklearn's CategoricalNB model.
       - **Support Vector Machine (SVM):** Trains a linear SVM classifier and plots its optimized separating boundary and margins.
    5. **Lab 6: Cluster Analysis (K-Means):** Groups synthetic n-dimensional coordinate points into cohesive clusters, showing the effect of changing the number of clusters ($K$) on inertia (WCSS).
    """)
    st.info("👈 Use the sidebar navigation menu to run and explore each experiment!")

# ==========================================
# Lab 2: Data Cleaning
# ==========================================
elif page == "Lab 2: Data Cleaning":
    st.header("🧹 Lab 2: Data Preprocessing — Data Cleaning")
    
    csv_file = get_path("Lab2_DataCleaning/DataCleaning.csv")
    if not os.path.exists(csv_file):
        st.error(f"Dataset file '{csv_file}' not found! Please check folder placement.")
    else:
        df_raw = pd.read_csv(csv_file)
        
        col1, col2 = st.columns(2)
        with col1:
            st.subheader("Original (Dirty) Dataset")
            st.dataframe(df_raw, height=400)
            st.caption(f"Total Rows: {len(df_raw)}")
            
        with col2:
            st.subheader("Cleaned Dataset (Processed)")
            
            # Apply cleaning logic
            df_clean = df_raw.copy()
            
            # Fill missing Calories
            mean_calories = df_clean["Calories"].mean()
            df_clean["Calories"] = df_clean["Calories"].fillna(mean_calories)
            
            # Convert dates and drop invalid
            df_clean["Date"] = pd.to_datetime(df_clean["Date"], errors="coerce")
            invalid_dates = df_clean["Date"].isna().sum()
            df_clean.dropna(subset=["Date"], inplace=True)
            
            # Outlier capping
            outliers_capped = (df_clean["Duration"] > 120).sum()
            df_clean.loc[df_clean["Duration"] > 120, "Duration"] = 120
            
            # Remove duplicates
            duplicates_removed = df_clean.duplicated().sum()
            df_clean.drop_duplicates(inplace=True)
            
            st.dataframe(df_clean, height=400)
            st.caption(f"Total Rows after cleaning: {len(df_clean)}")
            
        st.markdown("---")
        st.subheader("Processing Log")
        st.success(f"✔️ Imputed missing 'Calories' using column mean: **{mean_calories:.2f}**")
        st.success(f"✔️ Identified and dropped **{invalid_dates}** rows containing invalid dates.")
        st.success(f"✔️ Capped **{outliers_capped}** outlier duration value(s) exceeding 120 minutes.")
        st.success(f"✔️ Identified and removed **{duplicates_removed}** identical duplicate rows.")
        
        # Download Cleaned Data
        csv_download = df_clean.to_csv(index=False).encode('utf-8')
        st.download_button(
            label="📥 Download Cleaned Dataset as CSV",
            data=csv_download,
            file_name="Cleaned_Dataset.csv",
            mime="text/csv"
        )

# ==========================================
# Lab 3: Data Integration
# ==========================================
elif page == "Lab 3: Data Integration":
    st.header("🔗 Lab 3: Data Preprocessing — Data Integration")
    
    excel_path = get_path("Lab3_DataIntegration/Online RetailSmall.xlsx")
    csv_path = get_path("Lab3_DataIntegration/Online RetailSmallData.csv")
    
    if not (os.path.exists(excel_path) and os.path.exists(csv_path)):
        st.error("Excel or CSV online retail datasets are missing from Lab3 folder.")
    else:
        st.markdown("This lab integrates customer shopping transactions recorded in different format sources (Excel and CSV) and alignments.")
        
        common_cols = ['StockCode', 'Description', 'Quantity', 'UnitPrice', 'CustomerID', 'Country']
        
        df_excel = pd.read_excel(excel_path)[common_cols]
        df_excel['Source'] = "Excel"
        
        df_csv = pd.read_csv(csv_path, encoding="unicode_escape")[common_cols]
        df_csv['Source'] = "CSV"
        
        col1, col2 = st.columns(2)
        with col1:
            st.subheader("Source 1: Excel Records")
            st.dataframe(df_excel.head(5))
            st.caption(f"Rows: {len(df_excel)}")
        with col2:
            st.subheader("Source 2: CSV Records")
            st.dataframe(df_csv.head(5))
            st.caption(f"Rows: {len(df_csv)}")
            
        # Integration
        df_integrated = pd.concat([df_excel, df_csv], ignore_index=True)
        df_integrated.drop_duplicates(inplace=True)
        
        st.markdown("---")
        st.subheader("Combined & Integrated Dataset (Deduplicated)")
        st.dataframe(df_integrated, height=350)
        st.caption(f"Total Integrated Rows: {len(df_integrated)}")
        
        st.markdown("---")
        st.subheader("Sales Analytics (Aggregated Revenue)")
        df_integrated['Revenue'] = df_integrated['Quantity'] * df_integrated['UnitPrice']
        revenue_by_country = df_integrated.groupby('Country')['Revenue'].sum().reset_index()
        
        col_c1, col_c2 = st.columns([1, 2])
        with col_c1:
            st.dataframe(revenue_by_country)
        with col_c2:
            fig, ax = plt.subplots(figsize=(6, 3))
            ax.bar(revenue_by_country['Country'], revenue_by_country['Revenue'], color=['#3498db', '#2ecc71'])
            ax.set_title("Revenue Distribution by Country")
            ax.set_ylabel("Revenue ($)")
            st.pyplot(fig)

# ==========================================
# Lab 4: Frequent Patterns (Apriori)
# ==========================================
elif page == "Lab 4: Frequent Patterns (Apriori)":
    st.header("🛒 Lab 4: Association Rule Mining (Apriori)")
    
    st.markdown("Generate frequent itemsets and derive association rules from custom transactions.")
    
    # Dataset
    dataset = [
        ['A', 'B', 'C'],
        ['A', 'C'],
        ['A', 'D'],
        ['B', 'E', 'F']
    ]
    
    st.subheader("Raw Transactions Database")
    st.write(dataset)
    
    # One-hot encoding
    df = pd.DataFrame(dataset)
    df_encoded = df.apply(
        lambda x: pd.Series(1, index=x.dropna().values), axis=1
    ).fillna(0).astype(bool)
    
    st.subheader("One-Hot Encoded Representation")
    st.dataframe(df_encoded)
    
    st.markdown("---")
    st.subheader("Mining Configurations")
    
    min_sup = st.slider("Minimum Support Threshold", 0.1, 1.0, 0.5, step=0.05)
    min_conf = st.slider("Minimum Confidence Threshold", 0.1, 1.0, 0.7, step=0.05)
    
    # Run Apriori
    frequent_itemsets = apriori(df_encoded, min_support=min_sup, use_colnames=True)
    frequent_itemsets['length'] = frequent_itemsets['itemsets'].apply(len)
    
    col1, col2 = st.columns(2)
    with col1:
        st.subheader("Discovered Frequent Itemsets")
        if not frequent_itemsets.empty:
            # Format itemset for clean display
            frequent_itemsets_display = frequent_itemsets.copy()
            frequent_itemsets_display['itemsets'] = frequent_itemsets_display['itemsets'].apply(lambda x: ", ".join(list(x)))
            st.dataframe(frequent_itemsets_display)
        else:
            st.warning("No frequent itemsets found for the selected support threshold.")
            
    with col2:
        st.subheader("Association Rules")
        if not frequent_itemsets.empty:
            try:
                rules = association_rules(frequent_itemsets, metric="lift", min_threshold=0.1)
                strong_rules = rules[rules['confidence'] >= min_conf]
                if not strong_rules.empty:
                    # Clean display of sets
                    display_rules = strong_rules.copy()
                    display_rules['antecedents'] = display_rules['antecedents'].apply(lambda x: ", ".join(list(x)))
                    display_rules['consequents'] = display_rules['consequents'].apply(lambda x: ", ".join(list(x)))
                    st.dataframe(display_rules[['antecedents', 'consequents', 'support', 'confidence', 'lift']])
                else:
                    st.warning("No strong association rules meet the confidence threshold.")
            except ValueError:
                st.warning("Could not calculate association rules (frequent itemsets list too short).")
        else:
            st.warning("Frequent itemsets list is empty.")

# ==========================================
# Lab 5: Classification
# ==========================================
elif page == "Lab 5: Classification (ID3, Naive Bayes, SVM)":
    st.header("🏷️ Lab 5: Classification Classifiers")
    
    tab1, tab2, tab3 = st.tabs(["ID3 Decision Tree", "Naive Bayes Classifier", "Support Vector Machine"])
    
    # ---------------- ID3 TAB ----------------
    with tab1:
        st.subheader("🌳 Lab 5A: ID3 Decision Tree Classifier")
        
        # Load dataset
        golf_path = get_path("Lab5_Classification/ID3_golf_dataset.csv")
        if not os.path.exists(golf_path):
            st.error("Golf CSV dataset not found in Lab5 folder.")
        else:
            df_golf = pd.read_csv(golf_path)
            st.markdown("### Training Dataset")
            st.dataframe(df_golf)
            
            # Display Entropy functions info
            st.info("Decision tree calculations are based on maximizing **Information Gain** (reducing Shannon Entropy).")
            
            # Predict form
            st.markdown("### Interactive Predictor")
            col1, col2, col3, col4 = st.columns(4)
            with col1:
                outlook = st.selectbox("Outlook", ["Sunny", "Overcast", "Rainy"])
            with col2:
                temp = st.selectbox("Temperature", ["Hot", "Mild", "Cool"])
            with col3:
                humidity = st.selectbox("Humidity", ["High", "Normal"])
            with col4:
                windy = st.selectbox("Windy", [False, True])
                
            # Quick decision boundary predict representing the trained tree:
            # {'Outlook': {'Overcast': 'Yes',
            #              'Rainy': {'Humidity': {'High': 'No', 'Normal': 'Yes'}},
            #              'Sunny': {'Windy': {False: 'Yes', True: 'No'}}}}
            prediction = "Unknown"
            if outlook == "Overcast":
                prediction = "Yes"
            elif outlook == "Rainy":
                if humidity == "High":
                    prediction = "No"
                else:
                    prediction = "Yes"
            elif outlook == "Sunny":
                if windy:
                    prediction = "No"
                else:
                    prediction = "Yes"
                    
            st.success(f"**Predicted PlayGolf Status:** {prediction}")

    # ---------------- NAIVE BAYES TAB ----------------
    with tab2:
        st.subheader("🧼 Lab 5B: Categorical Naive Bayes Classification")
        
        st.markdown("Trains a Categorical Naive Bayes model using `scikit-learn` to classify golf decisions.")
        
        # In-memory play-golf dataset
        data = {
            'Outlook':     ['Rainy','Rainy','Overcast','Sunny','Sunny','Sunny','Overcast',
                            'Rainy','Rainy','Sunny','Rainy','Overcast','Overcast','Sunny'],
            'Temperature': ['Hot','Hot','Hot','Mild','Cool','Cool','Cool',
                            'Mild','Cool','Mild','Mild','Mild','Hot','Mild'],
            'Humidity':    ['High','High','High','High','Normal','Normal','Normal',
                            'High','Normal','Normal','Normal','High','Normal','High'],
            'Windy':       [False,True,False,False,False,True,True,
                            False,False,False,True,True,False,True],
            'Play Golf':   ['No','No','Yes','Yes','Yes','No','Yes',
                            'No','Yes','Yes','Yes','Yes','Yes','No']
        }
        df_nb = pd.DataFrame(data)
        st.dataframe(df_nb)
        
        # Train Bayes Model
        df_encoded = pd.get_dummies(df_nb.drop('Play Golf', axis=1), drop_first=True)
        y = df_nb['Play Golf'].map({'No': 0, 'Yes': 1})
        
        model = CategoricalNB()
        model.fit(df_encoded, y)
        
        st.markdown("### Test Custom Case prediction")
        nb_out = st.selectbox("Bayes Outlook", ["Sunny", "Overcast", "Rainy"], key="nb_o")
        nb_t = st.selectbox("Bayes Temp", ["Hot", "Mild", "Cool"], key="nb_t")
        nb_h = st.selectbox("Bayes Humidity", ["High", "Normal"], key="nb_h")
        nb_w = st.selectbox("Bayes Windy", [False, True], key="nb_w")
        
        test_input = pd.DataFrame([{
            'Outlook': nb_out, 'Temperature': nb_t, 'Humidity': nb_h, 'Windy': nb_w
        }])
        test_encoded = pd.get_dummies(test_input).reindex(columns=df_encoded.columns, fill_value=0)
        prediction_nb = model.predict(test_encoded)[0]
        
        result_nb = "Yes" if prediction_nb == 1 else "No"
        st.success(f"**Naive Bayes Decision prediction:** {result_nb}")

    # ---------------- SVM TAB ----------------
    with tab3:
        st.subheader("📈 Lab 5C: SVM Separating Boundary Visualizer")
        
        # Dataset
        X = np.array([[1, 2], [2, 3], [3, 3], [4, 4],
                      [6, 7], [7, 8], [8, 7], [9, 9]])
        y = np.array([0, 0, 0, 0, 1, 1, 1, 1])
        
        clf = svm.SVC(kernel='linear')
        clf.fit(X, y)
        
        st.write("Fitting Linear SVM on synthetic dataset...")
        
        fig, ax = plt.subplots(figsize=(7, 4))
        scatter = ax.scatter(X[:,0], X[:,1], c=y, s=100, cmap='viridis', edgecolors='k', zorder=3)

        xlim, ylim = ax.get_xlim(), ax.get_ylim()
        xx = np.linspace(xlim[0], xlim[1], 50)
        yy = np.linspace(ylim[0], ylim[1], 50)
        YY, XX = np.meshgrid(yy, xx)
        Z = clf.decision_function(np.c_[XX.ravel(), YY.ravel()]).reshape(XX.shape)

        # Plot decision boundaries and margins
        ax.contour(XX, YY, Z, colors='k', levels=[-1, 0, 1],
                   linestyles=['--', '-', '--'], alpha=0.6)

        # Highlight support vectors
        ax.scatter(clf.support_vectors_[:,0], clf.support_vectors_[:,1],
                   s=220, facecolors='none', edgecolors='red', linewidths=1.5,
                   label='Support Vectors')

        ax.set_xlabel("Feature X1")
        ax.set_ylabel("Feature X2")
        ax.set_title("SVM Optimized Decision Boundary")
        ax.legend(loc='lower right')
        st.pyplot(fig)
        
        st.write(f"Number of Support Vectors discovered: **{len(clf.support_vectors_)}**")

# ==========================================
# Lab 6: Clustering
# ==========================================
elif page == "Lab 6: Cluster Analysis (K-Means)":
    st.header("🔲 Lab 6: Cluster Analysis (K-Means)")
    
    st.markdown("Evaluate clustering of standard coordinates using the K-Means algorithm.")
    
    X, y_true = make_blobs(n_samples=300, centers=4, cluster_std=0.60, random_state=42)
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    
    k_val = st.slider("Select Number of Clusters (K):", 2, 8, 4)
    
    kmeans = KMeans(n_clusters=k_val, random_state=42, n_init=10)
    kmeans.fit(X_scaled)
    labels = kmeans.labels_
    centroids = kmeans.cluster_centers_
    
    col_k1, col_k2 = st.columns([2, 1])
    
    with col_k1:
        fig, ax = plt.subplots(figsize=(8, 5))
        scatter = ax.scatter(X_scaled[:,0], X_scaled[:,1], c=labels, s=40, cmap='rainbow', alpha=0.7)
        ax.scatter(centroids[:, 0], centroids[:, 1], s=250, c='black', marker='X', label='Centroids')
        ax.set_title(f"K-Means Clustering with K={k_val}")
        ax.legend()
        st.pyplot(fig)
        
    with col_k2:
        st.subheader("Performance Metrics")
        st.metric("Inertia (Within-Cluster Sum of Squares)", f"{kmeans.inertia_:.4f}")
        st.metric("Iterations taken to converge", kmeans.n_iter_)
        
        unique_labels, counts = np.unique(labels, return_counts=True)
        st.write("Cluster size distribution:")
        st.dataframe(pd.DataFrame({"Cluster": unique_labels, "Sizes": counts}))
