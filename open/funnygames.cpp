// this testcase is about as hard as the hardest judge testcase
// 1
// 500 6 0.9 0.89 0.899 0.899991 0.899998 0.899999
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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

// use bloom filters for memo
typedef unsigned long long ull;
constexpr int maxsz = int(5e8);
bitset<maxsz> bs1;
bitset<maxsz> bs2;
bitset<maxsz> bs3;
bitset<maxsz> bs4;
constexpr ull magic1 = 2374279394923;
constexpr ull magic2 = 93475789346579823;
constexpr ull magic3 = 47857682346918;
constexpr ull magic4 = 348757413248923794;
double smallest;
int nodes = 0;
bool wins(double p, ull h, vector<double>& nums, vi& weights)
{
    if (p * smallest <= 1)
    {
        return true;
    }


    ull hash1 = h * magic1 % maxsz;
    ull hash2 = h * magic2 % maxsz;
    ull hash3 = h * magic3 % maxsz;
    ull hash4 = h * magic4 % maxsz;

    if (bs1[hash1] && bs2[hash2]) {
        return bs3[hash3] && bs4[hash4];
    }

    bool can_win = false;
    for (size_t i = 0; i < nums.size(); i++) {
        if (!wins(p * nums[i], h + weights[i], nums, weights)) {
            can_win = true;
            break;
        }
    }

    bs1[hash1] = 1;
    bs2[hash2] = 1;
    if (can_win) {
        bs3[hash3] = 1;
        bs4[hash4] = 1;
    }
    nodes++;
    return can_win;
}

signed main()
{
    fast();

    int t;
    cin >> t;

    while (t--)
    {
        double start;
        cin >> start;
        int n;
        cin >> n;
        vector<double> nums(n);
        rep(i, n) cin >> nums[i];
        // sorting is VERY important for performance
        sort(all(nums));
        bs1.reset();
        bs2.reset();
        bs3.reset();
        bs4.reset();
        smallest = *min_element(all(nums));
        vi weights = { 1 };
        while (sz(weights) < n) weights.push_back(weights.back() * 60);

        cout << (wins(start, 0, nums, weights) ? "Nils" : "Mikael") << "\n";
    }

    return 0;
}
