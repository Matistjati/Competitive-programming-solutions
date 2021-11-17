#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define dread(type, a) type a; cin >> a
#define write(a) cout << (a) << endl
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))


inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

bool possible(vp2& intervals, ll n, ll k, ll d)
{
    ll pos = 0;
    ll n_students = 0;


    repe(interval, intervals)
    {
        if (pos > interval.second)
        {
            continue;
        }
        if (pos >= interval.first)
        {
            pos = interval.second + 1;
        }
        else
        {
            ll dx = (interval.first - pos - 1) / d+1;
            n_students += dx;
            pos += dx*d;
            if (pos <= interval.second)
            {
                pos = interval.second + 1;
            }
        }
    }

    if (pos < k)
    {
        n_students += (k - pos - 1) / d + 1;
    }

    return n_students >= n;
}

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread(ll, n);
    dread(ll, m);
    dread(ll, k);

    vp2 intervalsTemp(m);
    rep(i, m)
    {
        dread(ll, start);
        dread(ll, end);
        intervalsTemp[i] = {start,end};
    }
    sort(all(intervalsTemp));


    vp2 intervals;
    if (intervalsTemp.size())
    {
        p2 curr = intervalsTemp[0];
        for (int i = 1; i < intervalsTemp.size(); i++)
        {
            p2 interval = intervalsTemp[i];
            if (curr.second + 1 >= interval.first)
            {
                curr.second = interval.second;
            }
            else
            {
                intervals.push_back(curr);
                curr = interval;
            }
        }
        intervals.push_back(curr);
    }


    ll high = k/(n-1)+1;
    ll low = 0;
    while (true)
    {
        ll mid = (high + low) / 2;

        bool p = possible(intervals, n, k, mid);
        if (p)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }

        if (low+1 == high)
        {
            write(low);
            return 0;
        }
    }

    return 0;
}