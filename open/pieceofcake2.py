a,b,c=[int(i) for i in input().split(" ")]
print(max(b*c,(a-c)*b,(a-b)*c,(a-b)*(a-c))*4)
