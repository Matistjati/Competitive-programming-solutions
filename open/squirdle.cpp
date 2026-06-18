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

    #if 1
    auto ask = [](string s) {
        cout << "? " << s << endl;
        string resp;
        cin >> resp;
        if (resp=="22222") exit(0);
        return resp;
    };
    #else
    string secret;
    uniform_int_distribution<int> dist('a','z');
    random_device rd;
    mt19937 rng(rd());
    rep(i,5) secret.push_back(dist(rng));
    cerr << "secret= " << secret << '\n';
    auto ask = [secret](string s) {
        string resp(5,'-');
        cerr << "? " << s << endl;
        rep(i,5) {
            if (s[i]==secret[i]) resp[i]='2';
            else if (find(all(secret),s[i])!=secret.end()) resp[i]='1';
            else resp[i]='0';
        }
        cerr << "= " << resp << '\n';
        return resp;
    };
    #endif

    string alpha;
    repp(c,'a','z'+1) alpha.push_back(c);
    rep(i,4) alpha.push_back('a'+i);

    char good[256]{};
    for (int i = 0; i < 25; i+=5) {
        string res = ask(alpha.substr(i,5));
        rep(j,5) {
            if (res[j]=='1' || res[j]=='2') {
                good[alpha.substr(i,5)[j]]=1;
            }
        }
    }

    string g;
    rep(i,256) {
        if (good[i]) g.push_back(i);
    }
    if (sz(g)==4) g.push_back('z');
    string ans(5,'-');
    rep(i,4) {
        string res = ask(g);
        rep(j,5) if (res[j]=='2') ans[j]=g[j];
        g.insert(begin(g), g.back());
        g.pop_back();
    }
    rep(j,5) if (ans[j]=='-') ans[j]=g[j];
    ask(ans);

    return 0;
}
