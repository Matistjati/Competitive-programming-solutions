import sys
for x in sys.stdin:
    x=x.replace(" ", "")
    print(sum(float(x) for x in x.split(",")))

