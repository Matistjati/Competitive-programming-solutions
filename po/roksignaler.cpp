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

    map<string, char> signalToChar;
    rep(i, 26)
    {
        string letter;
        read(letter);
        string sequence;
        read(sequence);

        signalToChar[sequence] = letter[0];
    }
    int s;
    int p;
    read(s);
    read(p);
    int t;
    int b;
    int m;
    read(t);
    read(b);
    read(m);

    int discard;
    read(discard);

    string sequence;
    read(sequence);


    string newChar = string(b, '0');
    string space = string(m, '0');
    string newType = string(t, '0');
    string line = string(s, '1');
    string dot = string(p, '1');
    string ans = "";

    string currentSequence = "";

    int zeros = 0;
    int ones = 0;
    rep(i, sequence.size())
    {
        if (sequence[i] == '0')
        {
            auto f = sequence.find('1', i);
            if (f == string::npos)
            {
                ones = sequence.size() - i;
                break;
            }
            zeros = f-i;
            i = sequence.find('1', i)-1;
        }
        else
        {
            auto f = sequence.find('0', i);
            if (f == string::npos)
            {
                ones = sequence.size() - i;
                break;
            }
            ones = f - i;
            i = sequence.find('0', i)-1;
        }
        if (zeros == b)
        {
            if (ones == s)
            {
                currentSequence += '-';
            }
            else
            {
                currentSequence += '.';
            }
            zeros = 0;
            ones = 0;
            ans += signalToChar[currentSequence];
            currentSequence = "";
        }
        else if (zeros == m)
        {
            if (ones == s)
            {
                currentSequence += '-';
            }
            else
            {
                currentSequence += '.';
            }
            zeros = 0;
            ones = 0;
            ans += signalToChar[currentSequence];
            currentSequence = "";
            ans += ' ';
        }
        else if (zeros == t)
        {
            if (ones == s)
            {
                currentSequence += '-';
            }
            else
            {
                currentSequence += '.';
            }
            ones = 0;
            zeros = 0;
        }
    }

    if (ones == s)
    {
        currentSequence += '-';
    }
    else
    {
        currentSequence += '.';
    }
    ans += signalToChar[currentSequence];
    write(ans);

    return 0;
}