#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

// Also has modmul
typedef unsigned long long ull;
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
bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 },
        s = countr_zero(n - 1), d = n >> s;
    for (ull a : A) {   // ^ count trailing zeroes
        ull p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}

const int MAX_PR = 1e8;
bitset<MAX_PR> isprime;
void eratosthenesSieve(int lim = MAX_PR - 1) {
    isprime.set(); isprime[0] = isprime[1] = 0;
    for (int i = 4; i < lim; i += 2) isprime[i] = 0;
    for (int i = 3; i * i < lim; i += 2) if (isprime[i])
        for (int j = i * i; j < lim; j += i * 2) isprime[j] = 0;
}



#ifdef _MSC_VER
#include <intrin.h>
#pragma intrinsic(_umul128)
#endif

bool multiply_with_overflow(unsigned long long a, unsigned long long b, unsigned long long* result) {
#ifdef _MSC_VER
    unsigned long long high;
    *result = _umul128(a, b, &high);
    return high != 0;
#else
    __uint128_t product = (__uint128_t)a * (__uint128_t)b;
    *result = (unsigned long long)product;
    return (product >> 64) != 0;
#endif
}

bool multiply_with_overflow_s(int a, int b, int* result) {
#ifdef _MSC_VER
    __int64 high;
    __int64 low = _mul128(a, b, &high);
    if ((high == 0 && low >= 0) || (high == -1 && low < 0)) {
        *result = (int)low;
        return false;
    }
    return true;
#else
    __int128 product = (__int128)a * (__int128)b;
    if (product < LLONG_MIN || product > LLONG_MAX) {
        return true;
    }
    *result = (int)product;
    return false;
#endif
}

signed main()
{
    fast();

    eratosthenesSieve();

    auto is_prime = [&](int x)
        {
            if (x < sz(isprime)) return (bool)isprime[x];
            return isPrime(x);
        };

    int hi = int(1e15) + 10;
    vi exploding;
    if (1)
    {
        repp(a, 1, int(1e5) + 10)
        {
            repp(b, 1, int(1e5) + 10)
            {
                ull last = 1;
                ull p = 1;
                bool toobig = 0;
                repp(cnt, 1, int(1e10))
                {
                    ull nxt = last;
                    if (multiply_with_overflow(nxt, a, &nxt))
                    {
                        toobig = 1;
                        break;
                    }
                    nxt += b;
                    if (multiply_with_overflow(p, nxt, &p))
                    {
                        toobig = 1;
                        break;
                    }
                    if (p > hi)
                    {
                        toobig = 1;
                        break;
                    }
                    if (cnt >= 3)
                    {
                        break;
                    }
                    last = nxt;
                }
                if (toobig)
                {
                    //cout << "broke at " << b << '\n';
                    break;
                }

                last = 1;
                p = 1;
                repp(cnt, 1, int(1e10))
                {
                    ull nxt = last;
                    if (multiply_with_overflow(nxt, a, &nxt))
                    {
                        break;
                    }
                    nxt += b;
                    if (!is_prime(nxt))
                    {
                        break;
                    }
                    if (multiply_with_overflow(p, nxt, &p))
                    {
                        break;
                    }
                    if (p > hi) break;
                    if (cnt >= 3)
                    {
                        exploding.push_back(p);
                    }
                    last = nxt;
                }
            }
        }
    }

    int m = 0;
    repp(a, 1, 6e4)
    {
        repp(b, -a, -a+284)
        {
            int last = 1;
            int p = 1;
            if (a + b <= 0) continue;
            if (b >= 0) continue;
            repp(cnt, 1, int(1e10))
            {
                int nxt = last;
                if (multiply_with_overflow_s(nxt, a, &nxt))
                {
                    break;
                }
                nxt += b;
                if (nxt <= 0) break;
                if (!is_prime(nxt))
                {
                    break;
                }
                if (multiply_with_overflow_s(p, nxt, &p))
                {
                    break;
                }
                if (p > hi) break;
                if (cnt >= 3)
                {
                    int k = abs(a + b);
                    m = max(m, k);
                    //cout << m << '\n';
                    exploding.push_back(p);
                }
                last = nxt;
            }
        }
    }
    cerr << sz(exploding) << '\n';

    int q;
    cin >> q;
    while (q--)
    {
        int lo, hi;
        cin >> lo >> hi;
        int ans = 0;
        repe(p, exploding)
        {
            if (p >= lo && p <= hi)
            {
                ans++;
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
