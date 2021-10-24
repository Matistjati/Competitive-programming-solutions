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



ll n_possible(vector<int>& memo, char c, int n, int personvagn, int postvagn, int godsvagn)
{
    int currentState = 0;
    int leftShift = 0;
    currentState += (c - 'a');
    leftShift += 6;
    currentState += n << leftShift;
    leftShift += 5;
    currentState += personvagn << leftShift;
    leftShift += 5;
    currentState += postvagn << leftShift;
    leftShift += 3;
    currentState += godsvagn << leftShift;
    if (memo[currentState])
    {
        return memo[currentState];
    }
    if (postvagn > 2)
    {
        return 0;
    }
    if (godsvagn > 3)
    {
        return 0;
    }
    if (n == 0)
    {
        return personvagn > 0 && c != 'r';
    }

    ll ret = 0;

    if (c == 'p')
    {
        ret += n_possible(memo, 'p', n - 1, personvagn, postvagn + 1, godsvagn);
        ret += n_possible(memo, 'b', n - 1, personvagn + 1, postvagn, godsvagn);
        ret += n_possible(memo, 'g', n - 1, personvagn, postvagn, godsvagn + 1);
    }
    else if (c == 'r')
    {
        ret += n_possible(memo, 'b', n - 1, personvagn + 1, postvagn, godsvagn);
    }
    else if (c == 'b')
    {
        ret += n_possible(memo, 'b', n - 1, personvagn + 1, postvagn, godsvagn);
        ret += n_possible(memo, 'g', n - 1, personvagn, postvagn, godsvagn + 1);
        ret += n_possible(memo, 'r', n - 1, personvagn, postvagn, godsvagn);
    }
    else if (c == 'g')
    {
        ret += n_possible(memo, 'g', n - 1, personvagn, postvagn, godsvagn + 1);
    }
    memo[currentState] = ret;

    return ret;
}

int main()
{
    fast();

    int n;
    read(n);

    vector<int> memo(2548576, 0);
    write(n_possible(memo,'p', n, 0, 0, 0));

    return 0;
}