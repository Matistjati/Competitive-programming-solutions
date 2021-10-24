#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_set>
#include <string>
#include <iterator>
#include <queue>
#include <tuple>
#include <numeric>
#include <random>
#include <time.h>
#include <stack>
#include <chrono>
#include <unordered_map>
#include <iomanip>

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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}


int main()
{
    fast();

    int n;
    read(n);
    vector<p2> rows;
    rep(i,n)
    {
        ll left;
        ll right;
        read(left);
        read(right);
        rows.push_back({ left,right });
    }

    reverse(all(rows));

    double power = 1;
    double value = 0;
    double maxValue = 0;
    rep(i, rows.size())
    {
        rep(j, rows[i].first)
        {
            value += power;
        }
        power *= (rows[i].first + rows[i].second+1);


    }

    double additionV;
    read(additionV);
    value = fmod(value + additionV, power);


    reverse(all(rows));

    vector<p2> out;
    rep(i, rows.size())
    {
        power /= (rows[i].first + rows[i].second + 1);
        p2 r = { 0,0 };
        rep(j, rows[i].first+rows[i].second)
        {
            if (value - power >= 0)
            {
                value -= power;
                r.first++;
            }
            else
            {
                break;
            }
        }

        r.second = (rows[i].first + rows[i].second) - r.first;
        out.push_back(r);
    }



    repe(row, out)
    {
        cout << row.first << " " << row.second << "\n";
    }


    return 0;
}