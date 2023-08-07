
def SieveOfEratosthenes(num):
    prime = [True for i in range(num+1)]
# boolean array
    p = 2
    while (p * p <= num):
 
        # If prime[p] is not
        # changed, then it is a prime
        if (prime[p] == True):
 
            # Updating all multiples of p
            for i in range(p * p, num+1, p):
                prime[i] = False
        p += 1
 
    primes = []
    # Print all prime numbers
    for p in range(2, num+1):
        if prime[p]:
            primes.append(p)
    return primes

primes = SieveOfEratosthenes(int(1e6+10))

while 1:
    k,l=[int(i) for i in input().split()]
    if k==0: break

    found = -1
    for prime in primes:
        if prime>=l:
            break
        if k%prime==0:
            found=prime
            break
    if found == -1:
        print("GOOD")
    else:
        print("BAD",found)