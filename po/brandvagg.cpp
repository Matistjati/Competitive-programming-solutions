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

enum ruletype
{
    accept = 1,
    drop = 2,
    Log = 3,
    port = 4,
    ip = 5,
    limit = 6
};

struct Rule
{
    ruletype type;
    int limit;
    string ip;
    string port;
};

int main()
{
    fast();

    int n;
    read(n);

    map<string, ruletype> stringToRule = { {"accept",ruletype::accept},{"drop",ruletype::drop},{"log",ruletype::Log},{"port",ruletype::port},{"ip",ruletype::ip},{"limit",ruletype::limit} };
    vector<pair<ruletype, vector<Rule>>> rules;

    rep(i, n)
    {
        string rule;
        getline(cin, rule);
        if (rule == "")
        {
            getline(cin, rule);
        }

        vector<string> ruleV = split(rule, ' ');

        pair<ruletype, vector<Rule>> ruleP;
        ruleP.first = stringToRule[ruleV[0]];

        for (int i = 1; i < ruleV.size(); i++)
        {
            vector<string> r = split(ruleV[i], '=');
            Rule ruleO;
            ruleO.type = stringToRule[r[0]];
            if (r[0] == "port")
            {
                ruleO.port = r[1];
                ruleP.second.push_back(ruleO);
            }
            else if (r[0] == "ip")
            {
                ruleO.ip = r[1];
                ruleP.second.push_back(ruleO);
            }
            else if (r[0] == "limit")
            {
                ruleO.limit = stoi(r[1]);
                ruleP.second.push_back(ruleO);
            }
            else
            {
                //deb
            }

        }
        rules.push_back(ruleP);
    }

    int p;
    read(p);

    vector<string> requests;
    rep(i, p)
    {
        readpush(string, requests);
    }

    map<string, int> n_requests = {};
    queue<string> requestLimit;

    rep(i, requests.size())
    {
        string request = requests[i];
        vector<string> requestParts = split(request, ':');
        string requestIp = requestParts[0];
        string requestPort = requestParts[1];

        n_requests[requestIp]++;
        requestLimit.push(requestIp);
        if (requestLimit.size() > 1000)
        {
            string ip = requestLimit.front();
            requestLimit.pop();
            n_requests[ip]--;
        }
        repe(ruleset, rules)
        {

            bool passing = true;


            repe(rule, ruleset.second)
            {
                if (rule.type == ruletype::ip)
                {
                    if (requestIp != rule.ip)
                    {
                        passing = false;
                        break;
                    }
                }
                else if (rule.type == ruletype::port)
                {
                    if (requestPort != rule.port)
                    {
                        passing = false;
                        break;
                    }
                }
                else if (rule.type == ruletype::limit)
                {
                    if (n_requests[requestIp] < rule.limit)
                    {
                        passing = false;
                        break;
                    }
                }
                else
                {
                    //deb
                }
            }

            if (passing)
            {
                if (ruleset.first == ruletype::accept)
                {
                    cout << "accept " << i + 1 << "\n";
                    goto endRequest;
                }
                else if (ruleset.first == ruletype::Log)
                {
                    cout << "log " << i + 1 << "\n";
                    continue;
                }
                else if (ruleset.first == ruletype::drop)
                {
                    cout << "drop " << i + 1 << "\n";
                    goto endRequest;
                }
            }


        }

    endRequest:;
    }

    return 0;
}