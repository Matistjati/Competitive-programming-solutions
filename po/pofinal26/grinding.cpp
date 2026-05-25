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


int main()
{
    cin.tie(0)->sync_with_stdio(0);

    int n, b;
    cin >> n >> b;

    vector<vector<p2>> dungeons(n);
    rep(i, n)
    {
        int m;
        cin >> m;
        dungeons[i].resize(m);
        rep(j, m) cin >> dungeons[i][j].first >> dungeons[i][j].second;
    }

    ll ans = inf;
    ll runs = 0;
    ll strength = 1;
    ll best_prev = 0;

    rep(i, n) // i just unlocked dungeon i
    {
        vi breakpoints = { dungeons[i][0].first };
        vi breakpoint_gain = { dungeons[i][0].second };
        {
            vector<p2>& dungeon = dungeons[i];
            ll start_strength = dungeon[0].first;
            ll extra_strength = dungeon[0].second;
            repp(j, 1, sz(dungeon))
            {
                if (start_strength + extra_strength >= dungeon[j].first)
                {
                    //
                }
                else
                {
                    ll delta = dungeon[j].first - (start_strength + extra_strength);
                    start_strength += delta;
                }
                breakpoints.push_back(start_strength);
                extra_strength += dungeon[j].second;
                breakpoint_gain.push_back(extra_strength);
            }
            breakpoints.push_back(inf);
            breakpoint_gain.push_back(extra_strength);
        }

        auto min_to_get = [&](ll target)
        {
            ll str = strength;
            ll newruns = 0;

            if (best_prev)
            {
                auto gain_point = lower_bound(all(breakpoint_gain), best_prev);
                ll breakeven_strength;
                if (gain_point == breakpoint_gain.end()) breakeven_strength = target;
                else breakeven_strength = breakpoints[gain_point - begin(breakpoint_gain)];
                ll num_prev = (breakeven_strength - strength + best_prev - 1) / best_prev;
                if (num_prev > 0)
                {
                    str += num_prev * best_prev;
                    newruns += num_prev;
                }
            }
            while (str < target)
            {
                assert(str >= breakpoints[0]);
                auto it = upper_bound(all(breakpoints), str);
                assert(it != begin(breakpoints));
                it = prev(it); // last with breakpoint <= str
                ll curr_gain = breakpoint_gain[it - begin(breakpoints)];
                ll next_breakpoint;
                if (*next(it) == inf) // no improvement possible
                {
                    next_breakpoint = target;
                }
                else next_breakpoint = min(target, *next(it));
                ll num_runs = (next_breakpoint - str + curr_gain - 1) / curr_gain;
                str += num_runs * curr_gain;
                newruns += num_runs;
            }
            return make_pair(str, newruns);
        };

        // Ans if we dont care about unlocking more dungeons
        ans = min(ans, runs + min_to_get(b).second);

        // Cheapeast way to get strong enough to unlock new dungeon
        ll strength_to_defeat = breakpoints[sz(breakpoints) - 2];
        ll newruns;
        tie(strength, newruns) = min_to_get(strength_to_defeat);
        runs += newruns;

        // Run the dungeon
        runs++;
        ll dungeon_profit = breakpoint_gain.back();
        best_prev = max(best_prev, dungeon_profit);
        strength += dungeon_profit;
    }
    cout << ans << '\n';

    return 0;
}
