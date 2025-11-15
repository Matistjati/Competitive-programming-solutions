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

    int m;
    cin >> m;
    string name;
    cin >> name;

    auto split_name = [&](string& in)
    {
        vector<string> ret;
        string s;
        repe(c, in)
        {
            if (c=='-')
            {
                assert(sz(s));
                ret.push_back(s);
                s = "";
            }
            else
            {
                s += c;
            }
        }
        assert(sz(s));
        ret.push_back(s);
        return ret;
    };
    vector<string> ans = split_name(name);

    auto merge = [&](vector<string>& a, const vector<string>& b, int limit)
    {
        a.insert(end(a), all(b));
        int tot_size = 0;
        for (auto s : a) tot_size += sz(s);

        while (tot_size>limit)
        {
            p2 best = p2(-1, inf);
            rep(i,sz(a))
            {
                best = max(best, p2(sz(a[i]), -i));
            }
            assert(best.second != inf);
            if (best.first == 1) return;
            a[-best.second].pop_back();
            tot_size--;
        }
    };

    rep(i, m)
    {
        int limit,n;
        cin >> limit >> n;
        rep(j, n)
        {
            string name;
            cin >> name;
            merge(ans, split_name(name), limit);
        }
    }
    cout << ans[0];
    repp(i, 1, sz(ans))
    {
        cout << "-" << ans[i];
    }
    cout << '\n';


    return 0;
}
