
solutions = {}

operators = ["+", "-", "/", "*"]

opmap = {"/": "//", "+":"+", "-":"-","*":"*"}

def evaluate(a,b,c):
    return eval(f"4{opmap[a]}4{opmap[b]}4{opmap[c]}4")

for first in operators:
    for second in operators:
        for third in operators:
            solutions[evaluate(first,second,third)] = [first,second,third]


m = int(input())

nums = [int(input()) for i in range(m)]


for n in nums:
    if n in solutions:
        op = solutions[n]
        print(f"4 {op[0]} 4 {op[1]} 4 {op[2]} 4 = {n}")
    else:
        print("no solution")

