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

const int EMPTY = 0;
const int JOHAN = 1;
const int ABDULLAH = 2;

void mirror(vvi& grid) {
    rep(i,3) rep(j,3) grid[i][j]*=-1;
}

int has_win(vvi grid) {
    rep(i,3) {
        int s = 0;
        rep(j,3) s += grid[i][j];
        if (s==3) return true;
    }
    rep(i,3) {
        int s = 0;
        rep(j,3) s += grid[j][i];
        if (s==3) return true;
    }
    int s = 0;
    rep(i,3) s+=grid[i][i];
    if (s==3) return true;
    s=0;
    rep(i,3) s+=grid[i][2-i];
    if (s==3) return true;
    return false;
}

int winning[2]={};
void solve(vvi grid, int who) {
    int ret = 0;
    rep(i,3) rep(j,3) {
        if (grid[i][j]==0) {
            grid[i][j]=1;
            if (has_win(grid)) {
                grid[i][j]=0;
                winning[who]=1;
                continue;
            }
            mirror(grid);
            solve(grid, who^1);
            mirror(grid);
            grid[i][j]=0;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vvi grid(3,vi(3));
    int nonempty=0;
    rep(i,3) rep(j,3) {
        char c;
        cin >> c;
        if (c=='_') grid[i][j]=0;
        if (c=='X') grid[i][j]=1;
        if (c=='O') grid[i][j]=-1;
        nonempty += grid[i][j]!=0;
    }

    if (nonempty%2==0) { // johan

    }
    else { // abdullah
        mirror(grid);
    }
    solve(grid,nonempty%2);
    int t = winning[0]+winning[1];
    if (t==0) cout << "ingen kan vinna\n";
    if (t==1) cout << (winning[0]?"Johan" : "Abdullah") << " kan vinna\n";
    if (t==2) cout << "Abdullah och Johan kan vinna\n";

    return 0;
}
