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

using namespace std;

#define ll long long
#define p2 pair<ll, ll>
#define p3 vector<ll>
#define p4 vector<ll>
#define vi vector<ll>
#define inf 1e9

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

void replaceAll(string& s, const string& search, const string& replace) {
    for (size_t pos = 0; ; pos += replace.length()) {
        // Locate the substring to replace
        pos = s.find(search, pos);
        if (pos == string::npos) break;
        // Replace by erasing and inserting
        s.erase(pos, search.length());
        s.insert(pos, replace);
    }
}

void mult(string& goal, string start)
{
    vector<string> pref = { "A","B","C" };
    vector<char> value = { 'A','B','C','-' };

    vector<pair<string, string>> alternatives;
    repe(prefix, pref)
    {
        repe(first, value)
        {
            repe(second, value)
            {
                repe(third, value)
                {
                    string v = "";
                    if (first != '-')
                    {
                        v += first;
                    }
                    if (second != '-')
                    {
                        v += second;
                    }
                    if (third != '-')
                    {
                        v += third;
                    }

                    alternatives.push_back({ prefix, v });
                }
            }
        }
    }

    repe(a, alternatives)
    {
        string copy(start);
        replaceAll(copy, a.first, a.second);
        if (copy == goal)
        {
            cout << a.first << " " << a.second << "\n";
            return;
        }
    }

    repe(a, alternatives)
    {
        repe(b, alternatives)
        {
            string copy(start);
            replaceAll(copy, a.first, a.second);
            replaceAll(copy, b.first, b.second);
            if (copy == goal)
            {
                cout << a.first << " " << a.second << "\n";
                cout << b.first << " " << b.second << "\n";
                return;
            }
        }
    }

    repe(a, alternatives)
    {
        repe(b, alternatives)
        {
            repe(c, alternatives)
            {
                string copy(start);
                replaceAll(copy, a.first, a.second);
                replaceAll(copy, b.first, b.second);
                replaceAll(copy, c.first, c.second);
                if (copy == goal)
                {
                    cout << a.first << " " << a.second << "\n";
                    cout << b.first << " " << b.second << "\n";
                    cout << c.first << " " << c.second << "\n";
                    return;
                }
            }
        }
    }
}


int main()
{
    fast();

    string start;
    string goal;
    read(goal);
    read(start);

    mult(start, goal);

    return 0;
}