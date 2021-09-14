n, q = [int(i) for i in input().split()]

vaccinations = [int(i) for i in input().split()]
persons = sorted([[int(j), i] for i, j in enumerate(input().split())])

times = [-1] * len(persons)

j = 0
v = 0


for i, vaccs in enumerate(vaccinations):
    v += vaccs

    while persons[j][0] < v:
        times[persons[j][1]] = i + 1
        j += 1
        if j >= len(persons):
            break
    if j >= len(persons):
        break

[print(i) for i in times]
