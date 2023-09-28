n=int(input())
for i in range(n):
    a = set()
    j = int(input())
    for _ in range(j):
        city = input()
        if city not in a:
            a.add(city)
    print(len(a))
        
