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

#define p2 pair<int, int>
#define ll long long
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

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
    vector<int> left;
    vector<bool> leftTaken;
    vector<int> right;
    vector<bool> rightTaken;
    read(n);

    rep(i, n)
    {
        readpush(int, left);
        if (temp == 1)
        {
            leftTaken.push_back(true);
        }
        else
        {
            leftTaken.push_back(false);
        }
    }

    rep(i, n)
    {
        readpush(int, right);
        if (temp == 1)
        {
            rightTaken.push_back(true);
        }
        else
        {
            rightTaken.push_back(false);
        }
    }

    int minA = n * n;

    rep(i, n)
    {
        if (!leftTaken[i])
        {
            leftTaken[i] = true;
            minA += left[i]-1;

            rep(j, n)
            {
                if (!rightTaken[j] && right[j] == left[i])
                {
                    rightTaken[j] = true;
                    break;
                }
            }

        }
    }

    rep(i, n)
    {
        if (!rightTaken[i])
        {
            rightTaken[i] = true;
            minA += right[i]-1;

            rep(j, n)
            {
                if (!leftTaken[j] && left[j] == right[i])
                {
                    leftTaken[j] = true;
                    break;
                }
            }

        }
    }


    int maxA = 0;

    rep(i, n)
    {
        rep(j, n)
        {
            maxA += min(left[i],right[j]);
        }
    }

    cout << minA << " " << maxA;

    return 0;
}