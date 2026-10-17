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

using ull = unsigned long long;
struct RollingHash
{
    vi suf, b;
    int mod;
    RollingHash(string& s, int base = 131, int mod = 1e9 + 7) : mod(mod), suf(s.size() + 1), b(s.size() + 1)
    {
        b[0] = 1;
        b[1] = base;

		for (int i = sz(s)-1; i >= 0; i--) {
            suf[i] = ((ll)suf[i + 1] * base + (s[i] - 'a' + 1)) % mod;
        }

        repp(i, 2, s.size() + 1)
        {
            b[i] = (ll)b[i - 1] * b[1] % mod;
        }
    }

    ull gethash(int l, int r) // [l, r]
    {
        ll v = suf[l] - (ll)suf[r + 1] * b[r - l + 1];
        // Make sure that v is within [0, mod)
        v %= mod;
        v += mod;
        v %= mod;

        return v;
    }
};

struct DoubleHash
{
    RollingHash h1;
    RollingHash h2;
    DoubleHash(string& s, int base = 131, int mod = 1e9 + 7) : h1(s, base, mod), h2(s, base, mod) {}
    ull GetHash(int l, int r)
    {
        ull hash = ((ull)h1.gethash(l, r) << 32) + h2.gethash(l, r);
        return hash;
    }
};

typedef ull hashType;

hashType stringHash(string& s)
{
    int pow = 153;
    hashType ret = 0;
    hashType base = 1;

    rep(i, s.size())
    {
        ret += s[i] * base;
        base *= pow;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<string> dict;
    unordered_map<ull,int> nameToId;

    string line;
    int id = 0;
    while (getline(cin, line))
    {
        if (line == "") break;
        dict.push_back(line);
        nameToId[stringHash(line)] = id++;
    }

    int n = dict.size();
    vvi edges(n);



    rep(i, n)
    {
        rep(j, dict[i].size())
        {
            repp(k, 'a', 'z' + 1)
            {
                string c(dict[i]);
                c[j] = k;
                ull hash = stringHash(c);
                if (nameToId.contains(hash))
                {
                    if (nameToId[hash]!=i) edges[i].push_back(nameToId[hash]);
                }
            }
        }
    }

    vector<pair<string, string>> queries;
    while (getline(cin, line)) {
		stringstream ss(line);
		string a,b;
		ss >> a >> b;
        queries.emplace_back(a,b);
    }

    repe(quest, queries)
    {
        queue<p2> q;
        vi prev(n,-1);
        int start = nameToId[stringHash(quest.first)];
        q.emplace(start, -2);
        int target = nameToId[stringHash(quest.second)];

        int last = -2;
        while (q.size())
        {
            int u, p;
            tie(u, p) = q.front();
            q.pop();

            if (u == target)
            {
                last = p;
                break;
            }
            if (prev[u] != -1) continue;
            prev[u] = p;

            repe(edge, edges[u])
            {
                q.emplace(edge, u);
            }
        }

        vector<string> path;
        while (last!=-2)
        {
            path.push_back(dict[last]);
            last = prev[last];
        }
        reverse(all(path));
        path.push_back(dict[target]);

        if (path.size()>1)
        {
            repe(p, path) cout << p << "\n";
            cout << "\n";
        }
        else
        {
            cout << "No solution.\n\n";
        }
    }


    return 0;
}
