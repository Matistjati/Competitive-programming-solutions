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
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

typedef unsigned long long ull;
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

// Get the number of divisors given factors. A lot faster than getDivisors(...).size()
ull getDivisorcount(vector<ull> factors, bool isSorted = false)
{
    if (!isSorted) sort(all(factors));
    if (factors.size() == 0) return 1;

    ull ans = 1;
    ull f = factors[0];
    int i = 0;
    while (i < factors.size())
    {
        int start = factors[i];
        int cnt = 0;
        while (i < factors.size() && factors[i] == start)
        {
            cnt++;
            i++;
        }
        ans *= cnt + 1;
    }
    return ans;
}

const int MAX_PR = 1e8 + 10;
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

// Also has modmul

// Slow version for msvc. both compute a*b%k, which is hard if a*b>2^63
#if _LOCAL
const int bits = 1;
// if all numbers are less than 2^k, set bits = 64-k
const ull po = 1ULL << bits;
ull modmul(ull a, ull b, ull c) {
    ull x = a * (b & (po - 1)) % c;
    while ((b >>= bits) > 0) {
        a = (a << bits) % c;
        x += (a * (b & (po - 1))) % c;
        x %= c;
    }
    return x % c;
}

#else
ull modmul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
#endif
// b^e % mod
ull modpow(ull b, ull e, ull mod) {
    ull ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}
bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 },
        s = sin(n - 1), d = n >> s;
    for (ull a : A) {   // ^ count trailing zeroes
        ull p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}

ull pollard(ull n) {
    auto f = [n](ull x) { return modmul(x, x, n) + 1; };
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return gcd(prd, n);
}
vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return { n };
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

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

vector<ull> factor_dyn(int x)
{
    if (x<int(1e8))
    {
        return GetFactors(x);
    }
    return factor(x);
}

// Get a list of the prime factors in the form (base, power). e.g. 2^5+11^2
typedef pair<ull, ull> pull;
typedef vector<pull> vpll;
vpll power_list(vector<ull> factors)
{
    vpll ret;
    sort(all(factors));
    int i = 0;
    while (i < factors.size())
    {
        int start = factors[i];
        pull prime;
        prime.first = start;
        for (; i < factors.size() && factors[i] == start; i++)
        {
            prime.second++;
        }
        ret.push_back(prime);
    }
    return ret;
}

signed main()
{
    fast();

    int a, b;
    cin >> a >> b;
    ifstream in("/src/pre.txt");
    int x;
    int ans = 0;
    while (in >> x)
    {
        if (x >= a && x <= b) ans++;
    }
    cout << ans;

    // code for precomputing answer
    /*
    smallestFactorSieve();

    int t = 1000;
    repp(i, 1, int(1e8+10))
    {
        if (i == t)
        {
            t *= 4;
            cerr << i << "\n";
        }
        if (i % 2 == 0) continue;
        vector<ull> primes = factor_dyn(i);
        vpll powers = power_list(primes);
        repe(p, powers) p.second*=i;
        repe(p, powers) p.second++;

        bool yes = 1;
        int prod = 1;
        vector<ull> allfactors;
        repe(p, powers)
        {
            repe(pr, factor_dyn(p.second))
            {
                allfactors.push_back(pr);
            }
        }
        repe(p, power_list(allfactors))
        {
            prod *= p.second + 1;
            if (prod > i)
            {
                yes = 0;
                break;
            }
        }
        if (yes&&i%prod==0)
        {
            cout << i << "\n";
        }

    }*/

    return 0;
}
