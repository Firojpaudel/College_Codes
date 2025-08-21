from collections import OrderedDict, defaultdict
import re

class GrammarAnalyzer:
    def __init__(self, grammar):
        self.grammar = grammar
        self.first = defaultdict(set)
        self.follow = defaultdict(set)
        self.start_symbol = next(iter(grammar.keys()))  # first NT = start

    def compute_first(self):
        changed = True
        while changed:
            changed = False
            for nt in self.grammar:
                for prod in self.grammar[nt]:
                    # Empty production => epsilon
                    if not prod:
                        if '' not in self.first[nt]:
                            self.first[nt].add('')
                            changed = True
                        continue

                    for i, symbol in enumerate(prod):
                        if symbol.islower() or not symbol.isalpha():  
                            # Terminal
                            if symbol not in self.first[nt]:
                                self.first[nt].add(symbol)
                                changed = True
                            break
                        else:  
                            # Non-terminal
                            before = len(self.first[nt])
                            self.first[nt].update(self.first[symbol] - {''})
                            if '' not in self.first[symbol]:
                                break
                            if i == len(prod) - 1:  # all symbols nullable
                                self.first[nt].add('')
                            if len(self.first[nt]) > before:
                                changed = True

    def compute_follow(self):
        # Start symbol gets $
        self.follow[self.start_symbol].add('$')

        changed = True
        while changed:
            changed = False
            for nt in self.grammar:
                for prod in self.grammar[nt]:
                    for i, symbol in enumerate(prod):
                        if symbol.isupper():  # only for NTs
                            trailer = set()
                            for j in range(i + 1, len(prod)):
                                nxt = prod[j]
                                if nxt.islower() or not nxt.isalpha():  
                                    if nxt not in self.follow[symbol]:
                                        self.follow[symbol].add(nxt)
                                        changed = True
                                    trailer = set()
                                    break
                                else:
                                    before = len(self.follow[symbol])
                                    self.follow[symbol].update(self.first[nxt] - {''})
                                    if '' in self.first[nxt]:
                                        trailer = trailer.union(self.first[nxt] - {''})
                                        continue
                                    trailer = set()
                                    if len(self.follow[symbol]) > before:
                                        changed = True
                                    break
                            else:
                                # If nothing follows or all nullable, add FOLLOW(nt)
                                before = len(self.follow[symbol])
                                self.follow[symbol].update(self.follow[nt])
                                if len(self.follow[symbol]) > before:
                                    changed = True


def tokenize(prod: str):
    # Terminals are lowercase, operators (+, *, etc.) are terminals too
    return re.findall(r"[A-Z][A-Za-z0-9]*|epsilon|[^A-Z\s]", prod)


def parse_grammar():
    grammar = OrderedDict()
    print("How many non-terminals? ", end="")
    try:
        nt_count = int(input())
        if nt_count <= 0:
            print("Please enter a positive number!")
            return None
    except ValueError:
        print("Invalid input! Please enter a number.")
        return None

    for _ in range(nt_count):
        print("Enter non-terminal: ", end="")
        nt = input().strip()
        if not nt or not nt.isupper():
            print("Non-terminal must be uppercase!")
            return None
        print(f"How many productions for {nt}? ", end="")
        try:
            prod_count = int(input())
            if prod_count <= 0:
                print("Must have at least 1 production!")
                return None
        except ValueError:
            print("Invalid input!")
            return None

        prods = []
        for i in range(prod_count):
            print(f"Enter production {i+1} for {nt}: ", end="")
            prod = input().strip()
            if prod == "epsilon":
                prods.append([])
            else:
                prods.append(tokenize(prod))
        grammar[nt] = prods
    return grammar


# --- MAIN LOOP ---
print("==================================================")
print("Computing FIRST and FOLLOW sets for a grammar")
print("==================================================")

while True:
    grammar = parse_grammar()
    if not grammar:
        print("Invalid grammar!")
        continue
    if input("Process this grammar? (yes/no): ").lower().strip() != 'yes':
        continue

    analyzer = GrammarAnalyzer(grammar)
    analyzer.compute_first()
    analyzer.compute_follow()

    print("\nFIRST Sets:")
    print("Non-terminal | FIRST")
    print("-------------|--------")
    for nt in grammar:
        first_set = analyzer.first[nt]
        formatted = "{ " + ", ".join(sorted(x if x else "epsilon" for x in first_set)) + " }"
        print(f"{nt:<13} | {formatted}")

    print("\nFOLLOW Sets:")
    print("Non-terminal | FOLLOW")
    print("-------------|--------")
    for nt in grammar:
        follow_set = analyzer.follow[nt]
        formatted = "{ " + ", ".join(sorted(follow_set)) + " }"
        print(f"{nt:<13} | {formatted}")
    print()