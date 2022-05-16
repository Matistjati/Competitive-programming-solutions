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

    int score = 0;
    for(int i = 1; i < n + 1; i++)
    {
        int shot;
        read(shot);
        if (shot > 7)
        {
            shot = 7;
        }
        if (i%2==0)
        {
            score += (shot - 3);
        }
        else
        {
            score += (shot - 2);
        }
    }

    write(score);



    return 0;
}