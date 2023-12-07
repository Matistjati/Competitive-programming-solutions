a,b=[int(i.replace("2","$").replace("5","2").replace("$","5")[::-1]) for i in input().split()]
print(1 if a>b else 2)
