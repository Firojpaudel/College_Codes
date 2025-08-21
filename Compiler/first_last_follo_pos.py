from collections import defaultdict

class Node:
    def __init__(self, symbol):
        self.symbol = symbol
        self.left = None
        self.right = None
        self.firstpos = set()
        self.lastpos = set()
        self.nullable = False
        self.position = -1

def compute_first_last(root):
    if root is None:
        return
    if root.left is None and root.right is None:  # leaf
        if root.position != -1:
            root.firstpos.add(root.position)
            root.lastpos.add(root.position)
        root.nullable = False
        return
    compute_first_last(root.left)
    compute_first_last(root.right)
    if root.symbol == '|':
        root.firstpos = root.left.firstpos | root.right.firstpos
        root.lastpos = root.left.lastpos | root.right.lastpos
        root.nullable = root.left.nullable or root.right.nullable
    elif root.symbol == '.':
        root.firstpos = root.left.firstpos.copy()
        if root.left.nullable:
            root.firstpos |= root.right.firstpos
        root.lastpos = root.right.lastpos.copy()
        if root.right.nullable:
            root.lastpos |= root.left.lastpos
        root.nullable = root.left.nullable and root.right.nullable
    elif root.symbol == '*':
        root.firstpos = root.left.firstpos.copy()
        root.lastpos = root.left.lastpos.copy()
        root.nullable = True

def compute_followpos(root, followpos):
    if root is None:
        return
    if root.symbol == '.':
        for i in root.left.lastpos:
            followpos[i] |= root.right.firstpos
    elif root.symbol == '*':
        for i in root.lastpos:
            followpos[i] |= root.firstpos
    compute_followpos(root.left, followpos)
    compute_followpos(root.right, followpos)

def parse_regex(s, pos, leaf_count, pos_to_symbol):
    if pos[0] >= len(s):
        return None
    if s[pos[0]] == '(':
        pos[0] += 1
        left = parse_regex(s, pos, leaf_count, pos_to_symbol)
        op = s[pos[0]]
        pos[0] += 1
        right = parse_regex(s, pos, leaf_count, pos_to_symbol)
        root = Node(op)
        root.left = left
        root.right = right
        pos[0] += 1  # skip )
        if pos[0] < len(s) and s[pos[0]] == '*':
            star = Node('*')
            star.left = root
            pos[0] += 1
            return star
        return root
    elif s[pos[0]].isalnum():
        sym = s[pos[0]]
        leaf = Node(sym)
        leaf.position = leaf_count[0]
        pos_to_symbol[leaf_count[0]] = sym
        leaf_count[0] += 1
        pos[0] += 1
        if pos[0] < len(s) and s[pos[0]] == '*':
            star = Node('*')
            star.left = leaf
            pos[0] += 1
            return star
        return leaf
    return None

print(f"{"="*10}firstpos(), lastpos() and followpos(){"="*10}")

print("Enter a fully parenthesized regex (e.g., ((a.b)|c)* ) (type 'exit' to quit):")
while True:
    user_input = input("Expression: ").strip()
    if user_input.lower() == 'exit':
        break
    if not user_input:
        print("Please enter an expression!")
        continue
    pos = [0]
    leaf_count = [1]
    pos_to_symbol = {}
    root = parse_regex(user_input, pos, leaf_count, pos_to_symbol)
    if root is None or pos[0] != len(user_input):
        print("Invalid expression!")
        continue
    compute_first_last(root)
    first_str = '{ ' + ', '.join(map(str, sorted(root.firstpos))) + ' }'
    last_str = '{ ' + ', '.join(map(str, sorted(root.lastpos))) + ' }'
    print("\nFirstpos: " + first_str)
    print("Lastpos: " + last_str)
    followpos = defaultdict(set)
    compute_followpos(root, followpos)
    # Displaying followpos in tabular format
    print("\nPos | Symbol | Followpos")
    print("----|--------|----------")
    for k in sorted(pos_to_symbol):
        sym = pos_to_symbol[k]
        foll = followpos[k]
        foll_str = '{ ' + ', '.join(map(str, sorted(foll))) + ' }' if foll else '{}'
        print(f"{k:<3} | {sym:<6} | {foll_str}")
    print()