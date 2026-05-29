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

int winning[1 << 16];
string best_move[1 << 16];
int res_mask[1 << 16];

int solve(int mask) {
    if (winning[mask] != -1) return winning[mask];

    auto at = [&](int i, int j) {
        return (mask & (1 << (i * 4 + j))) > 0;
    };

    auto char_at = [](int i, int j) {
        return string(1, 'A' + (i * 4 + j));
    };

    vector<pair<string, int>> legalmoves;
    rep(i, 4) {
        rep(j, 4) {
            int m = mask;
            string move;
            rep(o, 4) {
                if (j + o >= 4) break;
                if (!at(i, j+o)) break;
                m &= ~(1 << (i * 4 + j+o));
                if (m == 0) break;
                move += char_at(i, j+o) + " ";
                legalmoves.emplace_back(move, m);
            }
        }
    }
    rep(i, 4) {
        rep(j, 4) {
            int m = mask;
            string move;
            rep(o, 4) {
                if (i + o >= 4) break;
                if (!at(i+o, j)) break;
                m &= ~(1 << ((i+o) * 4 + j));
                if (m == 0) break;
                move += char_at(i+o, j) + " ";
                legalmoves.emplace_back(move, m);
            }
        }
    }
    if (legalmoves.empty()) {
        return winning[mask] = 0;
    }

    bool canwin = false;
    for (auto [s, m] : legalmoves) {
        bool they = solve(m);
        if (!they) {
            canwin = true;
            best_move[mask] = s;
            res_mask[mask] = m;
            break;
        }
    }

    return winning[mask] = canwin;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    memset(winning, -1, sizeof(winning));

    int curr_mask = (1 << 16) - 1;
    while (1) {
        string oppmove;
        getline(cin, oppmove);
        stringstream ss(oppmove);
        string s;
        while (ss >> s) {
            curr_mask &= ~(1 << (s[0] - 'A'));
        }
        if (curr_mask==0) return 0;
        solve(curr_mask);

        assert(winning[curr_mask]);
        cout << best_move[curr_mask] << endl;


        curr_mask = res_mask[curr_mask];
    }


    return 0;
}
