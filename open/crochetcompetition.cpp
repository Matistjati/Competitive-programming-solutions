#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
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

    map<string, int> t;
    t["Mon"] = 1440 * 0;
    t["Tue"] = 1440 * 1;
    t["Wed"] = 1440 * 2;
    t["Thu"] = 1440 * 3;
    t["Fri"] = 1440 * 4;
    t["Sat"] = 1440 * 5;
    t["Sun"] = 1440 * 6;

    auto get = [&]()
        {
            string day;
            cin >> day;
            int ret = t[day];
            string b;
            cin >> b;
            ret += 60 * stoi(b.substr(0, 2));
            ret += stoi(b.substr(3, 2));
            return ret;
        };

    int a = get();
    int b = get();

    int dist;
    if (a<b)
    {
        dist = b - a;
    }
    else
    {
        dist = -a + 1440 * 7 + b;
    }
    
    string ans;
    if (dist>= 1440)
    {
        int days = dist / 1440;
        ans += to_string(days);
        if (days == 1) ans += " day, ";
        else ans += " days, ";
        dist %= 1440;
    }
    if (dist>= 60)
    {
        int hours = dist / 60;
        ans += to_string(hours);
        if (hours == 1) ans += " hour, ";
        else ans += " hours, ";
        dist %= 60;
    }
    if (dist)
    {
        int minutes = dist;
        ans += to_string(minutes);
        if (minutes == 1) ans += " minute, ";
        else ans += " minutes, ";
    }

    while (ans.back()==' ' || ans.back()==',')
    {
        ans.pop_back();
    }
    if (count(all(ans),',')==1)
    {
        auto it = find(all(ans), ',');
        it = ans.erase(it);
        int ind = it - begin(ans);
        ans.insert(begin(ans) + ind, 'd');
        ans.insert(begin(ans) + ind, 'n');
        ans.insert(begin(ans) + ind, 'a');
        ans.insert(begin(ans) + ind, ' ');
    }

    cout << ans << '\n';

    return 0;
}
