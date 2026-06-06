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

    string s;
    getline(cin, s);
    getline(cin, s);

    stack<char> st;
    int i = 0;
    auto isright = [](char c) {
        return c == ']' || c == '}' || c == ')';
    };
    auto rev = [](char c) {
        if (c == ']') return '[';
        if (c == '}') return '{';
        if (c == ')') return '(';
        assert(0);
    };
    repe(c, s) {
        i++;
        if (c == ' ') continue;
        if (isright(c) && (st.empty() || st.top() != rev(c))) {
            cout << c << ' ' << i-1 << '\n';
            return 0;
        }
        if (isright(c)) st.pop();
        else st.push(c);
    }

    cout << "ok so far\n";

    return 0;
}
