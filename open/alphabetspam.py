lowercase = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
uppercase = [i.upper() for i in lowercase]

s = input()

lower = 0
upper = 0
whitepsace = 0
other = 0
for letter in s:
    if letter in lowercase:
        lower += 1
    elif letter in uppercase:
        upper += 1
    elif letter == "_":
        whitepsace += 1
    else:
        other += 1

print(whitepsace/len(s), lower/len(s), upper/len(s), other/len(s))