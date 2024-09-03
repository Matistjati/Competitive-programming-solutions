#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const int MAX_PR = 1e6+10;
vi smallestfactor(MAX_PR);

// Find smallest factor of all numbers in range[0, hi)
void smallestFactorSieve(int hi = MAX_PR)
{
    rep(i, hi) smallestfactor[i] = i;
    for (int i = 0; i < hi; i += 2) smallestfactor[i] = 2;

    repp(i, 3, min(hi + 0., ceil(sqrt(hi)) + 10))
    {
        if (smallestfactor[i] == i)
        {
            for (size_t j = i * i; j < hi; j += i)
            {
                if (smallestfactor[j] == j) smallestfactor[j] = i;
            }
        }
    }
}
typedef unsigned long long ull;

// Factor n in log(n) time
vector<ull> GetFactors(int n)
{
    vector<ull> factors;
    int k = n;
    while (k != 1 && k != 0)
    {
        factors.emplace_back(smallestfactor[k]);
        k /= smallestfactor[k];
    }
    return factors;
}
// Helper function
void setDivisors(ull n, ull i, vector<ull>& divisors, vector<pair<ull, ull>>& factors) {
    ull j, x, k;
    for (j = i; j < factors.size(); j++) {
        x = factors[j].first * n;
        for (k = 0; k < factors[j].second; k++) {
            divisors.push_back(x);
            setDivisors(x, j + 1, divisors, factors);
            x *= factors[j].first;
        }
    }
}
// Get all factor from a list of primes
vector<ull> getDivisors(vector<ull> primes)
{
    unordered_map<ull, ull> primeCount;
    repe(prime, primes) primeCount[prime]++;
    vector<pair<ull, ull>> factorCount;
    repe(p, primeCount) factorCount.emplace_back(p);
    vector<ull> ret;
    setDivisors(1, 0, ret, factorCount);
    ret.push_back(1);
    return ret;
}

signed main()
{
    fast();
    smallestFactorSieve();

    int n;
    cin >> n;
    vi dp(n + 1, 1);
    vi par(n + 1, -1);


    for (int i = n; i > 0; i--)
    {
        repe(f, getDivisors(GetFactors(i)))
        {
            if (f == i) continue;
            if (dp[f] < dp[i]+1)
            {
                dp[f] = dp[i] + 1;
                par[f] = i;
            }
        }
    }
    
    int u = 1;
    vi ans;
    while (u!=-1)
    {
        ans.push_back(u);
        u = par[u];
    }
    cout << sz(ans) << "\n";
    rep(i, sz(ans)) cout << ans[i] << " ";

    return 0;
}
