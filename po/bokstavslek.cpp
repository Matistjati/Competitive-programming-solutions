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

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
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

    string word;
    int n;
    read(word);
    read(n);

    int start = -1;
    rep(i, word.size())
    {
        if (word[i] != *min_element(next(begin(word),i), end(word)))
        {
            start = i;
            break;
        }
    }

    while (true)
    {
        if (start == word.size())
        {
            break;
        }
        auto smol = min_element(next(begin(word), start), end(word));
        int l = smol - next(begin(word), start);
        if (n < l)
        {
            break;
        }
        n -= l;
        char c = *smol;
        word.erase(smol);
        word.insert(next(begin(word), start), c);

        start++;

    }


    queue<pair<string, int>> toDo;
    toDo.push({ word,0 });
    set<string> seen;
    seen.insert(word);

    while (toDo.size())
    {
        pair<string, int> curr = toDo.front();
        toDo.pop();
        if (curr.second >= n)
        {
            continue;
        }

        rep(i, curr.first.size() - 1)
        {
            if (curr.first[i] > curr.first[i + 1])
            {
                string s(curr.first);
                swap(s[i], s[i + 1]);
                if (!setcontains(seen, s))
                {
                    seen.insert(s);
                    toDo.push({ s,curr.second + 1 });
                }
            }
        }
    }


    write(*begin(seen));


    return 0;
}
