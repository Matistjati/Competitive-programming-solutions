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

#define ISOPEN 1
#define ISCLOSED 2
#define THINKCLOSED 3 
#define THINKOPEN 4

#if 1
bool query(ll a, ll b)
{
    a++; b++;
    cout << "? " << a << " " << b << endl;
    ll ans;
    cin >> ans;
    return ans;
}
#else
string hidden;
bool query(ll a, ll b)
{
    a--; b--;
    assert(a >= 0 && a < hidden.size());
}
#endif

string solve(ll n, ll q)
{

    vi ans(n);
    ans[0] = THINKOPEN;

    stack<ll> leftpar;
    leftpar.push(0);
    ll r = 1;
    rep(i, n - 1)
    {
        if (r >= n)
        {
            break;
        }
        bool v = query(leftpar.top(), r);
        if (v)
        {
            ans[r] = ISCLOSED;
            ans[leftpar.top()] = ISOPEN;
            leftpar.pop();
            if (r + 1 >= n)
            {
                break;
            }
            if (leftpar.empty())
            {
                ans[r + 1] = THINKOPEN;
                leftpar.push(r + 1);
                r += 2;
            }
            else
            {
                r++;
            }
        }
        else
        {
            ans[r] = THINKOPEN;
            leftpar.push(r);
            r++;
        }
    }

    ll numthinks = 0;

    rep(i, n)
    {
        if (ans[i] == THINKCLOSED || ans[i] == THINKOPEN)
        {
            numthinks++;
        }
    }

    ll placed = 0;
    rep(i, n)
    {
        if (ans[i] == THINKCLOSED || ans[i] == THINKOPEN)
        {
            if (placed < numthinks / 2) ans[i] = ISCLOSED;
            else ans[i] = ISOPEN;

            placed++;
        }
    }

    string ret = "! ";
    rep(i, n) ret += (ans[i] == ISOPEN ? '(' : ')');
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, q;
    cin >> n >> q;

    cout << solve(n, q);

    return 0;
}
