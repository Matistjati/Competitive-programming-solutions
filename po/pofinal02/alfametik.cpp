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
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
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

int evaluate(map<char, int> dict, string str)
{
    int s = 0;
    rep(i, str.size())
    {
        s += dict[str[i]] * pow(10, str.size() - i - 1);
    }
    return s;
}

map<char, int>* ans(vector<string>& terms, string& sum, vector<pair<vector<char>, char>>& columns, queue<char>& left, set<int>& options, int index, int n_chars, int carry, map<char, int>& dict)
{
    if (dict.size() >= columns[index].first.size() + 1)
    {
        int s = 0;
        bool possible = true;
        repe(t, columns[index].first)
        {
            if (setcontains(dict, t))
            {
                s += dict[t];
            }
            else
            {
                possible = false;
                break;
            }
        }

        int aS = -1;
        if (setcontains(dict, columns[index].second))
        {
            aS = dict[columns[index].second];
        }
        else
        {
            possible = false;
        }

        if (possible)
        {
            if ((s + carry) % 10 != aS)
            {
                return nullptr;
            }

            index++;
            carry = (s + carry) / 10;
        }
    }

    if (dict.size() == n_chars)
    {
        int sEval = evaluate(dict, sum);
        int s = 0;
        repe(term, terms)
        {
            s += evaluate(dict, term);
            if (s > sEval)
            {
                return nullptr;
            }
        }

        if (s == sEval)
        {
            pair<vector<char>, char> column = columns[columns.size()-1];
            repe(c, column.first)
            {
                if (dict[c] == 0)
                {
                    return nullptr;
                }
            }
            if (dict[column.second] == 0)
            {
                return nullptr;
            }
            return new map<char, int>(dict);
        }
    }

    queue<char> leftC(left);

    char currC = leftC.front();
    leftC.pop();
    repe(option, options)
    {
        set<int> c(options);
        c.erase(option);
        map<char, int> dictC(dict);
        dictC[currC] = option;

        map<char, int>* ret = ans(terms, sum, columns, leftC, c, index, n_chars, carry, dictC);
        if (ret != nullptr)
        {
            return ret;
        }
    }

    return nullptr;
}

int main()
{
    fast();

    int n;
    read(n);

    set<char> chars;

    vector<string> terms;
    int longest = -inf;
    rep(i, n)
    {
        readpush(string, terms);
        longest = max(longest, (int)terms[terms.size() - 1].size());
        repe(c, terms[terms.size() - 1])
        {
            chars.insert(c);
        }
    }
    string sum;
    read(sum);
    repe(c, sum)
    {
        chars.insert(c);
    }
    longest = max(longest, (int)sum.size());

    vector<pair<vector<char>, char>> columns;
    rep(i, longest)
    {
        vector<char> t;
        repe(term, terms)
        {
            if (term.size() - i - 1 < term.size())
            {
                t.push_back(term[term.size() - i - 1]);
            }
        }

        pair<vector<char>, char> column = { t,sum[sum.size() - i - 1] };
        columns.push_back(column);
    }


    queue<char> charV;
    repe(c, chars)
    {
        charV.push(c);
    }
    set<int> options = { 9,8,7,6,5,4,3,2,1,0 };
    map<char, int> m;
    map<char, int> ansMap = *ans(terms, sum, columns, charV, options, 0, charV.size(), 0, m);
    repe(term, terms)
    {
        repe(c, term)
        {
            cout << ansMap[c];
        }
        cout << "\n";
    }

    repe(c, sum)
    {
        cout << ansMap[c];
    }

    return 0;
}