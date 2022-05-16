from re import split

state = input()

n=int(input())
ans = 1
for i in (len(d) for d in split('0+', bin(n)[2:]) if d != ''):
    ans *= round(pow(2,i+2)/3.)

print(ans)
