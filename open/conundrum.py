word=input()
n = 0
for i in range(len(word)//3):
    j = i * 3
    if word[j+0] != "P":
        n+=1
    if word[j+1] != "E":
        n += 1
    if word[j+2] != "R":
        n+=1
print(n)
