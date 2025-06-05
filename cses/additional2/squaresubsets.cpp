#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

const int MAX_PR = 5'000'000;
bitset<MAX_PR> isprime;
vi eratosthenesSieve(int lim) {
	isprime.set(); isprime[0] = isprime[1] = 0;
	for (int i = 4; i < lim; i += 2) isprime[i] = 0;
	for (int i = 3; i * i < lim; i += 2) if (isprime[i])
		for (int j = i * i; j < lim; j += i * 2) isprime[j] = 0;
	vi pr;
	repp(i, 2, lim) if (isprime[i]) pr.push_back(i);
	return pr;
}

const int m = 669;
typedef bitset<m> bs;

int solveLinear(vector<bs>& A) {
	int n = sz(A), rank = 0, br;
	vi col(m); iota(all(col), 0);
	repp(i, 0, n) {
		for (br = i; br < n; ++br) if (A[br].any()) break;
		if (br == n) {
			break;
		}
		int bc = (int)A[br]._Find_next(i - 1);
		swap(A[i], A[br]);
		swap(col[i], col[bc]);
		repp(j, 0, n) if (A[j][i] != A[j][bc]) {
			A[j].flip(i); A[j].flip(bc);
		}
		repp(j, i + 1, n) if (A[j][i]) {
			A[j] ^= A[i];
		}
		rank++;
	}

	return rank;
}

signed main()
{
    fast();

	vi primes = eratosthenesSieve(5001);

    int n;
    cin >> n;
    vi nums(n);
    repe(v, nums) cin >> v;

	vector<bs> A;
	repe(v, nums)
	{
		bs row;

		int hi = sqrt(v) + 10;
		rep(i, sz(primes))
		{
			while (v % primes[i] == 0)
			{
				row[i] = !row[i];
				v /= primes[i];
			}
		}
		A.push_back(row);
	}

	int free = n;
	free -= solveLinear(A);
	int ans = 1;
	rep(i, free) ans = (ans * 2) % int(1e9 + 7);

	cout << ans;

    return 0;
}
