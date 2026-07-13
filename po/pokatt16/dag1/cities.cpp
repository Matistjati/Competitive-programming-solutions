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

int merge(deque<ll>& a, deque<ll>& b, int k)
{
    if (a.size() < b.size()) swap(a, b);

    int ret = 0;
    for (int i = max<int>(0, k-sz(b)+1); i < min<int>(sz(a), k + 1); i++) ret += a[i] * b[k - i];

    rep(i, b.size()) a[i] += b[i];
    return ret;
}

using nodeV = pair<ll, deque<ll>>;

nodeV pathsLenK(int node, int parent, int k, vvi& edges)
{
    nodeV ret = { 0, {1} };

    repe(edge, edges[node])
    {
        if (edge == parent) continue;

        nodeV a = pathsLenK(edge, node, k, edges);
        a.second.push_front(0);

        ret.first += merge(ret.second, a.second, k) + a.first;
    }

    return ret;
}

ll paths(int n, int k, int f[], int t[]) {
    vvi edges(n);

    rep(i, n-1)
    {
        edges[f[i]].emplace_back(t[i]);
        edges[t[i]].emplace_back(f[i]);
    }

    return pathsLenK(0, -1, k, edges).first;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);


    int n, k;
    cin >> n >> k;
    vector<int> conA(n-1);
    for (auto& v : conA) cin >> v;
    vector<int> conB(n-1);
    for (auto& v : conB) cin >> v;
    cout << paths(n,k,&conA[0], &conB[0]) << '\n';

    return 0;
}

