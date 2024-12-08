a,b,c,d=map(int, input().split())
pq = (a*a+b*b)*(c*c+d*d)
print(f"{abs(a*c-b*d)}^2 + {abs(a*d+b*c)}^2 = {pq}")
print(f"{abs(a*c+b*d)}^2 + {abs(a*d-b*c)}^2 = {pq}")
