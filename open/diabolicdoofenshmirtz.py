prev=1
def ask(x):
    print("?",x)
    resp=int(input())
    return resp
if ask(1)==0:
    print("! 1")
    exit(0)
x=2
while 1:
    res = ask(x)
    if res < x:
        print("!",prev*2-res)
        exit(0)
    prev=x
    x*=2
