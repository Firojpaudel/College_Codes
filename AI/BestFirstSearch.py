import heapq

class Node:
    def __init__(self, name, cost=0, total_cost=0):
        self.name = name
        self.cost = cost
        self.total_cost = total_cost
        self.parent = None

    def __lt__(self, other):
        return self.total_cost < other.total_cost

def best_first_search(graph, start, goal):
    # Initialize the OPEN and CLOSED lists
    open_list = []
    closed_list = set()
    
    # Start from the initial node
    start_node = Node(start, cost=0, total_cost=0)
    goal_node = Node(goal)
    
    # Add the start node to the OPEN list
    heapq.heappush(open_list, start_node)
    
    while open_list:
        # Select the node with the lowest total cost
        current_node = heapq.heappop(open_list)
        closed_list.add(current_node.name)
        
        # If the goal is found, backtrack to find the path and calculate the cost
        if current_node.name == goal_node.name:
            path = []
            total_cost = current_node.total_cost
            while current_node:
                path.append(current_node.name)
                current_node = current_node.parent
            return path[::-1], total_cost  # Return reversed path and total cost
        
        # Expand the current node to all its children
        if current_node.name in graph:
            for (neighbor, cost) in graph[current_node.name]:
                if neighbor in closed_list:
                    continue
                
                neighbor_node = Node(neighbor, cost, current_node.total_cost + cost)
                neighbor_node.parent = current_node
                
                heapq.heappush(open_list, neighbor_node)
    
    return False, 0  # Return False if no path is found

def main():
    # Get user input for the tree (not limited to binary)
    graph = {}
    num_nodes = int(input("Enter the number of nodes: "))
    
    for _ in range(num_nodes):
        node = input("Enter the node name: ")
        graph[node] = []
        
        num_edges = int(input(f"Enter the number of children for {node}: "))
        for _ in range(num_edges):
            child = input(f"Enter the name of the child node connected to {node}: ")
            cost = int(input(f"Enter the cost to move from {node} to {child}: "))
            graph[node].append((child, cost))
    
    start = input("Enter the start node: ")
    goal = input("Enter the goal node: ")
    
    path, total_cost = best_first_search(graph, start, goal)
    
    if path:
        print(f"Path found: {' -> '.join(path)}")
        print(f"Total Cost: {total_cost}")
    else:
        print("No path found.")

if __name__ == "__main__":
    main()
