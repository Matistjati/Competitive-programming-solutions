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

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n,m;
    cin >> n >> m;
    int initial_m = m;
    priority_queue<pair<int,int>> pq;
    rep(i,n) {
        int a,b;
        cin >> a >> b;
        if (a>=b) continue;
        pq.emplace(-a,b);
    }

    while (sz(pq)) {
        auto [cost,value] = pq.top();
        pq.pop();
        cost=-cost;
        if (m<cost) break;
        m+=-cost+value;
    }

    cout << m-initial_m << '\n';

    return 0;
}
