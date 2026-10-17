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
    vector<tuple<int,int,int>> items(n);
    rep(i, n)
    {
        int p, v;
        cin >> p >> v;
        items[i] = { v,p,i };
    }

    int q;
    cin >> q;
    vector<tuple<int, int, int>> queries(q);
    rep(i, q)
    {
        int x, k;
        cin >> x >> k;
        queries[i] = { x,k,i };
    }
    sort(all(queries));
    sort(all(items));

    vvi answers(q);

    vector<p2> available;
    int qind = 0;

    auto answer = [&](int u) {
        auto [x, k, ind] = queries[u];
        rep(i, min<int>(k, sz(available))) answers[ind].push_back(available[i].second);
        sort(all(answers[ind]));
    };

    rep(i, n) {
        while (qind<q && get<0>(items[i]) > get<0>(queries[qind]))
        {
            answer(qind);
            qind++;
        }
        p2 v = p2(-get<1>(items[i]), get<2>(items[i]));
        available.insert(lower_bound(all(available), v), v);
        if (sz(available) > 10) available.pop_back();
    }
    repp(i, qind, q) answer(i);

    rep(i, q) {
        if (answers[i].size()) {
            repe(u, answers[i]) cout << u+1 << " ";
        }
        else {
            cout << "-1";
        }
        cout << "\n";
    }


	return 0;
}
