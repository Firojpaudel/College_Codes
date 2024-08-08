def tower_of_hanoi(n, source, target, auxiliary, steps):
    """Recursive function to solve Tower of Hanoi and record steps."""
    if n == 1:
        steps.append(f"Move disk from rod {source} to rod {target}")
        return

    tower_of_hanoi(n-1, source, auxiliary, target, steps)
    steps.append(f"Move disk from rod {source} to rod {target}")
    tower_of_hanoi(n-1, auxiliary, target, source, steps)

def main():
    n = int(input("Enter the number of disks: "))
    if n <= 0:
        print("Number of disks must be a positive integer.")
        return

    steps = []
    tower_of_hanoi(n, 'A', 'C', 'B', steps)
    
    print("\nSteps to solve the Tower of Hanoi:")
    for i, step in enumerate(steps, start=1):
        print(f"Step {i}: {step}")
    
    print(f"\nTotal number of steps: {len(steps)}")

if __name__ == "__main__":
    main()
