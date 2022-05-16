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

    int a_req;
    int c_req;
    int e_req;
    int a_val;
    int c_val;
    int e_val;
    read(a_req);
    read(c_req);
    read(e_req);
    read(a_val);
    read(c_val);
    read(e_val);

    string grade = "";
    bool e = false;
    bool c = false;
    if (e_val == e_req)
    {
        grade= ("E");
        e = true;
    }

    if (c_val >= ceildiv(c_req, 2) && e)
    {
        grade = ("D");
    }
    if (c_val == c_req && e)
    {
        grade = ("C");
        c = true;
    }

    if (a_val >= ceildiv(a_req, 2) && c)
    {
        grade = ("B");
    }

    if (a_val == a_req && c)
    {
        grade = ("A");
    }
    write(grade);


    return 0;
}