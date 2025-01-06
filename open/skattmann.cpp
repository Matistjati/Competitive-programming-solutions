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

const int MAX_PR = 1e4 + 10;
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
        if (smallestfactor[k] != n) factors.emplace_back(smallestfactor[k]);
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
    int p = 1;
    repe(u, primes) p *= u;
    //ret.erase(find(all(ret),p));
    return ret;
}

mt19937 rng(10);

int getRandomItem(vector<pair<double, int>>& items)
{
    double totalWeight = 0;
    for (const auto& item : items) totalWeight += item.first;

    uniform_int_distribution<> dis(1, totalWeight);

    int randomWeight = dis(rng);
    int cumulativeWeight = 0;
    repe(item, items)
    {
        cumulativeWeight += item.first;
        if (randomWeight <= cumulativeWeight) return item.second;
    }
    assert(0);
}

vector<double> powprecomp;
vvi divisors;
int bestscore = 0;
vi gans;

void playgame(int n)
{
    uniform_int_distribution<int> dist(1, n);

    vi taken(n + 1);
    int numleft = n;
    int score = 0;
    vi ans;

    vi cant(n + 1);
    auto cantake = [&](int x)
        {
            if (taken[x]) return false;
            if (cant[x]) return false;
            repe(f, divisors[x]) if (!taken[f]) return true;
            cant[x] = true;
            return false;
        };

    auto take = [&](int x, bool me)
        {
            if (!taken[x])
            {
                if (me) score += x;
                numleft--;
            }

            taken[x] = 1;
        };


    while (numleft)
    {
        vector<pair<double,int>> best;

        repp(i, 1, n + 1)
        {
            if (!cantake(i)) continue;
            int score = i;
            int numdivs = 0;
            int divsum = 0;
            repe(d, divisors[i]) if (!taken[d]) divsum += d, numdivs++;
            double sc = -(score / numdivs / powprecomp[divsum]);
            best.insert(lower_bound(all(best), p2(sc, i)), p2(sc, i));
            if (sz(best) > 3) best.pop_back();
        }

        if (best.empty()) break;

        repe(u, best) u.first *= -1;
        double m = 0;
        repe(u, best) m = min(m, u.first);
        repe(u, best) u.first -= m - 1;
        int u = getRandomItem(best);

        ans.push_back(u);
        take(u, 1);
        repe(f, divisors[u]) take(f, 0);
    }

    if (score > bestscore)
    {
        bestscore = score;
        gans = ans;
    }
}


signed main()
{
    fast();

    int n;
    cin >> n;
    auto start = chrono::high_resolution_clock::now();

    powprecomp.resize(1e5);
    rep(i, sz(powprecomp)) powprecomp[i] = pow(i, 0.2);

    //assert(n <= 1000);
    smallestFactorSieve();
    divisors.resize(n + 1);
    repp(i, 1, n + 1) repe(d, getDivisors(GetFactors(i))) if (d != i) divisors[i].push_back(d);
    repp(i, 1, n + 1) sort(all(divisors[i]));

    int numits = 0;
    int timelim = (n <= 1000 ? 4900 : 3000);
    while ((chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start)).count() < timelim)
    {
        numits++;
        playgame(n);
    }

    int they = (n * (n + 1) / 2 - bestscore);
    cout << sz(gans) << "\n";
#if !_LOCAL
    repe(u, gans) cout << u << " ";
#endif
    cout << '\n';
    cerr << "me: " << bestscore << ", they: " << they << ", me/they: " << double(bestscore) / they << "\n";
    cerr << "time: " << (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start)).count() << " ms\n";
    cerr << "numits: " << numits << "\n";
    cerr << "d";

    return 0;
}
