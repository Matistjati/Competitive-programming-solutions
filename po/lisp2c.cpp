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

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

pair<string,int> answer(string& q, int start)
{
    string functionName = "";
    vector<string> parameters;

    int spaceIndex = min(q.find(' ', start),q.find(')',start));

    functionName = q.substr(start+1, spaceIndex - start-1);

    string currParameter = "";

    int end = -1;
    int itEnd = q.size();

    for (int i = spaceIndex; i < itEnd; i++)
    {
        if (q[i] == '(')
        {
            auto n = answer(q, i);
            parameters.push_back(n.first);
            if (n.second!=-1)
            {
                end = max(end, n.second + 1);
                i = n.second;
            }

        }
        else if (q[i] == ')')
        {
            end = max(end,i);
            break;
        }
        else if (q[i] == ' ')
        {
            if (currParameter != "")
            {
                parameters.push_back(currParameter);
            }
            currParameter = "";
        }
        else
        {
            currParameter += q[i];
        }
    }

    if (currParameter != "")
    {
        parameters.push_back(currParameter);
    }
    string ret = "";
    ret += functionName;
    ret += "(";
    repe(parameter, parameters)
    {
        ret += parameter + ", ";
    }
    if (parameters.size())
    {
        ret.resize(ret.size() - 1);
        ret[ret.size() - 1] = ')';
    }
    else
    {
        ret += ')';
    }

    return { ret,end };
}

int main()
{
    fast();

    string lisp;
    getline(cin, lisp);

    auto c = answer(lisp, 0);
    write(c.first);


    return 0;
}