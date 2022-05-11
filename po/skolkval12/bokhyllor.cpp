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

    int small;
    int medium;
    int large;
    read(small);
    read(medium);
    read(large);

    int bookShelf;
    read(bookShelf);

    int capacity = bookShelf;
    int n_shelves = 1;
    while (large > 0)
    {
        if (capacity - 3 >= 0 && large > 0)
        {
            capacity -= 3;
            large--;
        }
        else if (capacity - 2 >= 0 && medium > 0)
        {
            capacity -= 2;
            medium--;
        }
        else if (capacity - 1 >= 0 && small > 0)
        {
            capacity--;
            small--;
        }
        else
        {
            if (large == 0)
            {
                break;
            }
            n_shelves++;
            capacity = bookShelf;
        }



    }

    while (medium > 0)
    {
        if (capacity == 0)
        {
            n_shelves++;
            capacity = bookShelf;
        }

        if (capacity - 2 >= 0 && medium > 0)
        {
            capacity -= 2;
            medium--;
        }
        else if (capacity - 1 >= 0 && small > 0)
        {
            capacity--;
            small--;
        }
        else
        {
            if (medium == 0)
            {
                break;
            }
            n_shelves++;
            capacity = bookShelf;
        }



    }

    while (small > 0)
    {

        if (capacity - 1 >= 0)
        {
            capacity--;
            small--;
        }
        else
        {
            if (small == 0)
            {
                break;
            }
            n_shelves++;
            capacity = bookShelf;
        }



    }

    write(n_shelves);

    return 0;
}