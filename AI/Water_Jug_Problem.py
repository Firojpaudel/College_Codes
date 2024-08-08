from collections import deque

def water_jug_solver(capacity1, capacity2, target):
    """Solves the water jug problem using BFS."""
    # Initialize the queue with the starting state
    queue = deque([(0, 0)])  # (amount in jug1, amount in jug2)
    visited = set()
    visited.add((0, 0))
    parent = { (0, 0): None }
    
    while queue:
        jug1, jug2 = queue.popleft()
        
        # Check if we have reached the target
        if jug1 == target or jug2 == target:
            print("Solution found:")
            return reconstruct_path((jug1, jug2), parent)
        
        # Generate all possible states
        states = [
            (capacity1, jug2),  # Fill jug1
            (jug1, capacity2),  # Fill jug2
            (0, jug2),          # Empty jug1
            (jug1, 0),          # Empty jug2
            (min(capacity1, jug1 + jug2), jug2 - (min(capacity1, jug1 + jug2) - jug1)),  # Pour jug2 into jug1
            (jug1 - (min(capacity2, jug1 + jug2) - jug2), min(capacity2, jug1 + jug2))   # Pour jug1 into jug2
        ]
        
        for state in states:
            if state not in visited:
                visited.add(state)
                queue.append(state)
                parent[state] = (jug1, jug2)
    
    print("No solution found.")
    return []

def reconstruct_path(state, parent):
    """Reconstructs the path from the end state to the start state."""
    path = []
    while state:
        path.append(state)
        state = parent[state]
    path.reverse()
    
    for step in path:
        print(f"Jug1: {step[0]}, Jug2: {step[1]}")
    
    return path

def main():
    capacity1 = int(input("Enter the capacity of jug 1: "))
    capacity2 = int(input("Enter the capacity of jug 2: "))
    target = int(input("Enter the target amount of water: "))
    
    if target > max(capacity1, capacity2):
        print("Target is greater than both jug capacities. No solution possible.")
        return

    print("\nSolving the Water Jug Problem...")
    water_jug_solver(capacity1, capacity2, target)

if __name__ == "__main__":
    main()
