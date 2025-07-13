#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)


template<typename T>
struct Kahan {
    T sum = 0;
    T c = 0;
    void add(T x) {
        T y = x - c;
        T t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    T value() const {
        return sum;
    }
};

Kahan<double> best;
int bestind = 0;

// i have added [0,l) (r, N)
void rec(int l, int r, Kahan<double> logsum, vector<map<int,ll>>& nums, vi& occs)
{
    if (l == r)
    {
        if (logsum.value()>best.value())
        {
            best = logsum;
            bestind = l;
        }
        return;
    }
    int mid = (l + r) / 2;
    {
        Kahan logc = logsum;

        vector<p2> save;

        repp(i, mid + 1, r + 1)
        {
            repe(f, nums[i]) save.emplace_back(f.first, occs[f.first]);
        }

        repp(i, mid + 1, r + 1)
        {
            repe(f, nums[i])
            {
                logc.add(-occs[f.first] * logl(f.first));
                occs[f.first] = max(occs[f.first], f.second);
                logc.add(occs[f.first] * logl(f.first));
            }
        }

        rec(l, mid, logc, nums, occs);
        repe(s, save)
        {
            occs[s.first] = s.second;
        }
    }
    
    {
        Kahan logc = logsum;

        vector<p2> save;

        repp(i, l, mid + 1)
        {
            repe(f, nums[i]) save.emplace_back(f.first, occs[f.first]);
        }

        repp(i, l, mid + 1)
        {
            repe(f, nums[i])
            {
                logc.add(-occs[f.first] * logl(f.first));
                occs[f.first] = max(occs[f.first], f.second);
                logc.add(occs[f.first] * logl(f.first));
            }
        }

        rec(mid+1, r, logc, nums, occs);
        repe(s, save)
        {
            occs[s.first] = s.second;
        }
    }
    
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    
    int n;
    cin >> n;
    vi nums(n);
    repe(v, nums) cin >> v;
    sort(all(nums));
    vector<map<int,ll>> factors(n);
    rep(i, n)
    {
        int v = nums[i];
        repp(j, 2, 1010)
        {
            while (v%j==0)
            {
                factors[i][j]++;
                v /= j;
            }
        }
        if (v > 1) factors[i][v]++;
    }

    vi occs(int(1e6)+10);
    rec(0, n-1, Kahan<double>(), factors, occs);
    cout << nums[bestind];

    return 0;
}
