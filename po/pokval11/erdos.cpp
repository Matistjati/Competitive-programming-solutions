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

    vector<vector<string>> publications;

    map<string, set<string>> neighbours;
    rep(i, m)
    {
        ll k;
        cin >> k;
        vector<string> authors(k);
        rep(i, k) cin >> authors[i];
        repe(a, authors)
        {
            repe(b, authors)
            {
                if (!neighbours.count(a)) neighbours[a] = {};
                if (!neighbours.count(b)) neighbours[b] = {};
                neighbours[a].insert(b);
                neighbours[b].insert(a);
            }
        }
    }

    map<string, ll> scientists;

    queue<pair<string, ll>> toDo;
    toDo.push({ "ERDOS",0 });

    while (toDo.size())
    {
        pair<string, ll> curr = toDo.front();
        toDo.pop();

        if (scientists.count(curr.first)) continue;
        else
        {
            scientists[curr.first] = curr.second;
        }

        repe(con, neighbours[curr.first])
        {
            toDo.push({ con,curr.second + 1 });
        }
    }

    repe(author, scientists)
    {
        cout << author.first << " " << author.second << "\n";
    }

    return 0;
}
