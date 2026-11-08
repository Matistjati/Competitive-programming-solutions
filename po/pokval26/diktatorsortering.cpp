#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vi arr(n);
    repe(v, arr) cin >> v;

    deque<vi> stacks;
    deque<int> top;

    top.push_back(arr[0]);
    stacks.push_back({ arr[0] });

    repp(i, 1, n)
    {
        if (arr[i] <= top[0])
        {
            top.push_front(arr[i]);
            stacks.push_front({ arr[i] });
        }
        else
        {
            auto it = lower_bound(all(top), arr[i]);
            assert(it != begin(top));
            top[prev(it) - begin(top)] = arr[i];
            stacks[prev(it) - begin(top)].push_back(arr[i]);
        }
    }

    reverse(all(stacks));
    repe(s, stacks) {
        bool f = 1;
        repe(v, s) cout << (f ? "" : " ") << v, f = 0;
        cout << '\n';
    }
    
    return 0;
}
