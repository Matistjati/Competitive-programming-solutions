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

set<p2> vis;
vector<p2> dirs = {{0,1},{1,0},{0,-1},{-1,0}};
vector<string> dir_name = {"right", "down","left","up"};
void dfs(p2 pos) {
    vis.insert(pos);
    rep(i,4) {
        p2 dir = dirs[i];
        string name = dir_name[i];

        p2 np = p2(pos.first+dir.first,pos.second+dir.second);
        if (vis.contains(np)) continue;
        cout << name << endl;
        string resp;
        cin >> resp;
        if (resp=="solved") {
            exit(0);
        }
        if (resp=="wall") continue;
        dfs(np);
        cout << dir_name[(i+2)%4] << endl;
        cin >> resp;
        assert(resp=="ok");
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    dfs({0,0});
    cout << "no way out\n";
    
    return 0;
}
