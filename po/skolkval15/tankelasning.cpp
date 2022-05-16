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
#define fract(a) (a-floor(a))

inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}


float evaluate(vector<pair<char, char>>& operations, float in)
{
    float orig = in;

    repe(operation, operations)
    {
        char op = operation.first;
        char v = operation.second;

        float operand;
        if (v == 'x')
        {
            operand = orig;
        }
        else
        {
            operand = v - '0';
        }

        switch (op)
        {
        case '-':
            in -= operand;
            break;
        case '*':
            in *= operand;
            break;
        case '/':
            in /= operand;
            break;
        case '+':
            in += operand;
            break;
        default:
            break;
        }
    }

    return in;
}

int main()
{
    fast();

    int n;
    read(n);

    bool works = true;
    vector<pair<char, char>> operations;
    rep(i, n)
    {
        string op;
        string v;
        read(op);
        read(v);
        operations.push_back({ op[0],v[0] });
    }

    float c = evaluate(operations, 0);

    for (float i = -100; i < 100; i++)
    {
        float s = evaluate(operations, i);


        if (s != c)
        {
            works = false;
            break;
        }
    }

    if (!works || fract(c) != 0)
    {
        write("Nej");
    }
    else
    {
        write(int(c));
    }


    return 0;
}
