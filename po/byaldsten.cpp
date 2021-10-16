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

int main()
{
    fast();

    int n;
    read(n);

    vector<p3> people;
    rep(i, n)
    {
        int born;
        int death;
        read(born);
        read(death);
        people.push_back({ born,death, i });
    }

    sort(all(people));
    vector<int> n_speeches(n);


    p3 prevOldest = {0,0,-1};
    ll currOldest = 0;
    rep(i, n)
    {
        p3 newPerson = people[i];
        currOldest = max(currOldest, newPerson[1]);
        if (newPerson[1] > prevOldest[1])
        {
            n_speeches[newPerson[2]] += min(newPerson[1] - prevOldest[1], newPerson[1] - newPerson[0]);
            prevOldest = newPerson;
        }


    }

    rep(i, n)
    {
        write(n_speeches[i]);
    }

    return 0;
}