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
    cin.tie(NULL); cout.tie(NULL);
}


int main()
{
    fast();

    int n;
    read(n);

    map<int, int> numbers;
    rep(i, n)
    {
        int temp;
        read(temp);
        numbers[temp] = 0;
    }

    for(int i = 1; i < 1e6; i++)
    {
        string s = to_string(i);


        map<int,int> ok(all(numbers));

        do
        {
            if (s[0] == '0')
            {
                continue;
            }
            int q = stoi(s);

            bool likes = false;
            set<int> rem;
            repe(f, ok)
            {
                if (q % f.first == 0)
                {
                    ok[f.first]++;
                }
            }

        } while (next_permutation(all(s)));

        bool yes = true;
        repe(f, ok)
        {
            if (f.second < 1)
            {
                yes = false;
                break;
            }
        }
        if (yes)
        {
            write(i);
            break;
        }

        endofloop:;
    }


    return 0;
}