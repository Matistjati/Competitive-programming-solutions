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

    int _;
    cin >> _;
    string x;
    cin >> x;
    
    stack<char> seen;
    set<char> isopen = { '{','(','[' };
    map<char, char> rev;
    rev['}'] = '{';
    rev[']'] = '[';
    rev[')'] = '(';
    repe(c, x)
    {
        bool opener = isopen.count(c);
        if (opener)
        {
            seen.push(c);
        }
        else
        {
            if (sz(seen) == 0 || seen.top() != rev[c])
            {
                cout << "Invalid";
                return 0;
            }
            seen.pop();
        }
    }
    if (sz(seen))
    {
        cout << "Invalid";
        return 0;
    }

    cout << "Valid";

    return 0;
}
