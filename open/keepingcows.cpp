#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll,ll>;
#define rep(i,n) for (int i = 0; i < (n); i++)
const ll inf = 1e18;
#define sz(x) ((ll)x.size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int k;
    cin >> k;

    int r = 100;
    int c = 100;

    cout << r << " " << c << '\n';

    vector<string> grid(r, string(c, '.'));
    for (int co = 0; co < c; co+=2) {
        grid[0][co]='#';
        grid[1][co]='O';
        grid[1][co+1]='#';
    }
    for (int ro = 2; ro < r; ro+=2) {
        grid[ro][1]='#';
        grid[ro+1][1]='O';
        grid[ro+1][0]='#';
        grid[ro][c-2]='#';
        grid[ro+1][c-2]='O';
        grid[ro+1][c-1]='#';
    }
    for (int co = 2; co < c-2; co+=2) {
        grid[2][co]='#';
        grid[2][co+1]='O';
        grid[3][co+1]='#';
    }
    int w = c - 4;

    auto move_down = [&](int ro, int co) {
        grid[ro][co]='.';
        grid[ro][co+1]='.';
        grid[ro+1][co]='.';
        grid[ro+1][co+1]='.';
        grid[ro+1][co]='#';
        grid[ro+1][co+1]='O';
        grid[ro+2][co+1]='#';
    };
    auto rotate = [&](int ro, int co) {
        grid[ro][co]='.';
        grid[ro][co+1]='.';
        grid[ro+1][co]='.';
        grid[ro+1][co+1]='.';
        grid[ro+1][co]='#';
        grid[ro+0][co+1]='#';
        grid[ro+1][co+1]='O';
    };

    for (int ro = 2; ro < r; ro++) {
        for (int co = 2; co < c-2; co+=2) {
            if (k>1) {
                move_down(ro,co);
                k-=2;
            }
            else if (k==1) {
                rotate(ro,co);
                k-=1;
            }
            else {}
        }
    }

    rep(i,r) {
        cout << grid[i];
        cout << '\n';
    }
    return 0;
}
