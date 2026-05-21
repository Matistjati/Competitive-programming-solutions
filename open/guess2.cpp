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

    auto guess = [](double x) { // is guess too low?
        cout << fixed << setprecision(15) << "? " << x << endl;
        string res;
        cin >> res;
        if (res=="That's" || res=="Eh,") {
            exit(0);
        }

        string nxt;
        cin >> nxt;
        return nxt == "low!";
    };

    double epsilon = 1e-6;
    vector<double> cands = {0};
    double curr = 0;
    while (curr<=1) cands.push_back(curr+=epsilon);
    curr = 0;
    while (exp(curr)<=1e9) cands.push_back(exp(curr+=epsilon));

    int lo = -1;
    int hi = sz(cands);
    while (1) {
        int mid = (lo+hi)/2;
        if (guess(cands[mid])) lo = mid;
        else hi = mid;
    }

    return 0;
}
