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


ll solvesmart(vector<tuple<int,int,int>>& people) {
    ll n = people.size();

    vi dp(n * 2 + 20, -inf);
    dp[n + 5] = 0LL;

    rep(i, n)
    {
        ll a, b, c;
        tie(a, b, c) = people[i];

        vi newdp(dp.size(), -inf);

        deque<p2> q;
        ll sub = 0;
        auto add = [&](p2 v)
        {
            while (q.size() && q.back().second - sub < v.second - sub)
            {
                q.pop_back();
            }
            q.emplace_back(v);
        };
        rep(j, c)
        {
            ll score = a * (j + 1);
            add(p2(j, score + dp[j]));
        }

        rep(k, dp.size())
        {
            while (q.size() && q.front().first < k) q.pop_front();
            ll best = newdp[k];
            best = q.front().second - sub;
            sub += a;
            if (k + c < dp.size()) add(p2(k + c, dp[k + c] + a * c + sub));

            newdp[k] = best + b;
        }

        repp(j, 1, dp.size())
        {
            ll old = dp[j - 1];
            newdp[j] = max(newdp[j], old);
        }

        swap(dp, newdp);
    }
    return dp[n + 5];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    vector<tuple<int,int,int>> people(n);
    rep(i, n) {
        int a, b, c;
        cin >> a >> b >> c;
        people[i] = { a,b,c };
    }
    cout << solvesmart(people) << '\n';

    return 0;
}
