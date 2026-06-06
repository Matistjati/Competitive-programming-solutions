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

    auto sort = [](pair<ll, ll>& a, pair<ll, ll>& b, pair<ll, ll>& c) {
        if (a.first > b.first) swap(a, b);
        if (a.first > c.first) swap(a, c);
        if (b.first > c.first) swap(b, c);
    };


    using P = pair<ll, ll>;
    vector<array<ll,3>> moves;
    pair<ll, ll> a, b, c;
    cin >> a.first >> b.first >> c.first;
    a.second = 0;
    b.second = 1;
    c.second = 2;
    sort(a, b, c);

    auto move = [&](int i, int j) {
        assert(i != j);
        P* x=0, *y=0;
        if (i == 0) x = &a;
        else if (i == 1) x = &b;
        else if (i == 2) x = &c;
        else assert(0);
        if (j == 0) y = &a;
        else if (j == 1) y = &b;
        else if (j == 2) y = &c;
        else assert(0);
        tie(x->first, y->first) = make_pair(x->first-y->first, y->first*2);
        array<ll,3> st;
        for (auto [amnt, ind] : {a,b,c}) {
            st[ind]=amnt;
        }
        moves.push_back(st);
    };

    while (a.first > 0) {
        ll div = b.first / a.first;
        ll rem = b.first % a.first;
        while (div) {
            if (div % 2 == 1) move(1, 0);
            else move(2, 0);
            div /= 2;
        }
        sort(a, b, c);
    }
    cout << sz(moves) << '\n';
    for (auto [a,b,c] : moves) {
        cout << a << ' ' << b << ' ' << c << '\n';
    }

    return 0;
}
