import sys
import statistics

def isfloat(token):
    return token.replace('.','1').isnumeric()

for line in sys.stdin:
    tokens = line.split()
    name = ' '.join(token for token in tokens if not isfloat(token))
    print(f"{statistics.fmean(map(float, (token for token in tokens if isfloat(token))))} {name}")
