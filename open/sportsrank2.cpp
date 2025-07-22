#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

#define rep(i, b) for(ll i = 0; i < (b); i++)
#define repp(i, a, b) for(ll i = a; i < (b); i++)
#define repe(i,arr) for (auto& i : arr)
#define all(x) begin(x), end(x)
#define sz(x) ((ll)(x).size())
typedef pair<ll, ll> p2;
typedef vector<ll> vi;
typedef vector<vi> vvi;

void solve()
{
    ll n;
    cin >> n;
    vi nums(n);
    repe(v, nums) cin >> v;

    vector<p2> ranks(n);
    vector<p2> nump(n);
    rep(i, n) nump[i] = p2(nums[i], i);
    sort(all(nump));
    reverse(all(nump));
    ranks[0] = p2(0, 0);
    repp(i, 1, n)
    {
        if (nump[i].first == nump[i - 1].first) ranks[i].first = ranks[i - 1].first;
        else ranks[i].first = ranks[i - 1].first + 1;

        if (nump[i].first == nump[i - 1].first) ranks[i].second = ranks[i - 1].second;
        else ranks[i].second = i;
    }
    ll ans = 0;
    rep(i, n) ans += abs(ranks[i].second - ranks[i].first)>0;
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}

