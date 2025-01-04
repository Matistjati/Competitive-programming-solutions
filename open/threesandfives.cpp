n = int(input())
n-=1
def sumdiv(d):
    h = n//d
    return h*(h+1)//2*d

print(sumdiv(3)+sumdiv(5)-sumdiv(15))

