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

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define repp(i, high) for (ll i = high; i >= 0; i--)
#define inf 1e9

void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}



int main()
{
    fast();

    int n;
    read(n);

    set<set<int>> trongles;
    for (int b = 1; b <= n; b++)
    {
        for (int a = 1; a <= n; a++)
        {
            float c = sqrt(a * a + b * b - a * b);
            if (c-floor(c) == 0)
            {
                set<int> triangle({ a,b,int(c) });
                trongles.insert(triangle);
            }

        }
    }
    write(trongles.size());

    return 0;
}