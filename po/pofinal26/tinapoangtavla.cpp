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

struct Team
{
    vi solved;
    vi problem_tries;
    p2 score = p2(0, 0);
    Team(int p) : solved(p), problem_tries(p) {}
    Team() {}

    void solve(int p)
    {
        assert(!solved[p]);
        solved[p] = 1;
        score.first++;
        score.second += problem_tries[p];
    }

    void fail(int p)
    {
        assert(!solved[p]);
        problem_tries[p]++;
    }

    void apply(tuple<int, int, char> sub)
    {
        auto [team, prob, verdict] = sub;
        if (verdict == 'W') fail(prob);
        else
        {
            solve(prob);
        }
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    const int BIG = 1e7;

    int n, p, h, f;
    cin >> n >> p >> h >> f;

    vector<Team> public_scores(n, Team(p));
    vvi totsubs(n, vi(p));
    rep(i, h)
    {
        int team, prob;
        string verdict;
        cin >> team >> prob >> verdict;
        team--; prob--;
        totsubs[team][prob]++;
        public_scores[team].apply(make_tuple(team, prob, verdict=="AC"?'A':'W'));
    }
    vector<Team> private_scores = public_scores;

    vi ans(n, -1);
    vi done(n);

    // per problem and team, frozen submissions compress to a potential +(0,0) or +(1, t)

    vector<tuple<int, int, char>> frozensubs;
    rep(i, f)
    {
        int team, prob;
        string verdict;
        cin >> team >> prob >> verdict;
        team--; prob--;
        frozensubs.emplace_back(team, prob, verdict=="AC"?'A':'W');
        private_scores[team].apply(frozensubs.back());
    }

    auto team_lowerbound = [&](int team_ind)
    {
        return public_scores[team_ind].score;
    };

    vvi numsubs(n, vi(p));
    vector<Team> public_upperbound = public_scores;
    for (auto [team, prob, verdict] : frozensubs)
    {
        totsubs[team][prob]++;
        numsubs[team][prob]++;
    }
    rep(team, n)
    {
        rep(prob, p)
        {
            if (numsubs[team][prob])
            {
                rep(j, numsubs[team][prob] - 1) public_upperbound[team].fail(prob);
                public_upperbound[team].solve(prob);
            }
        }
    }

    auto team_upperbound = [&](int team_ind)
    {
        return public_upperbound[team_ind].score;
    };

    auto canonicalize = [&](p2 p)
    {
        return BIG * p.first + (BIG - p.second);
    };


    multimap<ll, ll> finalpos;
    rep(i, n) finalpos.emplace(canonicalize(private_scores[i].score), i);

    vector<tuple<Team, Team, int>> changes;
    rep(frozen_idx, sz(frozensubs))
    {
        auto [team, prob, verdict] = frozensubs[frozen_idx];

        changes.emplace_back(public_scores[team], public_upperbound[team], team);
        if (numsubs[team][prob] == 1)
        {
            public_scores[team].apply(frozensubs[frozen_idx]);
            numsubs[team][prob]--;
            if (verdict == 'W')
            {
                public_upperbound[team].score.first--;
                public_upperbound[team].score.second -= totsubs[team][prob] - 1;
            }
        }
        else
        {
            public_scores[team].apply(frozensubs[frozen_idx]);
            assert(verdict == 'W');
            numsubs[team][prob]--;
        }
    }
    reverse(all(changes));
    int amount = f;
    repe(c, changes)
    {
        auto [t1, t2, team_index] = c;
        p2 range_before = { canonicalize(team_lowerbound(team_index)), canonicalize(team_upperbound(team_index)) };
        public_scores[team_index] = t1;
        public_upperbound[team_index] = t2;
        p2 range_after = { canonicalize(team_lowerbound(team_index)), canonicalize(team_upperbound(team_index)) };

        assert(range_before.first == range_after.first || range_before.second == range_after.second);

        auto pop = [&](ll lb, ll ub, int i)
        {
            auto it = finalpos.lower_bound(lb);
            while (true)
            {
                if (it == end(finalpos) || it->first >= ub) return;
                if (it->second == i)
                {
                    it = next(it);
                }
                else
                {
                    ans[it->second] = amount;
                    it = finalpos.erase(it);
                }
            }
        };

        if (range_before.first == range_after.first)
        {
            auto [lb, ub] = minmax(range_before.second, range_after.second);
            pop(lb, ub, team_index);
        }
        else
        {
            auto [lb, ub] = minmax(range_before.first, range_after.first);
            pop(lb, ub, team_index);
        }

        amount--;
    }

    for (auto [a, b] : finalpos)
    {
        ans[b] = 0;
    }

    rep(i, n)
    {
        cout << ans[i] << ' ';
    }
    cout << '\n';


    return 0;
}
