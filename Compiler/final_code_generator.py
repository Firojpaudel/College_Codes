class FinalCodeGenerator:
    def __init__(self):
        self.register_count = 0
        self.code = []
        self.register_map = {}

    def new_register(self):
        self.register_count += 1
        return f"R{self.register_count}"

    def generate(self, tac_code):
        for instr in tac_code:
            self.translate(instr)

    def translate(self, instr):
        parts = instr.split()
        if '=' in parts:
            lhs = parts[0]
            rhs = parts[2:]

            if len(rhs) == 1:
                # Simple assignment
                val = rhs[0]
                reg = self.register_map.get(val, val)
                self.register_map[lhs] = reg
                self.code.append(f"MOV {lhs}, {reg}")
            elif len(rhs) == 3:
                # Binary operation
                op1, op, op2 = rhs
                r1 = self.register_map.get(op1, op1)
                r2 = self.register_map.get(op2, op2)
                reg = self.new_register()
                self.code.append(f"MOV {reg}, {r1}")
                asm_op = self.map_operator(op)
                self.code.append(f"{asm_op} {reg}, {r2}")
                self.register_map[lhs] = reg

    def map_operator(self, op):
        return {
            '+': 'ADD',
            '-': 'SUB',
            '*': 'MUL',
            '/': 'DIV'
        }[op]

    def print_code(self):
        print("\nFinal Code (Pseudo Assembly):")
        for line in self.code:
            print(line)


# ===== Main =====
if __name__ == "__main__":
    tac_code = []
    print("Enter TAC instructions (one per line). Type 'done' when finished:")
    while True:
        line = input()
        if line.lower() == "done":
            break
        if line.strip():  # ignore empty lines
            tac_code.append(line.strip())

    fcg = FinalCodeGenerator()
    fcg.generate(tac_code)
    fcg.print_code()