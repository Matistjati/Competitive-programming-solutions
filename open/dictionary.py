import bz2
s=""
#/src/
for x in bz2.open("/src/out.txt.bz2").read().split(b'&'):
    x=x.decode()
    s=s[:len(s)-int(x[:2])]+x[2:]
    print(s.replace('%','\'s'))
