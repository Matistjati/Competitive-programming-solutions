#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

#define rep(i, b) for(int i = 0; i < (b); i++)
#define repp(i, a, b) for(int i = a; i < (b); i++)
#define repe(i,arr) for (auto& i : arr)
#define all(x) begin(x), end(x)
#define sz(x) ((int)(x).size())
typedef pair<int, int> p2;
typedef vector<int> vi;
typedef vector<vi> vvi;


signed main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, m, k;
    cin >> n >> m >> k;
    vi nums(n);
    repe(v, nums) cin >> v;
    int ans = 0;
    sort(all(nums));
    reverse(all(nums));
    rep(i, min(n,m+k)) ans += nums[i];

    cout << fixed << setprecision(15) << 100*(ans / accumulate(all(nums), 0.));

    return 0;
}

