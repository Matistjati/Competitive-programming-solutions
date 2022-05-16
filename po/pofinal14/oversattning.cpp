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

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
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

template <typename Out>
void split(const std::string& s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

string translate(map<string, vector<string>>& dictForward, map<string, vector<string>>& dictBack, string in)
{

    string prev = in;
    string ans;
    while (true)
    {
        string n = dictBack[dictForward[prev][0]][0];

        if (n == prev)
        {
            ans = prev;
            break;
        }
        prev = n;
    }

    prev = in;
    while (true)
    {
        string n = dictBack[dictForward[prev][0]][0];
        dictBack[dictForward[prev][0]][0] = ans;

        if (n == prev)
        {
            return ans;
        }
        prev = n;
    }
}

int main()
{
    fast();

    int n;
    read(n);

    map<string, vector<string>> dictForward;
    map<string, vector<string>> dictBack;

    rep(i, n)
    {
        string key;
        string value;
        read(key);
        read(value);

        if (!setcontains(dictForward,key))
        {
            dictForward[key] = {};
        }
        if (!setcontains(dictBack,value))
        {
            dictBack[value] = {};
        }

        dictForward[key].push_back(value);
        dictBack[value].push_back(key);
    }

    int m;
    read(m);
    vector<string> words;
    rep(i, m)
    {
        readpush(string, words);
    }

    map<string, string> finalTranslation;

    repe(word, words)
    {

        string finalWord;
        if (setcontains(finalTranslation, word))
        {
            finalWord = finalTranslation[word];
        }
        else
        {
            finalWord = translate(dictForward, dictBack, word);
            finalTranslation[word] = finalWord;
        }
        cout << finalWord << " ";

    }



    return 0;
}
