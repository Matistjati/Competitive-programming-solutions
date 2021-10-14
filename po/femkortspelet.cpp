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

using namespace std;

#define ll long long
#define p2 pair<ll, ll>
#define p3 tuple<ll, ll, ll>
#define vi vector<ll>
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define deb nothing();

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)

inline void nothing()
{

}

inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

#define alfN 0
#define betN 1

bool hasSuite(vector<pair<char, int>>& player, char suite)
{

    repe(card, player)
    {
        if (suite==card.first)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    fast();

    vector<pair<char, int>> alf;
    vector<pair<char, int>> bet;
    rep(i, 5)
    {
        char suit;
        int number;
        read(suit);
        read(number);
        alf.push_back({suit,number});
    }
    rep(i, 5)
    {
        char suit;
        int number;
        read(suit);
        read(number);
        bet.push_back({ suit,number });
    }

    int alfScore = 0;
    int betScore = 0;
    int currPlayer = alfN;
    bool alfCheated = false;
    bool betCheated = false;
    rep(i, 5)
    {
        pair<char, int> card;
        if (currPlayer == alfN)
        {
            card = alf.front();
            alf.erase(alf.begin());

            pair<char, int> opponentCard = bet.front();
            bet.erase(bet.begin());

            if (opponentCard.first != card.first)
            {
                alfScore = 1;
                betScore = 0;
                if (hasSuite(bet,card.first))
                {
                    betCheated = true;
                }
            }
            else
            {
                if (opponentCard.second > card.second)
                {
                    alfScore = 0;
                    betScore = 1;
                    currPlayer = betN;
                }
                else
                {
                    alfScore = 1;
                    betScore = 0;
                }
            }
        }
        else
        {
            card = bet.front();
            bet.erase(bet.begin());

            pair<char, int> opponentCard = alf.front();
            alf.erase(alf.begin());

            if (opponentCard.first != card.first)
            {
                alfScore = 0;
                betScore = 1;
                if (hasSuite(alf, card.first))
                {
                    alfCheated = true;
                }
            }
            else
            {
                if (opponentCard.second > card.second)
                {
                    alfScore = 1;
                    betScore = 0;
                    currPlayer = alfN;
                }
                else
                {
                    alfScore = 0;
                    betScore = 1;
                }
            }
        }
    }



    write((alfScore) ? "A" : "B");
    if (alfCheated && betCheated)
    {
        write("A och B fuskar");
    }
    else if (alfCheated)
    {
        write("A fuskar");
    }
    else if (betCheated)
    {
        write("B fuskar");
    }


    return 0;
}