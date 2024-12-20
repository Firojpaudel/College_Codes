from collections import Counter

def naive_bayes_predict(weather_data, condition):
    # Separate the data by outcome
    yes_data = [row for row in weather_data if row[1] == 'Yes']
    no_data = [row for row in weather_data if row[1] == 'No']

    # Calculate probabilities for each class
    p_yes = len(yes_data) / len(weather_data)
    p_no = len(no_data) / len(weather_data)

    # Count occurrences of conditions in each class
    weather_yes = Counter([row[0] for row in yes_data])
    weather_no = Counter([row[0] for row in no_data])

    # Calculate likelihoods
    p_condition_given_yes = weather_yes[condition] / len(yes_data)
    p_condition_given_no = weather_no[condition] / len(no_data)

    # Apply Naive Bayes formula
    p_yes_given_condition = p_condition_given_yes * p_yes
    p_no_given_condition = p_condition_given_no * p_no

    # Normalize probabilities
    total_prob = p_yes_given_condition + p_no_given_condition
    p_yes_given_condition /= total_prob
    p_no_given_condition /= total_prob

    # Print detailed probabilities
    print("--- Detailed Probability Values ---")
    print(f"P(Yes): {p_yes}")
    print(f"P(No): {p_no}")
    print(f"P(Condition | Yes): {p_condition_given_yes}")
    print(f"P(Condition | No): {p_condition_given_no}")
    print(f"P(Yes | Condition): {p_yes_given_condition}")
    print(f"P(No | Condition): {p_no_given_condition}")
    print("----------------------------------")

    # Return the class with the highest probability
    return 'Yes' if p_yes_given_condition > p_no_given_condition else 'No'

# Example dataset
weather_data = [
    ('Sunny', 'No'),
    ('Overcast', 'Yes'),
    ('Rainy', 'Yes'),
    ('Sunny', 'Yes'),
    ('Sunny', 'Yes'),
    ('Overcast', 'Yes'),
    ('Rainy', 'No'),
    ('Rainy', 'No'),
    ('Sunny', 'Yes'),
    ('Rainy', 'Yes'),
    ('Sunny', 'No'),
    ('Overcast', 'Yes'),
    ('Overcast', 'Yes'),
    ('Rainy', 'No')
]

# Ask user for input
user_condition = input("Enter the weather condition (Sunny, Overcast, Rainy): ")
while user_condition not in ['Sunny', 'Overcast', 'Rainy']:
    print("Invalid input. Please enter 'Sunny', 'Overcast', or 'Rainy'.")
    user_condition = input("Enter the weather condition (Sunny, Overcast, Rainy): ")

# Predict outcome
outcome = naive_bayes_predict(weather_data, user_condition)
print(f"Prediction: Play = {outcome}")
