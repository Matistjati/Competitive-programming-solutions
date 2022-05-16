#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
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

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif



    int n;
    read(n);

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

    map<ll, int> n_requests = {};
    queue<ll> requestLimit;

    rep(i, requests.size())
    {
        string request = requests[i];
        vector<string> requestParts = split(request, ':');
        string requestIp = requestParts[0];
        string requestPort = requestParts[1];

        ll ipHash = 0;
        for (int i = 0; i < requestIp.size();i++)
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