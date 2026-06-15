#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
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

vector<int> dices;

void solve() {
    int n;
    cin >> n;
    int chars=0;
    int words[26]{};
    memset(words,0,sizeof(words));
    rep(i, n) {
        string s;
        cin >> s;
        chars |= 1 << (s[0] - 'a');
        if (sz(s) > 1) words[s[0] - 'a'] |= 1 << (s[1] - 'a');
    }

    int ans = 0;
    int bestd = -1;
    auto consider = [&](int dice, int ev) {
        if (ev > ans) {
            bestd = dice;
            ans = ev;
        }
    };

    repe(dice, dices) {
        consider(dice, popcount((unsigned int)(dice & chars)) * 6);

        unsigned int deaddice = dice;
        int ev = 0;
        while (deaddice) {
            int ind = 31-countl_zero(deaddice);
            deaddice &= ~(1 << ind);

            int v = max(6, 2 * popcount((unsigned int)(words[ind] & dice)));
            ev += ((chars & (1<<ind))>0) ? v : 0;
        }
        consider(dice, ev);
    }
    // cerr << "ans= " << ans << '\n';
    // cerr << "bestd= " << bestd << '\n';
    rep(i, 26) {
        if (bestd & (1 << i)) {
            cout << (char)(i + 'a');
        }
    }
    cout << '\n';
    cout << fixed << setprecision(15) << ans/36.0 << '\n';
}

void dfs(int i, char lo, string& s) {
    if (sz(s) == 6) {
        int val = 0;

        for (char c : s) {
            val |= 1 << (c - 'a');
        }
        dices.push_back(val);
        return;
    }

    repp(c, lo, 'z' + 1) {
        s.push_back(c);
        dfs(i + 1, c + 1, s);
        s.pop_back();
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string s;
    dfs(0, 'a', s);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
