n=float(input())
while True:
    if (n/(sum([int(i) for i in str(int(n))]))).is_integer():
        print(int(n))
        break
    n+=1
