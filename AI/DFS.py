def dfs(graph, start, goal):
    # Step counter
    step = 1
    
    # Stack for DFS (LIFO)
    stack = [start]
    
    # To keep track of the path taken
    path = []

    print(f"Step {step}): {list(stack)}")
    
    while stack:
        node = stack.pop()
        path.append(node)

        if node == goal:
            print(f"Step {step}): {list(stack)} -> Found Goal state")
            break

        # Add the neighbors to the stack in reverse order for correct DFS
        for neighbor in reversed(graph[node]):
            if neighbor not in path and neighbor not in stack:
                stack.append(neighbor)
        
        step += 1
        print(f"Step {step}): {list(stack)}")
    
    print(f"Path: {' -> '.join(path)}")

# Function to take graph input from the user
def input_graph():
    graph = {}
    num_nodes = int(input("Enter the number of nodes: "))
    
    for _ in range(num_nodes):
        node = input("Enter the node: ")
        neighbors = input(f"Enter the neighbors of {node} (comma-separated): ").split(',')
        graph[node] = [n.strip() for n in neighbors if n.strip()]

    return graph

# Get the graph from user input
graph = input_graph()

# Define the start and goal nodes
start = input("Enter the start node: ")
goal = input("Enter the goal node: ")

# Run DFS
dfs(graph, start, goal)
