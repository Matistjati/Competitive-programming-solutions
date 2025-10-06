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

struct Square
{
    p2 tl;
    p2 br;

    Square intersect(const Square& other)
    {
        Square ret = *this;
        ret.tl = p2(max(tl.first, other.tl.first), min(tl.second, other.tl.second));
        ret.br = p2(min(br.first, other.br.first), max(br.second, other.br.second));
        return ret;
    }

    bool isempty()
    {
        ll x_area = br.first - tl.first;
        ll y_area = tl.second - br.second;
        return x_area < 0 || y_area < 0;
    }
};

template<class F>
ll ternSearch(ll a, ll b, F f) {
    assert(a <= b);
    while (b - a >= 5) {
        ll mid = (a + b) / 2;
        if (f(mid) < f(mid + 1)) a = mid; // (A)
        else b = mid + 1;
    }
    repp(i, a + 1, b + 1) if (f(a) < f(i)) a = i; // (B)
    return a;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    vector<p2> pts(n);
    repe(p, pts) cin >> p.first >> p.second;
    vector<p2> untransformed = pts;
    auto transform = [&](p2 x)
    {
        return p2(x.first + x.second,x.first - x.second);
    };
    repe(p, pts) p = transform(p);
    ll d;
    cin >> d;

    Square start = { p2(-2e9, 2e9),p2(2e9,-2e9) };

    repe(p, pts)
    {
        Square myvalid = { p2(p.first - d, p.second + d), p2(p.first+d,p.second-d) };
        start = start.intersect(myvalid);
    }
    if (start.isempty())
    {
        cout << "impossible\n";
        return 0;
    }

    auto eval = [&](ll x, ll y)
    {
        ll ret = 0;
        for (auto [a, b] : pts)
        {
            ret += max(abs(x - a), abs(b - y));
        }
        return -ret;
    };
    
    auto search_y = [&](ll x)
    {
        return ternSearch(start.br.second, start.tl.second, [&](ll y)
        {
            return eval(x, y);
        });
    };

    auto search_x = [&]()
    {
        ll bestx = ternSearch(start.tl.first, start.br.first, [&](ll x)
        {
            return eval(x, search_y(x));
        });
        ll besty = search_y(bestx);
        ll ret = inf;

        repp(dx, -2, 3)
        {
            repp(dy, -2, 3)
            {
                p2 np = { bestx + dx,besty + dy };
                if (((np.first + np.second) % 2 + 2) % 2 == 1) continue;
                if (np.first<start.tl.first||np.first>start.br.first||np.second<start.br.second||np.second>start.tl.second)
                {
                    continue;
                }
                ret = min(ret, -eval(np.first, np.second));
            }
        }
        return ret;
    };

    cout << search_x() << '\n';

    return 0;
}
