import pandas as pd
import math
from pprint import pprint
from collections import Counter
import glob

# --- Entropy Utilities ---
def entropy(probs):
    return sum(-p * math.log2(p) for p in probs if p > 0)

def entropy_of_list(ls):
    cnt = Counter(ls)
    probs = [v / len(ls) for v in cnt.values()]
    return entropy(probs)

def information_gain(df, split_attr, target_attr):
    total_entropy = entropy_of_list(df[target_attr])
    n = len(df)
    weighted_entropy = sum(
        (len(subset) / n) * entropy_of_list(subset[target_attr])
        for _, subset in df.groupby(split_attr)
    )
    return total_entropy - weighted_entropy

# --- Core ID3 Logic ---
def id3(df, target_attr, attr_names, default_class=None):
    cnt = Counter(df[target_attr])
    
    if len(cnt) == 1:
        return next(iter(cnt))
    if df.empty or not attr_names:
        return default_class
    
    default_class = max(cnt, key=cnt.get)
    
    # Pick the attribute with max info gain
    gains = {attr: information_gain(df, attr, target_attr) for attr in attr_names}
    best_attr = max(gains, key=gains.get)
    
    tree = {best_attr: {}}
    remaining = [a for a in attr_names if a != best_attr]
    
    for val, subset in df.groupby(best_attr):
        tree[best_attr][val] = id3(subset, target_attr, remaining, default_class)
    
    return tree

def classify(tree, instance):
    if not isinstance(tree, dict):
        return tree
    attr = next(iter(tree))
    val = instance.get(attr)
    subtree = tree[attr].get(val, "Unknown")
    return classify(subtree, instance)

def main():
    print("=" * 50)
    print(" LAB 5A: ID3 DECISION TREE ")
    print("=" * 50)

    dataset_file = glob.glob("*ID3*.csv")
    if not dataset_file:
        print("[ERROR] Golf dataset not found!")
        return

    df = pd.read_csv(dataset_file[0])
    target = df.keys()[-1]            
    attributes = list(df.keys()[:-1]) 
    
    print(f"[INFO] Dataset shape: {df.shape}")
    print(f"[INFO] Target: '{target}', Attributes: {attributes}\n")
    
    tree = id3(df, target, attributes)
    
    print("=== Generated Decision Tree ===")
    pprint(tree, width=40)
    
    # Predict a sample instance
    test_instance = {'Outlook': 'Sunny', 'Temperature': 'Cool', 'Humidity': 'High', 'Windy': bool("False")}
    result = classify(tree, test_instance)
    
    print(f"\n[PREDICTION]")
    print(f"Input: {test_instance}")
    print(f"Result (PlayGolf) => {result}")

if __name__ == "__main__":
    main()
