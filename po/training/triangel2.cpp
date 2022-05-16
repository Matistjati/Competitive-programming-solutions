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


using namespace std;

#define ll long long
#define p2 pair<ll, ll>
#define p3 tuple<ll, ll, ll>
#define vi vector<ll>
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

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

    ll q;
    read(q);

    ll n = 0;
    vector<ll> trongles;
    vector<ll> nums;
    for (int i = 0; i < inf; i++)
    {
        n += i;
        trongles.push_back(n);
        nums.push_back(i);
        if (n >= inf)
        {
            break;
        }
    }

    vector<ll> prefix;
    ll cum = 0;
    repe(trong, trongles)
    {
        cum += trong;
        prefix.push_back(cum);
    }

    rep(i, prefix.size())
    {
        ll v;
        if (q < prefix[i])
        {
            v = -( q - prefix[i]);
        }
        else
        {
            v = (q - prefix[i]);
        }

        auto it = lower_bound(all(prefix), v);
        if (it == prefix.end())
        {
            continue;
        }
        if (*it-prefix[i]==q)
        {

            cout << (nums[i+1]) << " ";
            write(nums[it - prefix.begin()]);
            return 0;
        }
        else if (prefix[i]-*it==q)
        {
            cout << (nums[it - prefix.begin()] + 1) << " ";
            write(nums[i]);
            return 0;
        }
    }
    write("NEJ");


    return 0;
}