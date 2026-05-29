import logging
from typing import List

import pandas as pd
from mlxtend.frequent_patterns import apriori, association_rules

logging.basicConfig(level=logging.INFO, format="%(levelname)s: %(message)s")


def encode_transactions(dataset: List[List[str]]) -> pd.DataFrame:
    """One-hot encode the raw transaction dataset."""
    df = pd.DataFrame(dataset)
    df_encoded = df.apply(
        lambda x: pd.Series(1, index=x.dropna().values), axis=1
    ).fillna(0).astype(bool)
    return df_encoded


def main() -> None:
    """Main execution of Apriori algorithm and association rule mining."""
    print("=" * 50)
    print(" LAB 4: MINING FREQUENT PATTERNS (APRIORI) ")
    print("=" * 50)

    # 1. Dataset Generation
    dataset = [
        ['A', 'B', 'C'],
        ['A', 'C'],
        ['A', 'D'],
        ['B', 'E', 'F']
    ]

    logging.info("Raw Transactions:")
    for i, transaction in enumerate(dataset, 1):
        print(f"  T{i}: {transaction}")

    # 2. One-Hot Encoding
    logging.info("Encoding Transactions...")
    df_encoded = encode_transactions(dataset)
    print(df_encoded)

    # 3. Apriori Execution
    logging.info("Running Apriori (min_support = 0.5)...")
    frequent_itemsets = apriori(df_encoded, min_support=0.5, use_colnames=True)
    frequent_itemsets['length'] = frequent_itemsets['itemsets'].apply(len)
    
    print("\n=== Frequent Itemsets ===")
    print(frequent_itemsets.sort_values(by='support', ascending=False))

    # 4. Association Rules Generation
    logging.info("Discovering Association Rules (min_lift >= 0.5)...")
    rules = association_rules(frequent_itemsets, metric="lift", min_threshold=0.5)

    pd.set_option('display.max_columns', None)
    pd.set_option('display.width', None)

    # Filtering strong rules (confidence >= 0.70)
    strong_rules = rules[rules['confidence'] >= 0.7]
    print("\n=== Strong Rules (confidence >= 0.70) ===")
    print(strong_rules[['antecedents', 'consequents', 'support', 'confidence', 'lift']])


if __name__ == "__main__":
    main()
