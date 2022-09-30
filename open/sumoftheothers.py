import sys

for line in sys.stdin:
    nums = [int(i) for i in line.split()]
    s = sum(nums)
    for i in range(len(nums)):
        if s-nums[i]==nums[i]:
            print(nums[i])
            break
