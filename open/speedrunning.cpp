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

    int n;
    cin >> n;
    string s;
    cin >> s;

    priority_queue<tuple<int,int,int>> pq;
    pq.emplace(0, 0, 0);
    pq.emplace(0, 1, 0);
    pq.emplace(0, 2, 0);

    vvi vis(3, vi(n));



    while (sz(pq)) {
        auto [d,m_state,i] = pq.top();
        pq.pop();
        d=-d;

        if (i==n-1) {
            cout << d << '\n';
            return 0;
        }
        if (vis[m_state][i]) continue;
        vis[m_state][i]=1;

        if (s[i]=='S') {
            if (m_state==0) continue;
            pq.emplace(-(d+(m_state==1?1:2)), m_state-1,i+1);
        }
        else if (s[i]=='.') {
            pq.emplace(-(d+(m_state==0?1:2)), m_state,i+1);
        }
        else {
            pq.emplace(-(d+(m_state==0?1:2)), m_state,i+1);
            pq.emplace(-(d+2), min<int>(2,m_state+1),i+1);
        }
    }
    cout << "-1\n";

    return 0;
}
