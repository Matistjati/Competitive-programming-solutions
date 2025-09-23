#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
using namespace std;
#include <bits/stdc++.h>
using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;

#define rep(i,n) for (int i = 0; i < (n); i++)
#define repp(i,a,b) for (int i = (a); i < (b); i++)
#define repe(i,a) for (auto& i : a)
#define all(x) begin(x),end(x)
#define sz(x) ((int)x.size())

typedef int T;
const int B = 9;
int cnt[1 << B] = { 0 };
int pref[1 << B];

vector<T> tmp(int(1e5 + 10));
void radix_sort_pairs(vector<T>& a) {
    const int MASK = (1 << B) - 1;
    const int PASSES = 2;
    int n = sz(a);

    for (int pass = 0; pass < PASSES; pass++) {
        memset(cnt, 0, sizeof(cnt));
        int shift = pass * B;

        for (int i = 0; i < n; i++)
            cnt[(a[i] >> shift) & MASK]++; // change this

        pref[0] = 0;
        for (int i = 1; i < (1 << B); i++)
            pref[i] = pref[i - 1] + cnt[i - 1];

        for (int i = 0; i < n; i++) {
            int d = (a[i] >> shift) & MASK; // and this
            tmp[pref[d]++] = a[i];
        }
        a.swap(tmp);
    }
}

int main()
{
    int n, b, r, w;
    cin >> n >> b >> r >> w;

    vi d(b);
    repe(v, d) cin >> v;
    vi prefd(d);
    repp(i, 1, sz(d)) prefd[i] += prefd[i - 1];

    vi q(n);
    repe(v, q) cin >> v, v--;

    auto works = [&](ll mid)
        {
            int i = 0;
            ll bus_number = 0;

            auto can_kick_off = [&](int amount)
                {
                    amount = min(amount, n - i);
                    if (amount == 0) return true;
                    vector<int> ppl(amount);
                    repp(j, i, i + amount)
                    {
                        ppl[j - i] = q[j];
                    }
                    ll base_time = bus_number * r + sz(ppl) * ll(w);
                    base_time += prefd[*max_element(all(ppl))];

                    if (sz(ppl) < 250) sort(all(ppl));
                    else radix_sort_pairs(ppl);


                    int inbus = sz(ppl);
                    int p = 0;
                    int tot_w = 0;
                    while (p < sz(ppl))
                    {
                        int v = ppl[p];
                        int amnt = 0;
                        while (p < sz(ppl) && ppl[p] == v) p++, amnt++;

                        inbus -= amnt;
                        tot_w += amnt;
                        tot_w += inbus * 2;
                    }
                    base_time += ll(tot_w) * w;

                    return base_time <= mid;
                };

            while (i < n)
            {
                // greedily kick off as many people as possible
                int lo = -1;
                int offset = 1;
                // binary searching for how big it is coarsely saves our complexity
                while (offset < n-i && can_kick_off(offset))
                {
                    offset *= 2;
                }

                int hi = offset+1;
                while (lo + 1 < hi)
                {
                    int mid = (lo + hi) / 2;
                    if (can_kick_off(mid)) lo = mid;
                    else hi = mid;
                }
                if (lo == 0) return false;
                i += lo;
                bus_number++;
            }

            return true;
        };

    ll lo = -1;
    ll hi = 1e13;
    while (lo + 1 < hi)
    {
        ll mid = (lo + hi) / 2;
        if (works(mid)) hi = mid;
        else lo = mid;
    }
    cout << hi << '\n';


    return 0;
}

