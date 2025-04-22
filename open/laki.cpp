import sys
nums=input().split(" + ")
a,b=nums[0],nums[1]

answers = {("tragedy", "time"):"comedy",
           ("repetition", "repetition"): "learning",
           ("fire","water"):"steam",
           ("red","blue"):"purple",
           ("icelander","deadline"):"procrastination",
           ("throat","potato"):"danish",    
           ("kattis","program"):"verdict",
           ("problem","solution"):"AC",
           ("contest","geometry"):"WA",
           ("nonsense","annoyance"):"this problem"}

if (a,b) in answers:
    print(answers[(a,b)])

def extended_gcd(a, b):
    if b == 0:
        return (a, 1, 0)
    g, x1, y1 = extended_gcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return (g, x, y)

def chinese_remainder_theorem(remainders, moduli):
    assert len(remainders) == len(moduli), "Mismatched input lengths"
    
    x = 0
    M = 1
    for m in moduli:
        M *= m

    for ai, mi in zip(remainders, moduli):
        Mi = M // mi
        _, inv, _ = extended_gcd(Mi, mi)
        x += ai * inv * Mi

    return (x%M, M)

if "mod" in a:
    a = list(int(i.split(" mod ")[0]) for i in nums)
    b = list(int(i.split(" mod ")[1]) for i in nums)

    k,s=chinese_remainder_theorem(a,b)
    print(f"{k} mod {s}")
    sys.exit(0)

maya = {
    "𝋠": 0,
    "𝋡": 1,
    "𝋢": 2,
    "𝋣": 3,
    "𝋤": 4,
    "𝋥": 5,
    "𝋦": 6,
    "𝋧": 7,
    "𝋨": 8,
    "𝋩": 9,
    "𝋪": 10,
    "𝋫": 11,
    "𝋬": 12,
    "𝋭": 13,
    "𝋮": 14,
    "𝋯": 15,
    "𝋰": 16,
    "𝋱": 17,
    "𝋲": 18,
    "𝋳": 19 
}

revmaya = {}
for A,B in maya.items():
    revmaya[B]=A

if a[0] in maya:
    def parse_maya(x):
        m = 1
        res = 0
        for c in reversed(x):
            res += maya[c] * m
            m *= 20
        return res
    a = parse_maya(a)
    b = parse_maya(b)
    res = a+b
    def to_maya(x):
        res = ""
        while x:
            res += revmaya[x%20]
            x//=20
        res = res[::-1]
        if len(res)==0:
            res += revmaya[0]

        return str(res)

    print(to_maya(res))
    sys.exit(0)

element_symbols = [
    "H", "He", "Li", "Be", "B", "C", "N", "O", "F", "Ne",
    "Na", "Mg", "Al", "Si", "P", "S", "Cl", "Ar",
    "K", "Ca", "Sc", "Ti", "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn",
    "Ga", "Ge", "As", "Se", "Br", "Kr",
    "Rb", "Sr", "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd",
    "In", "Sn", "Sb", "Te", "I", "Xe",
    "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb",
    "Dy", "Ho", "Er", "Tm", "Yb", "Lu",
    "Hf", "Ta", "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb",
    "Bi", "Po", "At", "Rn",
    "Fr", "Ra", "Ac", "Th", "Pa", "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf",
    "Es", "Fm", "Md", "No", "Lr",
    "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Nh", "Fl", "Mc",
    "Lv", "Ts", "Og"
]

if all(i in element_symbols for i in nums):
    ind = sum(element_symbols.index(i)+1 for i in nums)
    print(element_symbols[ind-1])

def is_complex_number(s):
    try:
        s = s.replace("i","j")
        complex(s)
        return True
    except:
        return False

any_complex = any("i" in i for i in nums)
if all(is_complex_number(i) for i in nums):
    ans = (sum(complex(i.replace("i","j")) for i in nums))
    ans = str(ans).replace("j","i").replace("(","").replace(")","").replace("+", " + ")
    if not any_complex:
        ans = ans.split(" +")[0]
    print(ans)
    sys.exit(0)


if "\"" in a:
    print(eval(a)+eval(b))
    sys.exit(0)
elif a.startswith("0x"):
    a = int(a, 16)
    b = int(b, 16)
    print(hex(a+b))
    sys.exit(0)

if "log" in a:
    nums = [i.replace("log(","").replace(")","") for i in nums]
    p = 1
    for i in nums:
        p *=int(i)
    print(f"log({p})")

if "{" in a:
    vecs = list(i.replace("{","").replace("}","").split(", ") for i in nums)
    ans = []
    vecs = [i for i in vecs if i[0]!='']
    for v in vecs:
        for j, vv in enumerate(v):
           ans.append(int(vv))
    ans = list(set(ans))
    ans.sort()
    print("{" + ", ".join(str(i) for i in ans) + "}")

