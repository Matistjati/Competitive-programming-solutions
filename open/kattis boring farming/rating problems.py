n, k = [int(i) for i in input().split()]

ratings = [int(input()) for i in range(k)]

print((sum(ratings)-3*(n-k))/n, (sum(ratings)+3*(n-k))/n)