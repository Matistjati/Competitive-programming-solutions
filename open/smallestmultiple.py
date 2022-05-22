import math
import sys

for line in sys.stdin:
    nums = [int(i) for i in line.split()]
    ans = nums[0]
    for i in range(1, len(nums)):
        ans = ans * nums[i] // int(math.gcd(ans, nums[i]))

    print(ans)


