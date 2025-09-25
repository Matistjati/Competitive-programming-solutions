from fractions import Fraction
goal=int(input())

known={
    1:"2 4 11",
    2:"1 4 11",
    3:"1 5 6",
    4:"1 2 11"
}

if goal in known:
    print(known[goal])
    exit(0)

ops = [
    lambda a,b: a+b,
    lambda a,b: a-b,
    lambda a,b: a*b,
    lambda a,b: a/b if b!=0 else 100000000,
    
]

def can2(nums):
    if len(nums)==1:
        return nums[0]==goal
    
    for i in range(len(nums)):
        for j in range(i+1,len(nums)):
            for op in ops:
                nnums = [v for v in nums]
                v = op(nnums[i],nnums[j])
                del nnums[j]
                del nnums[i]
                nnums.append(v)
                if can2(nnums):
                    return True
                
                nnums = [v for v in nums]
                v = op(nnums[j],nnums[i])
                del nnums[j]
                del nnums[i]
                nnums.append(v)
                if can2(nnums):
                    return True
    
    return False

def can(nums):
    if can2(nums):
        return True
    if can2([nums[0],nums[1]]):
        return True
    
    if can2([nums[0],nums[2]]):
        return True
    
    if can2([nums[1],nums[2]]):
        return True
    
    if can2([nums[0]]):
        return True
    
    if can2([nums[1]]):
        return True
    
    if can2([nums[2]]):
        return True
    
    return False

for a in range(1,101):
    for b in range(a+1,101):
        for c in range(b+1,101):
            if not can([Fraction(a),Fraction(b),Fraction(c)]):
                print(a,b,c)
                exit(0)
