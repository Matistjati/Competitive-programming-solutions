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

    vector<string> alpha = {
        "@",
        "8",
        "(",
        "|)",
        "3",
        "#",
        "6",
        "[-]",
        "|",
        "_|",
        "|<",
        "1",
        "[]\\/[]",
        "[]\\[]",
        "0",
        "|D",
        "(,)",
        "|Z",
        "$",
        "']['",
        "|_|",
        "\\/",
        "\\/\\/",
        "}{",
        "`/",
        "2"
    };

    map<char,string> remap;
    rep(i,26) {
        remap[i+'a']=alpha[i];
    }
    remap[' '] = ' ';

    string s;
    getline(cin,s);
    repe(c,s) {
        c=tolower(c);
        if (c>='a'&&c<='z') cout << remap[c];
        else cout << c;
    }

    return 0;
}
