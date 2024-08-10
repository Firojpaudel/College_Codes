import heapq

class Node:
    def __init__(self, name, parent=None):
        self.name = name
        self.parent = parent
        self.g = 0  # Cost from start node to current node
        self.h = 0  # Heuristic value (estimated cost from current node to goal)
        self.f = 0  # Total cost (g + h)

    def __lt__(self, other):
        return self.f < other.f

def astar(tree, start, goal, heuristic_values):
    # Create start and goal nodes
    start_node = Node(start)
    goal_node = Node(goal)
    
    # Initialize both open and closed lists
    open_list = []
    closed_list = set()
    
    # Add the start node to the open list
    heapq.heappush(open_list, start_node)
    
    # Main loop
    while open_list:
        # Get the node with the lowest f-score
        current_node = heapq.heappop(open_list)
        closed_list.add(current_node.name)
        
        # Goal node is reached
        if current_node.name == goal_node.name:
            return reconstruct_path(current_node)
        
        # Check the neighbors (children)
        for (child_name, cost) in tree.get(current_node.name, []):
            if child_name in closed_list:
                continue
            
            child_node = Node(child_name, current_node)
            child_node.g = current_node.g + cost  # Calculate g value
            child_node.h = heuristic_values.get(child_name, float('inf'))  # Get h value from user input
            child_node.f = child_node.g + child_node.h  # Calculate f value
            
            # If this node is already in the open list with a lower f, skip it
            if not add_to_open(open_list, child_node):
                continue
            
            # Otherwise, add it to the open list
            heapq.heappush(open_list, child_node)
    
    return None  # Return None if no path is found

def add_to_open(open_list, child_node):
    for node in open_list:
        if child_node.name == node.name and child_node.f >= node.f:
            return False
    return True

def reconstruct_path(current_node):
    path = []
    while current_node:
        path.append(current_node.name)
        current_node = current_node.parent
    return path[::-1]  # Return reversed path

# User Input for Tree and Heuristic Values
def get_user_input():
    tree = {}
    heuristic_values = {}

    print("Enter the tree connections (parent -> child, cost). Type 'done' when finished:")
    while True:
        connection = input("Enter connection (format: parent child cost): ")
        if connection == "done":
            break
        parent, child, cost = connection.split()
        cost = int(cost)
        if parent not in tree:
            tree[parent] = []
        tree[parent].append((child, cost))
    
    print("Enter the heuristic values for each node. Type 'done' when finished:")
    while True:
        h_value = input("Enter heuristic value (format: node h_value): ")
        if h_value == "done":
            break
        node, h = h_value.split()
        heuristic_values[node] = int(h)
    
    start = input("Enter the start node: ")
    goal = input("Enter the goal node: ")

    return tree, start, goal, heuristic_values

# Running the code:
tree, start, goal, heuristic_values = get_user_input()
path = astar(tree, start, goal, heuristic_values)

if path:
    print("Path:", " -> ".join(path))
else:
    print("No path found")