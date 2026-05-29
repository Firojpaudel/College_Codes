import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import CategoricalNB
from sklearn.metrics import accuracy_score, classification_report

def main():
    print("=" * 50)
    print(" LAB 5B: NAIVE BAYES CLASSIFICATION ")
    print("=" * 50)

    # 1. Dataset Initialization
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

    df = pd.DataFrame(data)
    print("[INFO] Dataset successfully loaded in-memory.")

    # 2. Data Preprocessing
    df_encoded = pd.get_dummies(df.drop('Play Golf', axis=1), drop_first=True)
    y = df['Play Golf'].map({'No': 0, 'Yes': 1})

    X_train, X_test, y_train, y_test = train_test_split(
        df_encoded, y, test_size=0.2, random_state=42
    )
    
    # 3. Model Training
    print("[INFO] Training Categorical Naive Bayes model...")
    model = CategoricalNB()
    model.fit(X_train, y_train)
    
    # 4. Evaluation
    y_pred = model.predict(X_test)
    print(f"\n[RESULTS] Model Accuracy: {accuracy_score(y_test, y_pred) * 100:.2f}%")
    print("\n--- Classification Report ---")
    print(classification_report(y_test, y_pred, target_names=['No (0)', 'Yes (1)']))

    # 5. Inference / Prediction
    print("\n[PREDICTION TEST]")
    test_input = pd.DataFrame([{
        'Outlook': 'Sunny', 'Temperature': 'Cool', 'Humidity': 'High', 'Windy': False
    }])
    
    test_encoded = pd.get_dummies(test_input).reindex(columns=df_encoded.columns, fill_value=0)
    prediction = model.predict(test_encoded)
    
    print(f"Condition: {test_input.iloc[0].to_dict()}")
    print(f"Prediction (Play Golf): {'Yes' if prediction[0] == 1 else 'No'}")

if __name__ == "__main__":
    main()
