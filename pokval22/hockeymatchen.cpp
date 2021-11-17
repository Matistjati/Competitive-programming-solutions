#include <bits/stdc++.h>

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
    cin.tie(NULL); cout.tie(NULL);
}

int main()
{
    fast();

    int savesA;
    int goalsA;
    int shotsA;
    int savesB;
    int goalsB;
    int shotsB;
    read(savesA);
    read(goalsA);
    read(shotsA);
    read(savesB);
    read(goalsB);
    read(shotsB);

    bool changed = true;

    while (changed)
    {
        changed = false;
        if (savesA == -1)
        {
            if (shotsB != -1 && goalsB != -1)
            {
                savesA = shotsB - goalsB;
                changed = true;
            }
            else if (shotsB == 0)
            {
                savesA = 0;
                changed = true;
            }
        }

        if (savesB == -1)
        {
            if (shotsA != -1 && goalsA != -1)
            {
                savesB = shotsA - goalsA;
                changed = true;
            }
            else if (shotsA == 0)
            {
                savesB = 0;
                changed = true;
            }
        }

        if (goalsA == -1)
        {
            if (shotsA != -1 && savesB != -1)
            {
                goalsA = shotsA - savesB;
                changed = true;
            }
            else if (shotsA == 0)
            {
                goalsA = 0;
                changed = true;
            }
        }

        if (goalsB == -1)
        {
            if (shotsB != -1 && savesA != -1)
            {
                goalsB = shotsB - savesA;
                changed = true;
            }
            else if (shotsB == 0)
            {
                goalsB = 0;
                changed = true;
            }
        }

        if (shotsA == -1)
        {
            if (goalsA != -1 && savesB != -1)
            {
                shotsA = goalsA + savesB;
                changed = true;
            }
        }

        if (shotsB == -1)
        {
            if (goalsB != -1 && savesA != -1)
            {
                shotsB = goalsB + savesA;
                changed = true;
            }
        }
    }


    cout << savesA << " " << goalsA << " " << shotsA << "\n";
    cout << savesB << " " << goalsB << " " << shotsB << "\n";

    return 0;
}