#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> vi;
ll inf = ll(1e18);
#define rep(i,lo,hi) for (int i=lo; i<hi;i++)
#define pb push_back

int main()
{
    map<string, int> powerlevel;
    powerlevel["Shadow"] = 6;
    powerlevel["Gale"] = 5;
    powerlevel["Ranger"] = 4;
    powerlevel["Anvil"] = 7;
    powerlevel["Vexia"] = 3;
    powerlevel["Guardian"] = 8;
    powerlevel["Thunderheart"] = 6;
    powerlevel["Frostwhisper"] = 2;
    powerlevel["Voidclaw"] = 3;
    powerlevel["Ironwood"] = 3;
    powerlevel["Zenith"] = 4;
    powerlevel["Seraphina"] = 1;

    vector<pair<int, int>> locs;

    auto readloc = [&](bool first, int loc)
    {
        int n;
        cin >> n;
        vector<pair<string, int>> units;
        rep(i, 0, n)
        {
            string name;
            cin >> name;
            if (powerlevel.find(name) == powerlevel.end())
            {
                assert(0);
            }
            units.emplace_back(name, powerlevel[name]);
        }

        rep(i, 0, n)
        {
            if (units[i].first == "Thunderheart" && n == 4)
            {
                units[i].second *= 2;
            }
            if (units[i].first == "Zenith" && loc == 1)
            {
                units[i].second += 5;
            }
        }

        rep(i, 0, n)
        {
            if (units[i].first == "Seraphina")
            {
                rep(j, 0, n)
                {
                    if (i == j) continue;
                    units[j].second++;
                }
            }
        }
        int totpower = 0;
        rep(i, 0, n) totpower += units[i].second;
        if (first) locs.back().first = totpower;
        else locs.back().second = totpower;
    };

    rep(i, 0, 3)
    {
        locs.emplace_back(-1000, -1000);
        readloc(true, i);
        readloc(false, i);
    }

    int player1won = 0;
    int player2won = 0;
    int player1power = 0;
    int player2power = 0;

    rep(i, 0, 3)
    {
        if (locs[i].first > locs[i].second) player1won++;
        if (locs[i].second > locs[i].first) player2won++;
        player1power += locs[i].first;
        player2power += locs[i].second;
    }

    if (player1won > player2won)
    {
        cout << "Player 1";
    }
    else if (player2won > player1won)
    {
        cout << "Player 2";
    }
    else
    {
        if (player1power > player2power)
        {
            cout << "Player 1";
        }
        else if (player2power > player1power)
        {
            cout << "Player 2";
        }
        else
        {
            cout << "Tie";
        }
    }

    return 0;
}