from collections import deque

def bfs(graph, start, goal):
    # Step counter
    step = 1
    
    # Queue for BFS
    queue = deque([start])
    
    # To keep track of the path taken
    path = []

    print(f"Step {step}): {list(queue)}")
    
    while queue:
        node = queue.popleft()
        path.append(node)
        
        if node == goal:
            print(f"Step {step}): {list(queue)} -> Goal state found! (value dequeued...)")
            break

        # Add the neighbors to the queue
        for neighbor in graph[node]:
            if neighbor not in path and neighbor not in queue:
                queue.append(neighbor)
        
        step += 1
        print(f"Step {step}): {list(queue)}")
    
    print(f"Path followed = {path}")

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

# Run BFS
bfs(graph, start, goal)
