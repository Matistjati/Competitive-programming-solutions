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

    int n;
    read(n);

    rep(i, n)
    {
        int day;
        read(day);
        string month;
        read(month);

        if (month == "Jan")
        {
            if (day <= 20)
            {
                write("Capricorn");
            }
            else
            {
                write("Aquarius");
            }
        }
        else if (month == "Feb")
        {
            if (day <= 19)
            {
                write("Aquarius");
            }
            else
            {
                write("Pisces");
            }
        }
        else if (month == "Mar")
        {
            if (day <= 20)
            {
                write("Pisces");
            }
            else
            {
                write("Aries");
            }
        }
        else if (month == "Apr")
        {
            if (day <= 20)
            {
                write("Aries");
            }
            else
            {
                write("Taurus");
            }
        }
        else if (month == "May")
        {
            if (day <= 20)
            {
                write("Taurus");
            }
            else
            {
                write("Gemini");
            }
        }
        else if (month == "Jun")
        {
            if (day <= 21)
            {
                write("Gemini");
            }
            else
            {
                write("Cancer");
            }
        }
        else if (month == "Jul")
        {
            if (day <= 22)
            {
                write("Cancer");
            }
            else
            {
                write("Leo");
            }
        }
        else if (month == "Aug")
        {
            if (day <= 22)
            {
                write("Leo");
            }
            else
            {
                write("Virgo");
            }
        }
        else if (month == "Sep")
        {
            if (day <= 21)
            {
                write("Virgo");
            }
            else
            {
                write("Libra");
            }
        }
        else if (month == "Oct")
        {
            if (day <= 22)
            {
                write("Libra");
            }
            else
            {
                write("Scorpio");
            }
        }
        else if (month == "Nov")
        {
            if (day <= 22)
            {
                write("Scorpio");
            }
            else
            {
                write("Sagittarius");
            }
        }
        else if (month == "Dec")
        {
            if (day <= 21)
            {
                write("Sagittarius");
            }
            else
            {
                write("Capricorn");
            }
        }
    }

    return 0;
}
