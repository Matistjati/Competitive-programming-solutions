#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int MAX_PR = 10'000'000;
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

signed main()
{
    fast();

    int n;
    cin >> n;
    vi primes = eratosthenesSieve(n);
    p2 ans = p2(0, 0);
    int lo = 0;
    int s = 0;
    rep(i, sz(primes))
    {
        s += primes[i];
        while (s>=n)
        {
            s -= primes[lo++];
        }

        int j = lo;
        int ss = s;
        while (j<i && !isprime[ss])
        {
            ss -= primes[j++];
        }
        if (isprime[ss]) if (i - j > ans.first) ans = p2(i - j, ss);
    }
    cout << ans.second;

    return 0;
}
