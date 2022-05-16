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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

int main()
{
    fast();

    int n;
    read(n);
    double small;
    double medium;
    double large;
    read(small);
    read(medium);
    read(large);

    vector<int> workers(n, 0);
    int day = 0;
    while (small > 0 || medium > 0 || large > 0)
    {
        int available = 0;
        repe(worker, workers)
        {
            if (worker <= day)
            {
                available++;
            }
        }

        while (available > 2 && large > 0)
        {
            int i = 0;
            repe(worker, workers)
            {
                if (worker <= day)
                {
                    available--;
                    worker = day + 3;
                    i++;
                    if (i == 3)
                    {
                        large--;
                        break;
                    }
                }
            }
        }

        while (available > 1 && medium > 0)
        {
            int i = 0;
            repe(worker, workers)
            {
                if (worker <= day)
                {
                    available--;
                    worker = day + 2;
                    i++;
                    if (i == 2)
                    {
                        medium--;
                        break;
                    }
                }
            }
        }

        while (available > 0 && small > 0)
        {
            int i = 0;
            repe(worker, workers)
            {
                if (worker <= day)
                {
                    available--;
                    worker = day + 1;
                    i++;
                    if (i == 1)
                    {
                        small--;
                        break;
                    }
                }
            }
        }

        day++;
    }

    write(*max_element(all(workers)));

    return 0;
}