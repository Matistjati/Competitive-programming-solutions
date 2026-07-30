#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,aes,abm,bmi,bmi2,popcnt,lzcnt")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll,ll>;
const ll inf = 1e18;

#define repe(i, arr) for (auto& i : arr)
#define rep(i, b) for(ll i = 0; i < (b); ++i)
#define repp(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)x.size())

constexpr const int maxv = int(2e5+10);
using custom_bitset = bitset<maxv>;

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n, k;
    cin >> n >> k;

    vi types(n);

    vector<custom_bitset> sets(k);

    rep(i, n)
    {
        string type;
        cin >> type;
        types[i] = stoll(type, 0, 2);
        rep(j, k)
        {
            if (type[j] == '1')
            {
                sets[j].set(i);
            }
        }
    }

    ll q;
    cin >> q;

    const int N_PARTS = 5;
    if (k<=N_PARTS)
    {
        while (q--)
        {
            string queryS;
            cin >> queryS;

            ll query = stoi(queryS, 0, 2);
            ll match = -1;
            ll n_matches = 0;

            rep(i, n)
            {
                if ((types[i] & query) == query)
                {
                    match = i;
                    n_matches++;
                }
            }

            if (n_matches == 0) cout << "finns ej";
            else if (n_matches == 1) cout << match+1;
            else cout << "vet ej";

            cout << '\n';
        }
        return 0;
    }


    auto build = [&](int l, int r) {
        int count = r - l;
        vector<custom_bitset> ret(1 << count);

        ret[0].set();

        for (int mask = 1; mask < (1 << count); ++mask)
        {
            int bitpos = __builtin_ctz(mask);
            int prev_mask = mask ^ (1 << bitpos);
            int i = r - 1 - bitpos;
            ret[mask] = ret[prev_mask] & sets[i];
        }

        return ret;
    };

    array<vector<custom_bitset>, N_PARTS> parts;
    vi block_sizes(N_PARTS);
    vi block_sizes_pref(N_PARTS);

    {
        int fake_k = k;

        int i = 0;
        while (fake_k) {
            block_sizes[i++]++;
            i %= N_PARTS;
            fake_k--;
        }
        block_sizes_pref = block_sizes;
        block_sizes_pref.insert(block_sizes_pref.begin(), 0);
        repp(i, 1, sz(block_sizes_pref)) block_sizes_pref[i] += block_sizes_pref[i - 1];
    }

    rep(i, N_PARTS) {
        parts[i] = build(block_sizes_pref[i], block_sizes_pref[i + 1]);
    }

    custom_bitset possible;

    while (q--)
    {
        string queryS;
        cin >> queryS;

        possible.set();
        int i = 0;
        while (sz(queryS)) {
            string s = queryS.substr(0, block_sizes[i]);
            rep(j, block_sizes[i]) {
                queryS.erase(queryS.begin());
            }
            ll val = stoll(s, 0, 2);
            possible &= parts[i++][val];
        }

        int cnt = possible.count();
        if (cnt == 0) cout << "finns ej";
        else if (cnt == 1) cout << 1 + possible._Find_first();
        else cout << "vet ej";
        cout << "\n";
    }

    return 0;
}
