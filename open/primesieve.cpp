#include <iostream>
#include <cmath>
#include <vector>

int main()
{
	int n, q;
	std::cin >> n >> q;
	std::vector<int> ns(q);
	for (size_t i = 0; i < q; i++)
	{
		std::cin >> ns[i];
	}

	if (n == 1)
	{
		std::cout << 1;
		return 0;
	}

	std::vector<bool> primes(n + 1, true);
	primes[0] = false;
	primes[1] = false;
	int primeCount = 0;
	for (size_t i = 4; i < n; i+=2)
	{
		primes[i] = false;
	}

	int m = sqrt(n);
	for (int i = 0; i <= m; i++)
	{
		if (primes[i])
		{
			for (int j = i*2; j <= n; j+=i)
			{
				primes[j] = false;
			}
		}
	}

	for (int i = 0; i <= n; i++)
	{
		primeCount += primes[i];
	}


	std::cout << primeCount << std::endl;

	for (size_t i = 0; i < q; i++)
	{
		std::cout << primes[ns[i]] << std::endl;
	}

	return 0;
}