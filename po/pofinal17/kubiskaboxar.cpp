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
#define dread3(type, a, b, c) dread(type, a); dread(type, b); dread(type, c)
#define write(a) cout << (a) << endl
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
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

int bestbox(vector<int> r, vector<int> g, bool first)
{
    sort(all(r));

    sort(all(g));
    reverse(all(g));
    int matches = 0;
    int gsize = g.size();

    int j = 0;
    for (int i = 0; i < r.size(); i++)
    {
        int rem = -1;
        for (int j = 0; j < g.size(); j++)
        {
            if (r[i] > g[j])
            {
                rem = j;
                matches++;
                break;
            }
        }
        if (rem != -1)
        {
            g.erase(next(begin(g), rem));

        }
    }
    if (first)
    {
        return r.size() + gsize - matches;
    }
    return r.size() - matches;
}


int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread(int, n);

    vector<int> r;
    vector<int> g;
    vector<int> b;
    rep(i, n)
    {
        dread(int, side);
        dread(char, type);
        if (type == 'R')
        {
            r.push_back(side);
        }
        else if (type == 'G')
        {
            g.push_back(side);
        }
        else
        {
            b.push_back(side);
        }
    }

    int best = inf;
    string comb = "";
    int v = bestbox(r, g, false) + bestbox(g, b, true);
    if (v < best)
    {
        best = v;
        comb = "RGB";
    }

    v = bestbox(r, b, false) + bestbox(b, g, true);
    if (v < best)
    {
        best = v;
        comb = "RBG";
    }

    v = bestbox(b, g, false) + bestbox(g, r, true);
    if (v < best)
    {
        best = v;
        comb = "BGR";
    }

    v = bestbox(b, r, false) + bestbox(r, g, true);
    if (v < best)
    {
        best = v;
        comb = "BRG";
    }


    v = bestbox(g, b, false) + bestbox(b, r, true);
    if (v < best)
    {
        best = v;
        comb = "GBR";
    }

    v = bestbox(g, r, false) + bestbox(r, b, true);
    if (v < best)
    {
        best = v;
        comb = "GRB";
    }

    cout << comb << "\n" << best << "\n";

    return 0;
    _Exit(0);
}