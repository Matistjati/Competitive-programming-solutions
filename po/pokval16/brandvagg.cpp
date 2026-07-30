#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

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
    ll limit;
    string ip;
    string port;
};

vector<string> split(string& s, char delim) {
    vector<string> ret;
    istringstream iss(s);
    string item;
    while (getline(iss, item, delim)) {
        ret.push_back(item);
    }
    return ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;

    map<string, ruletype> stringToRule = { {"accept",ruletype::accept},{"drop",ruletype::drop},{"log",ruletype::Log},{"port",ruletype::port},{"ip",ruletype::ip},{"limit",ruletype::limit} };
    vector<pair<ruletype, vector<Rule>>> rules(n);

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

        for (ll i = 1; i < ruleV.size(); i++)
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
                assert(0);
            }

        }
        rules.push_back(ruleP);
    }

    ll p;
    cin >> p;

    vector<string> requests(p);
    rep(i, p) cin >> requests[i];

    map<ll, ll> n_requests = {};
    queue<ll> requestLimit;

    rep(i, requests.size())
    {
        string request = requests[i];
        vector<string> requestParts = split(request, ':');
        string requestIp = requestParts[0];
        string requestPort = requestParts[1];

        ll ipHash = 0;
        for (ll i = 0; i < requestIp.size();i++)
        {
            char c = requestIp[i];
            if (c >= '0' && c <= '9')
            {
                ipHash += (c - '0') * pow(10, i);
            }
        }
        n_requests[ipHash]++;
        requestLimit.push(ipHash);
        if (requestLimit.size() > 1000)
        {
            ll ip = requestLimit.front();
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
                    if (n_requests[ipHash] < rule.limit)
                    {
                        passing = false;
                        break;
                    }
                }
                else
                {
                    assert(0);
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
