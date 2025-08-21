from collections import defaultdict

# ====== Helper Functions ======
def compute_first(symbol, productions, first, visited):
    if symbol in first:
        return first[symbol]
    first[symbol] = set()
    for prod in productions[symbol]:
        if prod == 'epsilon':
            first[symbol].add('epsilon')
        else:
            symbols = []
            i = 0
            while i < len(prod):
                if i + 1 < len(prod) and prod[i+1] == "'":
                    symbols.append(prod[i:i+2])
                    i += 2
                else:
                    symbols.append(prod[i])
                    i += 1
            for s in symbols:
                if s.isupper() or "'" in s:
                    if s not in visited:
                        visited.add(s)
                        first[symbol] |= compute_first(s, productions, first, visited)
                        visited.remove(s)
                    if 'epsilon' not in first[s]:
                        break
                else:
                    first[symbol].add(s)
                    break
            else:
                first[symbol].add('epsilon')
    return first[symbol]

def compute_follow(start_symbol, productions, first, follow):
    follow[start_symbol].add('$')
    changed = True
    while changed:
        changed = False
        for A in productions:
            for prod in productions[A]:
                symbols = []
                i = 0
                while i < len(prod):
                    if i + 1 < len(prod) and prod[i+1] == "'":
                        symbols.append(prod[i:i+2])
                        i += 2
                    else:
                        symbols.append(prod[i])
                        i += 1
                for idx, B in enumerate(symbols):
                    if B.isupper() or "'" in B:
                        after = symbols[idx+1:]
                        temp_follow = set()
                        if after:
                            for sym in after:
                                if sym.isupper() or "'" in sym:
                                    temp_follow |= first[sym] - {'epsilon'}
                                    if 'epsilon' not in first[sym]:
                                        break
                                else:
                                    temp_follow.add(sym)
                                    break
                            else:
                                temp_follow |= follow[A]
                        else:
                            temp_follow |= follow[A]
                        if not temp_follow <= follow[B]:
                            follow[B] |= temp_follow
                            changed = True
    return follow

# ====== Grammar Input ======
productions = defaultdict(list)
non_terminals = int(input("How many non-terminals? "))
for _ in range(non_terminals):
    nt = input("Enter non-terminal: ").strip()
    prod_count = int(input(f"How many productions for {nt}? "))
    for i in range(prod_count):
        prod = input(f"Enter production {i+1} for {nt}: ").strip()
        productions[nt].append(prod)

start_symbol = list(productions.keys())[0]

# ====== FIRST and FOLLOW ======
first = {}
for nt in productions:
    compute_first(nt, productions, first, set())

follow = defaultdict(set)
compute_follow(start_symbol, productions, first, follow)

# ====== LL(1) Parsing Table ======
table = defaultdict(dict)
for nt in productions:
    for prod in productions[nt]:
        first_prod = set()
        if prod == 'epsilon':
            first_prod.add('epsilon')
        else:
            symbols = []
            i = 0
            while i < len(prod):
                if i + 1 < len(prod) and prod[i+1] == "'":
                    symbols.append(prod[i:i+2])
                    i += 2
                else:
                    symbols.append(prod[i])
                    i += 1
            for s in symbols:
                if s.isupper() or "'" in s:
                    first_prod |= first[s] - {'epsilon'}
                    if 'epsilon' not in first[s]:
                        break
                else:
                    first_prod.add(s)
                    break
            else:
                first_prod.add('epsilon')
        for terminal in first_prod - {'epsilon'}:
            table[nt][terminal] = prod
        if 'epsilon' in first_prod:
            for terminal in follow[nt]:
                table[nt][terminal] = prod

# ====== Input String ======
input_string = input("Enter input string: ").strip() + '$'
stack = ['$']
stack.append(start_symbol)
pointer = 0

# ====== Parsing ======
print("\n{:<20} {:<20} {:<20}".format("STACK", "INPUT", "ACTION"))

while stack:
    top = stack[-1]
    current = input_string[pointer]

    if top == current == '$':
        print("{:<20} {:<20} {:<20}".format(''.join(stack), input_string[pointer:], "ACCEPT ✅"))
        break
    elif top == current:
        stack.pop()
        pointer += 1
        print("{:<20} {:<20} {:<20}".format(' '.join(stack), input_string[pointer:], "MATCH"))
    elif top.isupper() or "'" in top:
        if current in table[top]:
            action = table[top][current]
            print("{:<20} {:<20} {:<20}".format(' '.join(stack), input_string[pointer:], f"{top}->{action}"))
            stack.pop()
            if action != 'epsilon':
                # push symbols in reverse, treating E' as single symbol
                symbols_to_push = []
                i = 0
                while i < len(action):
                    if i + 1 < len(action) and action[i+1] == "'":
                        symbols_to_push.append(action[i:i+2])
                        i += 2
                    else:
                        symbols_to_push.append(action[i])
                        i += 1
                for sym in reversed(symbols_to_push):
                    stack.append(sym)
        else:
            print("{:<20} {:<20} {:<20}".format(' '.join(stack), input_string[pointer:], "ERROR ❌"))
            break
    else:
        print("{:<20} {:<20} {:<20}".format(' '.join(stack), input_string[pointer:], "ERROR ❌"))
        break