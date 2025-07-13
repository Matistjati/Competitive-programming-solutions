#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

#if _LOCAL
#include <__msvc_int128.hpp>
typedef _Unsigned128 big_unsigned;
#else
typedef __uint128_t big_unsigned;
#endif

typedef big_unsigned ull;
typedef unsigned long long ull_real;
#if _LOCAL
#include <__msvc_int128.hpp>
ull modmul(ull a, ull b, ull c) {
    return (ull)(_Unsigned128(a) * b % c);
}
#else
ull modmul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
#endif
// b^e % mod
ull modpow(ull b, ull e, ull mod) {
    ull ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}

ull gcd(ull a, ull b) {
    while (b != 0) {
        ull temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {
    2, 325, 9375, 28178, 450775, 9780504, 1795265022,
    123456789012345ULL, 98765432109876ULL, 1122334455667788ULL,
    4294967291ULL, 18446744073709551557ULL, 305419896ULL,
    9223372036854775807ULL, 1357924680ULL
    };

        ull s = countr_zero((ull_real)(n - 1)), d = n >> s;
    for (ull a : A) {   // ^ count trailing zeroes
        ull p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}

ull pollard(ull n) {
    auto f = [n](ull x) { return modmul(x, x, n) + 1; };
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return gcd(prd, n);
}
vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return { n };
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

vector<ull> getDivisors(vector<ull> primes) {
    map<ull, int> cnt;
    repe(p, primes) cnt[p]++;
    vector<ull> d = { 1 };
    for (auto [p, e] : cnt) {
        int n0 = sz(d);
        rep(i, n0) {
            ull cur = d[i];
            rep(j, e) {
                cur *= p;
                d.push_back(cur);
            }
        }
    }
    sort(all(d));
    return d;
}


ull isPerfectSquare(ull x) {
    if (x == 0 || x == 1) return true;

    ull left = 0;
    ull right = (ull)1 << 64;

    while (left <= right) {
        ull mid = left + (right - left) / 2;
        ull sq = mid * mid;

        if (sq == x) {
            return mid;
        }
        else if (sq < x) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return left;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;

    vector<ull> cands;

    auto trycand = [&](ull div)
        {
            ull v = (8 * n) / div;
            if ((div + v) % 2 != 0) return;
            if (v < div) return;
            ull m = (v - div) / 2 + 1;

            if (m % 2 == 0 && m > 0)
            {
                cands.push_back(m / 2);
            }
        };

    repe(div, getDivisors(factor(8 * n)))
    {
        trycand(div);
    }
    sort(all(cands));

    repe(a, cands)
    {
        ull disc = ull(1 + 8 * n + 4 * a * a - 4 * a);
        if (disc < 0) continue;
        ull root = isPerfectSquare(disc);
        if (root * root != disc) continue;
        root -= 2 * a - 1;
        if (root < 1 || root % 2 == 1) continue;
        cout << (ull_real)a << " " << (ull_real)root / 2 << "\n";
    }

    return 0;
}
