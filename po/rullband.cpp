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

#define p2 pair<int, int>
#define ll long long
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

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
    int m;
    int speed;
    read(n);
    read(m);
    read(speed);

    vector<int> fastest(m+1, inf);
    map<int, set<p2>> belts;
    map<int, set<p2>> beltEnds;

    rep(i, n)
    {
        int start;
        int end;
        int duration;
        read(start);
        read(end);
        read(duration);

        if (!setcontains(belts,start))
        {
            belts[start] = set<p2>();
        }
        if (!setcontains(beltEnds, end))
        {
            beltEnds[end] = set<p2>();
        }

        belts[start].insert({ end,duration });
        beltEnds[end].insert({ start,duration });
    }

    fastest[0] = 0;
    for (int i = 1; i < m+1; i++)
    {
        if (fastest[i-1]+speed < fastest[i])
        {
            fastest[i] = fastest[i - 1] + speed;
        }

        int curr = fastest[i];
        if (setcontains(belts, i))
        {


            repe(belt, belts[i])
            {
                if (curr + belt.second < fastest[belt.first])
                {
                    fastest[belt.first] = curr + belt.second;
                }
            }
        }

        int j = i - 1;
        curr = fastest[i];
        while ((i-j)*speed+curr<fastest[j])
        {
            if (setcontains(belts, j))
            {
                repe(belt, belts[j])
                {
                    if ((i-j)*speed+curr+belt.second<fastest[belt.first])
                    {
                        fastest[belt.first] = (i - j) * speed + curr + belt.second;
                    }
                }
            }

            j--;
            if (j < 0)
            {
                break;
            }
        }

    }

    write(fastest[fastest.size() - 1]);

    return 0;
}