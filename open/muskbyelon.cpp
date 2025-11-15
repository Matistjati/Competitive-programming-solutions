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

    auto parse_time = [&](string s)
    {
        return 60 * stoi(s.substr(0, 2)) + stoi(s.substr(3, 2));
    };

    int t;
    cin >> t;
    int day = 1;
    while (t--)
    {
        int n;
        cin >> n;
        vector<p2> intervals(n);
        rep(i, n)
        {
            string x;
            cin >> x;
            intervals[i].first = parse_time(x);
            cin >> x;
            intervals[i].second = parse_time(x);
            getline(cin, x);
        }

        auto inside_any = [&](int t)
        {
            for (auto [a, b] : intervals)
            {
                if (t >= a && t <= b) return true;
            }
            return false;
        };
        auto to_date = [&](int x)
        {
            string ret = to_string(x / 60);
            while (sz(ret) < 2) ret = "0" + ret;
            ret += ":";
            string mins = to_string(x % 60);
            while (sz(mins) < 2) mins = "0" + mins;
            return ret + mins;
        };

        p2 best = p2(-1, -1);
        int start = 60 * 10-1;
        int curr_time = 0;
        repp(tim, 60 * 10, 60 * 19)
        {
            if (inside_any(tim))
            {
                curr_time = 0;
                start = tim;
            }
            else
            {
                curr_time++;
                best = max(best, p2(curr_time, -(start+1)));
            }
        }

        int dur = best.first;

        cout << "Day #" << day << ": Elon Musk will make Musk by Elon from " << to_date(-best.second) << " for " << dur / 60 << " hours and " << dur % 60 << " minutes\n";
        day++;
    }


    return 0;
}
