#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define deb __debugbreak();

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)


inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

ll most_boris(map<int,ll>& memo, vector<p4>& trains, ll& maxTime, p2 pos, int time, int prev, ll sum)
{
    int state = prev;
    if (setcontains(memo,state) && prev != -1)
    {
        return sum + memo[state];
    }
    if (time > maxTime || prev == trains.size())
    {
        return sum;
    }

    ll ret = sum;

    for(int i = 0; i < trains.size(); i++)
    {
        p4 train = trains[i];
        if (time > train[0] || prev == i)
        {
            continue;
        }
        
        if (abs(train[2]-pos.first) + abs(train[3]-pos.second) + time <= train[0])
        {
            int s = (i + 1 == trains.size()) ? 1 : 0;
            ret = max(ret, most_boris(memo, trains, maxTime, { train[2],train[3] }, train[0], i, sum + train[1]));
        }
    }

    memo[state] = ret - sum;

    return ret;
}

int main()
{
    fast();

    ll n;
    read(n);

    vector<p4> trains;
    ll maxTime = -inf;

    rep(i, n)
    {
        ll leaveTime;
        ll n_boris;
        ll x;
        ll y;
        read(leaveTime);
        read(n_boris);
        read(x);
        read(y);
        maxTime = max(maxTime, leaveTime);
        trains.push_back({ leaveTime,n_boris,x,y });
    }

    ll ans = -linf;

    sort(all(trains));

    map<int, ll> memo;
    rep(i, trains.size())
    {
        ans = max(ans, most_boris(memo, trains, maxTime, {trains[i][2],trains[i][3]}, 0, -1, 0));
    }

    write(ans);

    return 0;
}