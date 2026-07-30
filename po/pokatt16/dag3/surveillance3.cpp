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

ll surveillance(int B, int W, int S[1000][1000], int T[1000][1000]) {

    ll base = (ll)(31);

    // Precompute base**i
    const ll precompSize = 1000 * 1000 + 1;
    vector<ll> powtable(precompSize);
    ll m = 1;
    rep(i, precompSize)
    {
        powtable[i] = m;
        m *= base;
    }

    vector<vector<ll>> rows(B - W + 1, vector<ll>(B));
    vector<vector<ll>> cols(B - W + 1, vector<ll>(B));
    rep(i, B)
    {
        ll hashV = 0;

        ll ind = B - (B - W) - 1;
        for (int j = B - 1; j >= B - W; j--)
        {
            hashV += powtable[ind] * S[i][j];
            ind--;
        }
        ind = B - (B - W) - 1;

        rows[B - W][i] = hashV;

        for (int j = B - 2; j >= 0; j--)
        {
            if (B - W - (B - 1 - j) < 0) break;
            hashV -= S[i][j + 1] * powtable[ind];
            hashV *= base;
            hashV += S[i][j - W + 1];
            rows[B - W - (B - 1 - j)][i] = hashV;
        }
    }

    rep(j, B)
    {
        ll hashV = 0;

        ll ind = (W * W - W);
        for (int i = B - 1; i >= B - W; i--)
        {
            hashV += powtable[ind] * S[i][j];
            ind -= W;
        }
        ind = W * W - W;

        cols[B - W][j] = hashV;

        for (int i = B - 2; i >= 0; i--)
        {
            if (B - W - (B - 1 - i) < 0) break;
            hashV -= S[i + 1][j] * powtable[ind];
            hashV *= powtable[W];
            hashV += S[i - W + 1][j];
            cols[B - W - (B - 1 - i)][j] = hashV;
        }
    }

    ll matches = 0;
    ll hashThief = 0;
    m = 1;
    ll mul = 0;
    rep(k, W)
    {
        rep(l, W)
        {
            hashThief += m * (T[k][l]);
            mul += m;
            m *= base;
        }
    }

    // B security size
    rep(i, B - W + 1)
    {
        ll hashV = 0;
        ll m = 1;

        rep(k, W)
        {
            hashV += rows[B - W][i + k] * m;
            m *= powtable[W];

        }

        ll hashW = hashThief + (S[i][B - W] - T[0][0]) * mul;

        matches += (hashW == hashV);

        rep(j, B - W)
        {
            hashV -= cols[i][B - j - 1] * powtable[W - 1];

            hashV *= base;
            hashV += cols[i][B - j - 1 - W];

            ll hashW = hashThief + (ll)(S[i][B - W - j - 1] - T[0][0]) * mul;
            matches += (hashW == hashV);

            //hashes[hashV]++;
        }
    }

    return matches;
}
