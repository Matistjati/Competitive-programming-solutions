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

typedef pair<double, double> pd;
pd start;
pd goal;
vector<pd> locs;

typedef pair<double, vi> state;

double dist(pd& a, pd& b) { double d1 = a.first - b.first; double d2 = a.second - b.second; return sqrt(d1 * d1 + d2 * d2); }

state best(int vis, int loc, vi& locmap, vector<vector<state>>& dp)
{
    if (__builtin_popcount(vis) == locmap.size()) return { dist(locs[locmap[loc]], start), {loc} };

    state& v = dp[vis][loc];
    if (v.second.size() != 0) return v;

    state ret = { inf, {} };

    rep(i, locmap.size())
    {
        if (vis & (1 << i)) continue;
        state r = best(vis | (1 << i), i, locmap, dp);
        r.first += dist(locs[locmap[i]], locs[locmap[loc]]);
        if (r.first<ret.first)
        {
            ret = r;
        }
    }

    ret.second.push_back(loc);

    return (v = ret);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    locs.resize(n);
    map<string, int> nameid;
    vector<string> names;
    rep(i, n) {
        string name;
        cin >> name;
        nameid[name] = names.size();
        names.push_back(name);
        double x,y;
        cin >> x >> y;
        locs[i] = { x,y };
    }
    
    start = locs[nameid["home"]];
    goal = locs[nameid["work"]];

    string line,tmp;
    while (getline(cin,line)) {
        if (line == "") continue;
        stringstream ss(line);
        vi locs;
        while (ss >> tmp) locs.push_back(nameid[tmp]);
        locs.push_back(nameid["work"]);

        vector<vector<state>> dp(1 << locs.size(), vector<state>(locs.size(), {double(inf+1), {}}));

        state ans = best(1 << (locs.size() - 1), locs.size()-1, locs, dp);
        ans.second.pop_back();
        reverse(all(ans.second));
        rep(i, ans.second.size())
        {
            cout << names[locs[ans.second[i]]] << ' ';
        }
        cout << '\n';
    }

    return 0;
}
