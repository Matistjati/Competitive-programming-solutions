#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
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

int nums[1771562];

inline int plateToNum(int P[6])
{
    int v = 0;

    int m = 1;
    #pragma GCC ivdep
    #pragma GCC unroll 6
    rep(i, 6)
    {
        v += (P[i] == -1 ? 10 : P[i]) * m;
        m *= 11;
    }
    return v;
}

int np[6];

int plate(int P[6])
{

    int matches = 0;

    matches += nums[plateToNum(P)];

    #pragma GCC ivdep
    #pragma GCC unroll 64
    rep(i, (1 << 6))
    {
        bool match = true;

        #pragma GCC ivdep
        #pragma GCC unroll 6
        rep(j, 6)
        {
            bool setBit = (i & (1 << j));
            if ((setBit && P[j] == -1))
            {
                match = false;
            }
            np[j] = (setBit) ? -1 : P[j];
        }

        if (match)
        {
            nums[plateToNum(np)]++;
        }
    }

    return matches;
}


__attribute__((constructor))
void fake_main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    int x[6];
    rep(i,n) {
        rep(j,6) cin >> x[j];
        cout << plate(x) << '\n';
    }
    cout << flush;
    _Exit(0);
}

// int main() {
//     cin.tie(0)->sync_with_stdio(0);


//     return 0;
// }
