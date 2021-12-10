#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 tuple<ll,ll,ll>
#define p4 vi
#define ip3 tuple<int,int,int>
#define ip4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define write(a) cout << (a) << "\n"
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repp(i, low, high) for (ll i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}


int k;

int evaluate(string& config)
{
    int pairs = 0;
    rep(i, config.size() - 1)
    {
        pairs += config[i] == config[i + 1];
    }
    return pairs;
}

#define state tuple<int,int,string>

int best(map<state,int>& memo, string& config, int index, int mask, string old, int score)
{
    state s = { index,mask,old };
    if (setcontains(memo,s))
    {
        return memo[s] + score;
    }
    if (index == config.size())
    {
        return score;
    }
    if (old.size()==2)
    {
        return score;
    }

    int ans = score;

    if (true)
    {
        string c = old;
        c.erase(begin(c));
        if (index + 4 < config.size())
        {
            c += config[index + 4];
        }
        ans = max(ans, best(memo,config, index + 1, mask >> 1, c, score));
    }

    for (int i = 1; i <= k; i++)
    {
        if (!(mask & (1 << 1)) && !(mask & (1 << (i+1))))
        {
            int maskCopy = mask;
            maskCopy |= (1 << (k));

            string c = old;

            swap(c[1], c[1+i]);
            int newScore = score + evaluate(c)-evaluate(old);

            if (index+4<config.size())
            {
                c.erase(begin(c));
                c += config[index + 4];
            }

            ans = max(ans, best(memo, config, index + 1, maskCopy >> 1, c, newScore));
        }
    }

    memo[s] = ans - score;

    return ans;
}

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread(string, config);
    read(k);


    map<tuple<int, int, string>, int> memo;
    cout << best(memo, config, 0, 0, "P"+config.substr(0,4), evaluate(config));


    cout << endl;
    _Exit(0);
}