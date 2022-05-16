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
#define p5 vi
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


double median(vector<pair<ll, string>> v)
 {
    if (v.size()%2==1)
    {
        return v[v.size() / 2].first;
    }
    else
    {
        return (v[v.size() / 2].first+ v[v.size() / 2-1].first)/2.0;
    }
}


ll maxS(vector<pair<ll, string>>& v)
{
    ll maxV = -linf;
    repe(f, v)
    {
        maxV = max(maxV, f.first);
    }
    return maxV;
}

int main()
{
    fast();

    int n;
    read(n);
    vector< vector<pair<ll, string>>> competitions;
    competitions.resize(4, vector<pair<ll, string>>());

    rep(i, n)
    {
        string name;
        int grade;
        int f;

        read(name);
        read(grade);
        read(f);
        vector<ll> katts(3);
        read(katts[0]);
        read(katts[1]);
        read(katts[2]);

        name += to_string(grade);

        competitions[0].push_back({ f,name });
        competitions[1].push_back({ katts[0],name });
        competitions[2].push_back({ katts[1],name });
        competitions[3].push_back({ katts[2],name });
    }


    map<string, vector<float>> players;
    repe(player, competitions[0])
    {
        players[player.second] = {};
    }
    repe(competition, competitions)
    {
        sort(all(competition));
        float compMax = maxS(competition);
        float compMed = median(competition);

        repe(player, competition)
        {
            if (player.first <= compMed)
            {
                players[player.second].push_back(50 * player.first / compMed);
            }
            else
            {
                players[player.second].push_back(50 + 50 * ((player.first - compMed) / (compMax - compMed)));
            }
        }
    }

    vector<pair<float, string>> participants;
    repe(player, players)
    {
        vector<float> scores = { player.second[1], player.second[2],player.second[3] };
        sort(all(scores));
        reverse(all(scores));
        participants.push_back({ player.second[0] + scores[0] + scores[1], player.first });
    }

    sort(all(participants));
    reverse(all(participants));

    vector<string> ioi;
    rep(i, 4)
    {
        ioi.push_back(participants[i].second);
    }

    vector<string> boi;
    for (int i = 4; i < participants.size() && boi.size() < 2; i++)
    {
        if (*(prev(participants[i].second.end())) != '3')
        {
            boi.push_back(participants[i].second);
        }
    }

    sort(all(ioi));
    sort(all(boi));
    repe(person, ioi)
    {
        person.pop_back();
        cout << person << " ";
    }

    cout << "\n";

    repe(person, boi)
    {
        person.pop_back();
        cout << person << " ";
    }

    return 0;
}