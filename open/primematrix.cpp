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

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
        ll ret = a * b - M * ull(1.L / M * a * b);
        return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
        ull ans = 1;
        for (; e; b = modmul(b, b, mod), e /= 2)
                if (e & 1) ans = modmul(ans, b, mod);
        return ans;
}
bool isPrime(ull n) {
        if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
        ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
            s = __builtin_ctzll(n-1), d = n >> s;
        for (ull a : A) {   // ^ count trailing zeroes
                ull p = modpow(a%n, d, n), i = s;
                while (p != 1 && p != n - 1 && a % n && i--)
                        p = modmul(p, p, n);
                if (p != n-1 && i != s) return 0;
        }
        return 1;
}

auto start = chrono::high_resolution_clock::now();
ll n,b;
bool brute(vi& ro, int lo, ll tot) {
    if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count() > 950) {
        cout << "impossible\n";
        exit(0);
    }
    if (sz(ro)==n) {
        return isPrime(tot);
    }

    repp(v,lo,b+1) {
        tot+=v;
        ro.push_back(v);

        if (brute(ro, v+1,tot)) return true;

        ro.pop_back();
        tot-=v;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> b;


    vector<ll> toprow;
    brute(toprow, 1, 0);


    if (sz(toprow)==0) {
        cout << "impossible\n";
        return 0;
    }

    rep(i,n) {
        rep(j,n) cout << toprow[j] << ' ';
        cout << '\n';
        toprow.insert(toprow.begin(),toprow.back());
        toprow.pop_back();
    }


    return 0;
}
