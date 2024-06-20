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

    int a;
    int b;
    int c;
    int n;
    read(a);
    read(b);
    read(c);
    read(n);

    int ha = n / a+1;
    int hb = n / b+1;
    int k = 0;
    for (int i = 0; i < ha; i++)
    {
        for (int j = 0; j < hb; j++)
        {
            if (i*a+j*b>n)
            {
                break;
            }

            if ((n-i*a-j*b)%c==0)
            {
                k++;
                cout << i << " " << j << " " << ((n - i * a - j * b) / c) << "\n";
            }
        }
    }

    if (k==0)
    {
        write("impossible");
    }

    return 0;
}

