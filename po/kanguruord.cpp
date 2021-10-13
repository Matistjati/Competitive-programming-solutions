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
#define p2 pair<ll, ll>
#define p3 tuple<ll, ll, ll>
#define vi vector<ll>
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

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

    string s;
    read(s);
    string rs(s);
    reverse(all(rs));

    int n;
    read(n);

    vector<string> words;
    rep(i, n)
    {
        readpush(string, words);
    }

    map<char, vector<int>> occurences;
    rep(i, s.size())
    {
        char letter = s[i];
        if (!setcontains(occurences,letter))
        {
            occurences[letter] = vector<int>();
        }
        occurences[letter].push_back(i);
    }
    map<char, vector<int>> rOccurences;


    int n_messy = 0;
    repe(word, words)
    {

        vector<int> indices;
        int j = 0;
        bool done = true;
        int prev = -1;
        rep(i, word.size())
        {
            char letter = word[i];

            vector<int>& indiceOcc = occurences[letter];
            auto it = upper_bound(indiceOcc.begin(), indiceOcc.end(), prev);
            if (it == occurences[letter].end())
            {
                done = false;
                break;
            }
            indices.push_back(*it);
            prev = *it;
        }


        if (!done)
        {
            continue;
        }

        vector<int> indicesReverse;
        reverse(all(word));
        j = 0;
        per(i, s.size()-1)
        {
            if (word[j] == s[i])
            {
                indicesReverse.push_back(i);
                j++;
                if (j == word.size())
                {
                    break;
                }
            }
        }

        reverse(all(indicesReverse));
        if (indices!=indicesReverse)
        {
            n_messy++;
        }
    }

    write(n_messy);

    return 0;
}