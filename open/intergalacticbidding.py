n, t = [int(i) for i in input().split()]
people = [input().split() for i in range(n)]
people = [(i[0],int(i[1])) for i in people]

people = sorted(people, key=lambda x: x[1], reverse=True)

s = t
ans = []
for person in people:
    if s-person[1]>=0:
        s-=person[1]
        ans.append(person[0])

if s==0:
    print(len(ans))
    [print(i) for i in ans]
else:
    print(0)
