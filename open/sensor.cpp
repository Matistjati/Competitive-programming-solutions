#pragma GCC optimize("Ofast")
#include <bits/allocator.h>
#pragma GCC target("avx2,bmi,bmi2,popcnt")
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


// also include
/*
#pragma GCC optimize("Ofast")
#include <bits/allocator.h>
#pragma GCC target("avx2,bmi,bmi2,popcnt")
#include <bits/stdc++.h>
...
*/
using bset = bitset<100>;
const double TIME_LIMIT_MS = 1500;
const int RESTARTS = 500;
bset max_indep_set(vector<bset> adj)
{
    if (sz(adj) == 0) return {};
    rep(i, sz(adj)) adj[i][i] = 0;

    bset best_set;
    int best_size = 0;
    using namespace chrono;
    auto solve = [&]()
    {
        int indep_set_size = 0;
        bset indep;
        uniform_int_distribution<int> dist_n(0, sz(adj) - 1);

        uniform_real_distribution<double> dist_01(0, 1);
        mt19937 rng(time(0));
        double t_start = sz(adj)/10, t_end = 4e-2; // t_end<t_start
        auto start = high_resolution_clock::now();

        int current_size = 0;
        int its = 0;
        double tim = 0, temp = t_start;
        while (1) {
            if ((its++) % 128 == 0)
            {
                tim = duration_cast<milliseconds>(high_resolution_clock::now() - start).count() / (TIME_LIMIT_MS / RESTARTS);
                if (tim > 0.99) break;
                temp = t_start * pow(t_end / t_start, tim);
            }
            if (its % 100000 == 0)
            {
                cerr << "size: " << indep_set_size << ", temp:" << temp << ", time:" << tim << '\n';
            }
            // mutate
            int ind = dist_n(rng);
            bset kicked_out;
            if (indep[ind])
            {
                indep_set_size--;
            }
            else
            {
                kicked_out = indep & adj[ind];

                indep_set_size++;
                indep_set_size -= kicked_out.count();
            }
            indep[ind] = !indep[ind];

            int new_cost = indep_set_size;
            if (new_cost > current_size || dist_01(rng) < exp((new_cost - current_size) / temp)) {
                current_size = new_cost;
                if (current_size>best_size)
                {
                    best_size = current_size;
                    best_set = indep;
                }
                indep &= ~kicked_out;
            }
            else {
                //undo
                indep_set_size += kicked_out.count();
                indep_set_size += indep[ind] ? -1 : 1;
                indep[ind] = !indep[ind];
            }
        }
    };
    rep(i, RESTARTS)
    {
        solve();
        //cerr << "RESTART\n";
    }
    return best_set;
}

bset max_clique(vector<bset> adj)
{
    rep(i, sz(adj)) adj[i] = ~adj[i];
    return max_indep_set(adj);
}
bset min_vertex_cover(vector<bset> adj)
{
    return ~max_indep_set(adj);
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, d;
    cin >> n >> d;
    vector<p2> pts(n);
    repe(p, pts) cin >> p.first >> p.second;
    vector<bset> adj(n);

    auto dist = [&](p2 a, p2 b)
    {
        int dx = a.first - b.first;
        int dy = a.second - b.second;
        return hypot(dx, dy);
    };
    rep(i, n) rep(j, n)
    {
        if (dist(pts[i],pts[j])<=d+1e-6)
        {
            adj[i][j] = 1;
            adj[j][i] = 1;
        }
    }
    bset ans = max_clique(adj);
    cout << ans.count() << '\n';
    rep(i, sz(ans)) if (ans[i]) cout << i + 1 << ' ';

    return 0;
}
