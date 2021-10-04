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
#define repp(i, high) for (ll i = high; i >= 0; i--)
#define inf 1e9

void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

bool randomBool() {
    return rand() > (RAND_MAX / 2);
}

int main()
{
    fast();

    int n;
    read(n);
    int aTot = 0;
    int bTot = 0;

    string game;
    read(game);

    int a = 0;
    int b = 0;
    bool third = false;
    rep(i, game.size())
    {
        if (game[i] == 'A')
        {
            a++;
        }
        else if (game[i] == 'B')
        {
            b++;
        }
        if (third)
        {
            if (a >= 15 && a - b >= 2)
            {
                aTot++;
                break;
            }
            else if (b >= 15 && b - a >= 2 )
            {
                bTot++;
                break;
            }
        }
        else
        {
            if (a >= 25 && a - b >= 2)
            {
                aTot++;
                if (aTot == 1 && bTot == 1)
                {
                    third = true;
                }
                else if (aTot > 1)
                {
                    break;
                }

                a = 0;
                b = 0;
            }
            if (b >= 25 && b - a >= 2)
            {
                bTot++;
                if (aTot == 1 && bTot == 1)
                {
                    third = true;
                }
                else if (bTot > 1)
                {
                    break;
                }

                a = 0;
                b = 0;
            }
        }
    }

    cout << aTot << " " << bTot;

    return 0;
}