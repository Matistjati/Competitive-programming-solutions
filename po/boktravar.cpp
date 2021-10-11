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
#define p2 pair<ll, ll>
#define p3 tuple<ll, ll, ll>
#define vi vector<ll>
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

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

    map<vector<int>, int> days;

    int n;
    read(n);
    vector<int> books;
    rep(i, n)
    {
        readpush(int, books);
    }

    int day = 1;
    while (true)
    {
        if (!setcontains(days,books))
        {
            days[books] = day;
        }
        else
        {
            cout << days[books] << " " << day;
            return 0;
        }

        int s = 0;
        rep(i, books.size())
        {
            books[i]--;
            s++;
            if (books[i] == 0)
            {
                books.erase(next(books.begin(), i));
                i--;
            }
        }
        books.push_back(s);
        day++;
    }


    return 0;
}