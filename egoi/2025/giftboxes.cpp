#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i,n) for (int i=0;i<(n);i++)
#define repp(i,a,b) for (int i=(a);i<(b);i++)
#define repe(i,arr) for (auto &i : arr)
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()

int main()
{
    ll n, t;
    cin >> t >> n;

    vi nums(n);
    repe(v, nums) cin >> v;

    vi occs(t);
    repe(v, nums) occs[v]++;
    ll num_bad = 0;
    repe(v, occs) if (v > 1) num_bad++;
    
    ll ans = inf;
    p2 inter = p2(-1, -1);
    ll r = 0;
    rep(i, n)
    {
        while ((r<i||num_bad) && r<n)
        {
            if (occs[nums[r]] == 2) num_bad--;
            occs[nums[r++]]--;
        }
        if (num_bad == 0)
        {
            if (r - i < ans) ans = r - i, inter = { i,r };
        }
        if (occs[nums[i]] == 1) num_bad++;
        occs[nums[i]]++;
    }

    cout << inter.first << " " << inter.second-1 << endl;

    return 0;
}
