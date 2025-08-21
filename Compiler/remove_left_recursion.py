from collections import OrderedDict
import re

class GrammarUtils:
    def __init__(self, grammar):
        self.grammar = grammar

    def direct_left_corner(self, k):
        return [r[0] if r else None for r in self.grammar[k]]

    def has_direct_left_recursion(self):
        for k in self.grammar:
            lc = self.direct_left_corner(k)
            if k in [x for x in lc if x]:
                return True
        return False

    def remove_direct_recursion(self, A):
        Aprime = A + "'"
        while Aprime in self.grammar:
            Aprime += "'"
        alphas = [rule[1:] for rule in self.grammar[A] if rule and rule[0] == A]
        betas = [rule for rule in self.grammar[A] if not rule or (rule and rule[0] != A)]
        if alphas:
            # A' → alpha A' | ε
            self.grammar[Aprime] = [alpha + [Aprime] for alpha in alphas] + [[]]
            # A → beta A'
            self.grammar[A] = [beta + [Aprime] for beta in betas] if betas else [[Aprime]]
        else:
            self.grammar[A] = betas if betas else [[]]

    def remove_left_recursion(self):
        keylst = list(self.grammar.keys())
        for i in range(len(keylst)):
            Ai = keylst[i]
            for j in range(i):
                Aj = keylst[j]
                to_expand = [rule for rule in self.grammar[Ai] if rule and rule[0] == Aj]
                if to_expand:
                    for rule in to_expand:
                        self.grammar[Ai].remove(rule)
                        beta = rule[1:]
                        for aj_rule in self.grammar[Aj]:
                            new_rule = aj_rule + beta if aj_rule else beta
                            self.grammar[Ai].append(new_rule)
            self.remove_direct_recursion(Ai)


def tokenize(prod: str):
    return re.findall(r"[A-Z][A-Za-z0-9]*|[^A-Z\s]", prod)

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
        if not nt:
            print("Non-terminal cannot be empty!")
            return None
        print(f"How many productions for {nt}? ", end="")
        try:
            prod_count = int(input())
            if prod_count <= 0:
                print("Please enter a positive number of productions!")
                return None
        except ValueError:
            print("Invalid input! Please enter a number.")
            return None
        prods = []
        for i in range(prod_count):
            print(f"Enter production {i+1} for {nt}: ", end="")
            prod = input().strip()
            if not prod:
                print("Production cannot be empty!")
                return None
            if prod == 'epsilon':
                prods.append([])
            else:
                prods.append(tokenize(prod))  
        grammar[nt] = prods
    return grammar


print("==================================================")
print("Removing left recursion (direct and indirect)")
print("==================================================")
print("Enter number of non-terminals, then for each non-terminal enter its name, number of productions, and productions one per line. Enter blank line to process, type 'exit' to quit:")

while True:
    grammar = parse_grammar()
    if not grammar:
        print("Invalid grammar!")
        continue
    if input("Process this grammar? (yes/no): ").lower().strip() != 'yes':
        continue
    
    print("\nOriginal Grammar:")
    print("Non-terminal | Productions")
    print("-------------|------------")
    for nt, prods in grammar.items():
        prod_str = ' | '.join(' '.join(p) if p else 'epsilon' for p in prods)
        print(f"{nt:<13} | {prod_str}")
    
    gu = GrammarUtils(grammar)
    gu.remove_left_recursion()
    
    print("\nGrammar after removing left recursion:")
    print("Non-terminal | Productions")
    print("-------------|------------")
    for nt, prods in gu.grammar.items():
        prod_str = ' | '.join(' '.join(p) if p else 'epsilon' for p in prods)
        print(f"{nt:<13} | {prod_str}")
    print()