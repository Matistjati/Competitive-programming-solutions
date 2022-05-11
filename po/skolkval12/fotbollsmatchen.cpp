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

int n;
double pr1;
double pr2;

#define args tuple<int,int,int>

double winprob(vector<vector<double>>& memo, int n_a, int n_b, int target, bool left, double prob)
{
    double& dp = memo[n_a][n_b];
    if (dp!=-1)
    {
        return dp;
    }
    if (n_a == n)
    {
        return 1;
    }
    else if (n_b == n)
    {
        return 0;
    }
    if (n_a == target || n_b == target)
    {
        target += 5;
        left = !left;
    }

    double ret = 0;
    if (left)
    {
        ret += winprob(memo, n_a + 1, n_b, target, left, prob) * pr1;
        ret += winprob(memo, n_a, n_b + 1, target, left, prob) * (1 - pr1);
    }
    else
    {
        ret += winprob(memo, n_a + 1, n_b, target, left, prob) * pr2;
        ret += winprob(memo, n_a, n_b + 1, target, left, prob) * (1 - pr2);
    }

    dp = ret;

    return ret;
}

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    cin >> n;
    read(pr1);
    read(pr2);
    vector<vector<double>> memo(n+1, vector<double>(n+1,-1));
    cout << fixed << setprecision(15) << winprob(memo, 0, 0, 5, true, 1);
    cout << endl;
    _Exit(0);
}