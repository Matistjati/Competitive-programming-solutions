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
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
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

    string a;
    string b;
    read(a);
    read(b);
    string oa = a;
    set<char> consonants = { 'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z' };

    repe(c, consonants)
    {
        int na = count(all(a), c);
        int nb = count(all(b), c);
        if (nb > na * 2)
        {
            write("nej");
            return 0;
        }
    }

    set<string> s;


    rep(i, b.size())
    {
        if (i >= a.size())
        {

            if (i-2>0&& b[i] == a[i - 2] && setcontains(consonants, a[i-2]))
            {
                a += string(1, b[i]) + "o";
            }
            else if (i+1<b.size() && b[i+1]==a[i-1] && setcontains(consonants,a[i-1]))
            {
                a += "o" + string(1, a[i - 1]);
            }
            else
            {
                break;
            }

        }
        else if (a[i] != b[i])
        {
            if (a[i-1]==b[i-1]&&setcontains(consonants,a[i-1]))
            {
                a.insert(next(begin(a), i), 'o');
                a.insert(next(begin(a), i+1), a[i-1]);
            }
            else if (a[i - 2] == b[i - 2] && setcontains(consonants, a[i - 2]))
            {
                a.insert(next(begin(a), i-1), 'o');
                a.insert(next(begin(a), i), a[i - 2]);
            }
            else
            {
                break;
            }
        }
    }



    write(a==b ? "ja" : "nej");

    return 0;
}