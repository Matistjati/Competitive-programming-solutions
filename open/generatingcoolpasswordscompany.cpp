using namespace std;
#include <bits/stdc++.h>
using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;

#define rep(i,n) for (int i = 0; i < (n); i++)
#define repe(i,a) for (auto& i : a)
#define all(x) begin(x),end(x)
#define sz(x) ((int)x.size())

int main()
{
    int n;
    cin >> n;
    int len = 12;
    uniform_int_distribution<int> dist(33, 126);
    mt19937 rng(42);

    vector<string> pwd;
    auto good = [&pwd, len](string& si)
    {
        repe(s,pwd)
        {
            int diffs = 0;
            rep(i,len)
            {
                diffs += s[i]!=si[i];
            }
            if (diffs<2) return false;
        }

        return true;
    };
    auto upper = [](string s)
    {
        bool any =0;
        repe(c,s)
        {
            any |= (c>='A'&&c<='Z');
        }
        return any;
    };
    auto lower = [](string s)
    {
        bool any =0;
        repe(c,s)
        {
            any |= (c>='a'&&c<='z');
        }
        return any;
    };
    auto digit = [](string s)
    {
        bool any =0;
        repe(c,s)
        {
            any |= (c>='0'&&c<='9');
        }
        return any;
    };
    auto special = [](string s)
    {
        bool any =0;
        repe(c,s)
        {
            any |= !(c>='0'&&c<='9') && !(c>='a'&&c<='z') && !(c>='A'&&c<='Z');
        }
        return any;
    };
    while (sz(pwd) < n)
    {
        string s;
        rep(i,len) s.push_back(char(dist(rng)));
        if (!digit(s)) continue;
        if (!upper(s)) continue;
        if (!lower(s)) continue;
        if (!special(s)) continue;
        if (good(s)) pwd.push_back(s);
    }
    repe(s,pwd){
        cout << s << '\n';
    }


    return 0;
}

