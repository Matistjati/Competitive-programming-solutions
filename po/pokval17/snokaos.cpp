#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define always32int int
#define ll long long
#if 0
#define int ll
#endif
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
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

int calcscoreslow(vector<vector<int>>& weights, int low, int high)
{
    int score = 0;

    repp(i, low+1, high)
    {
        score += weights[i][high];
    }

    return score;
}

#define state tuple<int,int,int>

int ans(vector<vector<vector<int>>>& memo, vector<vector<int>>& weights, vector<bool>& snowed, int index, int prevIgnored, int p)
{
    int& v = memo[index][prevIgnored + 1][p];
    if (v != -1)
    {
        return v;
    }

    if (index+1 == snowed.size())
    {
        return calcscoreslow(weights, prevIgnored, index);
    }

    int ret = 0;

    bool snowing = snowed[index+1];

    if (p > 0 && snowing)
    {
        ret = max(ret, ans(memo, weights, snowed, index + 1, prevIgnored, p - snowing));
    }

    int r = ans(memo, weights, snowed, index + 1, (snowing ? index : prevIgnored), p);
    if (snowing)
    {
        r += calcscoreslow(weights, prevIgnored, index);
    }
    ret = max(ret, r);

    return v = ret;
}

always32int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread4(int, n, m, s, p);
    vvi weights(n, vi(n));

    if (p>=s)
    {
        cout << m << endl;
        _Exit(0);
    }

    rep(i, m)
    {
        dread2(int, start, end);
        start--;
        end--;
        if (start > end)
        {
            swap(start, end);
        }
        weights[start][end]++;
    }

    vector<bool> snowed(n);
    rep(i, s)
    {
        dread(int, station);
        station;
        snowed[station] = true;
    }

    vvi accumweights(n, vi(n));

    rep(i, n)
    {
        repp(j, 1, n)
        {
            weights[i][j] += weights[i][j - 1];
        }
    }

    vvvi memo(n + 1, vvi(n + 2, vi(p + 1, -1)));
    cout << ans(memo, weights, snowed, 0, -1, p);

    cout << endl;
    _Exit(0);
}