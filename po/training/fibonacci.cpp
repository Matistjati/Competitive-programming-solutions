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

    int q;
    read(q);

    ll a = 0;
    ll b = 1;

    vi fib;

    while (a+b<inf)
    {
        fib.push_back(a + b);
        int temp = b;
        b = a + b;
        a = temp;
    }

    int n = 0;
    int fibIndex = fib.size() - 1;
    vi ans;
    while (q > 0)
    {
        if (q-fib[fibIndex]>=0)
        {
            n++;
            q -= fib[fibIndex];
            ans.push_back(fib[fibIndex]);
        }
        else
        {
            fibIndex--;
        }

    }

    write(n);
    rep(i, n)
    {
        write(ans[i]);
    }

    return 0;
}