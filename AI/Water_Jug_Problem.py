def water_jug_problem(capacity_A, capacity_B, target):
    # Initialize the jugs
    A, B = 0, 0

    # Dictionary of rules
    rules = {
        0: "Initial State",
        1: "Fill A",
        2: "Fill B",
        3: "Empty A",
        4: "Empty B",
        5: "Pour A to B",
        6: "Pour B to A"
    }

    # To store the table of steps
    table = [{"Gallons in A": A, "Gallons in B": B, "Rule Applied": rules[0]}]

    while (A != target) and (B != target):
        # If A is empty, fill A
        if A == 0:
            A = capacity_A
            table.append({"Gallons in A": A, "Gallons in B": B, "Rule Applied": rules[1]})
        
        # If B is full, empty B
        elif B == capacity_B:
            B = 0
            table.append({"Gallons in A": A, "Gallons in B": B, "Rule Applied": rules[4]})
        
        # Pour water from A to B until B is full or A is empty
        else:
            transfer = min(A, capacity_B - B)
            A -= transfer
            B += transfer
            table.append({"Gallons in A": A, "Gallons in B": B, "Rule Applied": rules[5]})
        
        # Check if we've reached the target
        if A == target or B == target:
            break
    
    return table

# Take user input for jug sizes and target amount
capacity_A = int(input("Enter the capacity of A-gallon jug: "))
capacity_B = int(input("Enter the capacity of B-gallon jug: "))
target = int(input("Enter the target amount to measure: "))

# Get the steps
steps_table = water_jug_problem(capacity_A, capacity_B, target)

# Print the steps in tabular format
print("{:<15} {:<15} {:<20}".format('Gallons in A', 'Gallons in B', 'Rule Applied'))
for step in steps_table:
    print("{:<15} {:<15} {:<20}".format(step['Gallons in A'], step['Gallons in B'], step['Rule Applied']))
