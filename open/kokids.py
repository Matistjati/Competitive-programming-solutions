n,k=map(int,input().split())

s=input()

def remap(c):
    if c=='L': return 0
    if c=='R': return 1
    assert 0

new_ind = 0
new_dir = 0
for i in range(k):
    dead=0
    while new_ind < n:
        if not remap(s[new_ind]) == new_dir:
            new_dir = 1 - remap(s[new_ind])
            new_ind += 1
            dead = True
            break
        else:
            new_ind += 1
            new_dir = 1 - new_dir

    if new_ind==n:
        print(k-i-dead)
        exit(0)
print(0)
