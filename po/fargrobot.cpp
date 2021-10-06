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

    int n;
    read(n);
    string colors;
    read(colors);
    string ans = "";


    int index = 0;
    while (ans.size() < n)
    {
        int r = 0;
        int g = 0;
        int b = 0;
        int n_colored = 0;
        char chosen = 'S';
        for (int i = index; i < colors.size(); i++)
        {
            if (colors[i] == 'R')
            {
                if (r == 0)
                {
                    n_colored++;
                    if (n_colored > 2)
                    {
                        chosen = 'R';
                    }
                    r++;
                }
                else
                {
                    r++;
                }
            }
            if (colors[i] == 'G')
            {
                if (g == 0)
                {
                    n_colored++;
                    if (n_colored > 2)
                    {
                        chosen = 'G';
                    }
                    g++;
                }
                else
                {
                    g++;
                }
            }
            if (colors[i] == 'B')
            {
                if (b == 0)
                {
                    n_colored++;
                    if (n_colored > 2)
                    {
                        chosen = 'B';
                    }
                }
                b++;


            }
            if (chosen != 'S')
            {
                ans += chosen;
                index = i+1;
                break;
            }
        }
    }

    write(ans);

    return 0;
}