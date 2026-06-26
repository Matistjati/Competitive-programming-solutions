line=' '.join(input().strip().split())
if line=="What is problem A about?":
    print(r'''Problem A is about Ascii Art
   _     __   __  _   _
  / \   / /  / / | | | |
 / _ \  \ \ | |  | | | |
/_/ \_\ /_/  \_\ |_| |_|
''',end='')
elif line=="What is problem B about?":
    print(r'''Problem B is about Fortnite
###############
###############
####       /###
####   ########
####       ####
####   ########
####   ########
####   ########
####_~<########
###############
''',end='')
elif line=='What is problem C about?':
    print(r'''Problem C is about The Legend of Zelda
     /\
    /  \
   /____\
  /\    /\
 /  \  /  \
/____\/____\
''',end='')
else:
    print("I am not sure how to answer that.")