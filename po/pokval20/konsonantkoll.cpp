#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <string>
#include <iterator>
#include <queue>
#include <tuple>
#include <numeric>

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

int main()
{
    fast();
    string consonants = "bcdfghjklmnpqrstvwxz";
    string word;
    getline(cin, word);


    string ans = "";

    int n_prev = 0;
    char prev = 'P';
    rep(i, word.size())
    {
        if (word[i] == prev && consonants.find(word[i]) != string::npos)
        {
            n_prev++;
        }
        else
        {
            prev = word[i];
            n_prev = 0;
        }
        if (n_prev > 1)
        {
            continue;
        }
        else
        {
            ans += word[i];
        }
    }

    write(ans);

    return 0;
}