#include <bits/stdc++.h>

using namespace std;

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

int answer(vector<vector<int>>& tree, vector<bool>& visited, vector<bool>& nuts, int curr)
{
    if (visited[curr])
    {
        return 0;
    }
    else
    {
        visited[curr] = true;
    }

    int ret = 0;

    repe(branch, tree[curr])
    {
        ret += answer(tree, visited, nuts, branch);
    }

    return ret + ((ret > 0) | nuts[curr]);
}


int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif


    int n, k;
    read(n);
    read(k);

    vector<bool> nuts(n+1);
    vector<vector<int>> tree(n+1, vector<int>());

    rep(i, k)
    {
        dread(int, p);
        nuts[p] = true;
    }

    rep(i, n - 1)
    {
        dread2(int, a,b);
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    vector<bool> visited(n+1);

    write((answer(tree,visited,nuts,1)-1)*2);


    return 0;
}