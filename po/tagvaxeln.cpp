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
#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)
#define inf 1e9
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

    int a;
    read(a);
    int b;
    read(b);

    bool openA = true;
    int ans = 0;
    if (a > b)
    {
        swap(a, b);
    }

    int aV = a;
    int bV = b;

    rep(i, 1440)
    {
        if (i == aV && aV == bV)
        {
            ans++;
            openA = !openA;
            aV += a;
            bV += b;
        }
        else if (i == aV)
        {
            if (!openA)
            {
                openA = true;
                ans++;
            }
            aV += a;
        }
        else if (i == bV)
        {
            if (openA)
            {
                openA = false;
                ans++;
            }
            bV += b;
        }
    }

    write(ans);

    return 0;
}