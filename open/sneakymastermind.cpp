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

int strikes = 1;

int n, c;
vector<vector<char>> color_candidates;
void gen_color_sets(vector<char>& colors)
{
    if (sz(colors) == n)
    {
        color_candidates.push_back(colors);
        return;
    }
    int lo = sz(colors) ? colors.back() : 0;
    repp(col, lo, c)
    {
        colors.push_back(col);
        gen_color_sets(colors);
        colors.pop_back();
    }
}

char seen_g[15];
char seen_r[15];
int t = 0;
p2 simulate_guess(vector<char>& g, vector<char>& real)
{
    assert(g.size() == real.size());
    memset(seen_g, 0, sizeof(seen_g));
    memset(seen_r, 0, sizeof(seen_r));
    t++;
    int corr = 0;
    rep(i, n)
    {
        if (g[i] == real[i])
        {
            corr++;
        }
    }
    rep(i, n) seen_g[g[i]]++;
    rep(i, n) seen_r[real[i]]++;

    int common_colors = 0;
    rep(i, 15) common_colors += min(seen_g[i], seen_r[i]);
    return { corr,common_colors - corr };
}

int num_guess = 0;
#if _LOCAL
vector<char> ans;
p2 guess(vector<char>& g)
{
    num_guess++;
    if (ans.empty())
    {
        uniform_int_distribution<int> dist(0, c - 1);
        mt19937 rng(10);
        while (sz(ans) < n) ans.push_back(dist(rng));
    }
    return simulate_guess(g, ans);
}
#else
p2 guess(vector<char>& g)
{
    num_guess++;
    repe(c, g)
    {
        cout << (char)(c + 'a');
    }
    cout << endl;
    p2 res;
    cin >> res.first >> res.second;
    return res;
}
#endif

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> c;
    auto start = chrono::high_resolution_clock::now();
    color_candidates.reserve(4e6);

    vector<char> colors;
    gen_color_sets(colors);

    vector<pair<vector<char>, p2>> first_stage_guesses;
    auto get_colorset = [&]()
    {
        vector<char> impossibles(sz(color_candidates));
        mt19937 rng(42);
        while (sz(color_candidates) > 1)
        {
            cerr << "SIZE: " << sz(impossibles) << '\n';
            uniform_int_distribution<int> distn(0, sz(color_candidates) - 1);
            rep(i, sz(color_candidates))
            {
                int v = distn(rng);
                swap(color_candidates[i], color_candidates[v]);
                swap(impossibles[i], impossibles[v]);
            }

            if (sz(color_candidates) == 1) break;
            int min_strikes = inf;
            int ind = -1;
            rep(i, sz(impossibles))
            {
                if (impossibles[i]<min_strikes)
                {
                    min_strikes = impossibles[i];
                    ind = i;
                }
            }
            if (ind==-1)
            {
                strikes = 0;
                ind = 0;
            }
            vector<char> g = color_candidates[ind];

            p2 res = guess(g);
            first_stage_guesses.emplace_back(g, res);
            int num_corr = res.first + res.second;
            if (num_corr == n)
            {
                return g;
            }
            vector<vector<char>> filtered;
            vector<char> filtered_imp;
            rep(i, sz(color_candidates))
            {
                p2 they = simulate_guess(color_candidates[i], g);
                if (they.first + they.second != num_corr)
                {
                    impossibles[i]++;
                }
                if (impossibles[i]<=strikes)
                {
                    filtered_imp.push_back(impossibles[i]);
                    filtered.push_back(color_candidates[i]);
                }
            }
            impossibles = filtered_imp;
            color_candidates = filtered;
        }
        return color_candidates[0];
    };
    vector<char> color_set = get_colorset();
    cerr << "Guesses first part: " << num_guess << '\n';

    auto get_ans = [&]()
    {
        vector<vector<char>> final_cands;
        do
        {
            bool good = 1;

            repe(g, first_stage_guesses) good &= simulate_guess(g.first, color_set) == g.second;

            if (good) final_cands.push_back(color_set);
        } while (next_permutation(all(color_set)));
        mt19937 rng(42);
        vector<char> impossibles(sz(final_cands));
        cerr << "FILTERED SIZE: " << sz(impossibles) << '\n';

        while (sz(final_cands) > 1)
        {
            uniform_int_distribution<int> distn(0, sz(final_cands) - 1);
            rep(i, sz(final_cands))
            {
                int v = distn(rng);
                swap(final_cands[i], final_cands[v]);
                swap(impossibles[i], impossibles[v]);
            }

            while (impossibles.back() > strikes)
            {
                impossibles.pop_back();
                final_cands.pop_back();
            }
            if (sz(final_cands) == 1) break;
            vector<char> g = final_cands.back();

            p2 res = guess(g);
            if (res.first == n)
            {
                return g;
            }
            rep(i, sz(final_cands))
            {
                p2 they = simulate_guess(final_cands[i], g);
                if (they != res)
                {
                    impossibles[i]++;
                }
            }
        }
        return final_cands[0];
    };

    vector<char> res = get_ans();
    cerr << "Guesses after second part: " << num_guess << '\n';
    cerr << "time: " << (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count()) << "ms\n";
#if _LOCAL
    assert(res == ans);
#endif
    cout << "! ";
    repe(v, res)
    {
        cout << (char)(v + 'a');
    }

    return 0;
}
