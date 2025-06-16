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

const int MAX_PR = 1e5 + 20;
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
// Factor n in log(n) time
vi GetFactors(int n)
{
    vi factors;
    int k = n;
    while (k != 1 && k != 0)
    {
        factors.emplace_back(smallestfactor[k]);
        k /= smallestfactor[k];
    }
    return factors;
}

vi getDivisors(vi primes) {
    unordered_map<int, int> cnt;
    repe(p, primes) cnt[p]++;
    vi d = { 1 };
    for (auto [p, e] : cnt) {
        int n0 = sz(d);
        rep(i, n0) {
            ll cur = d[i];
            rep(j, e) {
                cur *= p;
                d.push_back(cur);
            }
        }
    }
    sort(all(d));
    return d;
}

signed main()
{
    fast();

    smallestFactorSieve();

    int n;
    cin >> n;
    set<int> numss;
    rep(i, n + 1)
    {
        int x;
        cin >> x;
        numss.insert(x);
    }

    int ans = 0;

    vi nums(all(numss));

    vi seen(1e5 + 10);

    vi phi(1e5 + 10);
    repp(i, 1, sz(phi))
    {
        map<int, int> occs;
        repe(u, GetFactors(i)) occs[u]++;
        int p = 1;
        repe(o, occs) p *= pow(o.first, o.second - 1) * (o.first - 1);
        phi[i] = p;
    }

    // count gcd(a,x)=b
    auto count_occs = [&](int a, int b)
        {
            a /= b;
            int ret = 0;
            repp(i, 1, a) ret += gcd(a, i) == 1;
            return ret;
        };

    // count number of x where gcd(a,x)=b
    auto count_fast = [&](int a, int b)
        {
            a /= b;
            if (a == 1) return 0LL;
            return phi[a];
        };


    rep(i, sz(nums))
    {
        int x = nums[i];
        repe(x2, getDivisors(GetFactors(x)))
        {
            if (!seen[x2]) ans += count_fast(x, x / x2);
        }

        repe(div, getDivisors(GetFactors(x)))
        {
            seen[div] = 1;
        }
    }

    cout << ans;

    return 0;
}
