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

ull pollard(ull n) {
        auto f = [n](ull x) { return modmul(x, x, n) + 1; };
        ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
        while (t++ % 40 || __gcd(prd, n) == 1) {
                if (x == y) x = ++i, y = f(x);
                if ((q = modmul(prd, max(x,y) - min(x,y), n))) prd = q;
                x = f(x), y = f(f(y));
        }
        return __gcd(prd, n);
}
vector<ull> factor(ull n) {
        if (n == 1) return {};
        if (isPrime(n)) return {n};
        ull x = pollard(n);
        auto l = factor(x), r = factor(n / x);
        l.insert(l.end(), all(r));
        return l;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n,m;
    cin >> n >> m;
    vector<ull> factors = factor(n);
    
    ll smallestodd = 1e10;
    repe(f,factors) if (f%2==1) smallestodd = min<ll>(smallestodd,f);
    if (m%2==0) {
        cout << "Yes\n";
    }
    else if (m>=smallestodd&&n-m>=smallestodd) {
        cout << "Yes\n";
    }
    else {
        cout << "No\n";
    }


    return 0;
}
