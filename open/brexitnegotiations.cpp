#include <bits/stdc++.h>

using namespace std;
#define rep(i,n) for(int i = 0; i < n; i++)
typedef long long ll;
typedef vector<ll> vi;

ll doit(ll mid, vi indeg, vi& cost, vector<vi>& edges)
{
    map<ll,vector<ll>> q;

    ll n = indeg.size();
    rep(i,n)
    {
        if (indeg[i]==0)
        {
            q[cost[i]].push_back(i);
        }
    }

    ll t = 0;
    while (q.size())
    {
        auto it = q.lower_bound(mid-t);
        if (it==q.begin()) return 0;
        it = prev(it);
        ll u = it->second.back();
        it->second.pop_back();
        if (it->second.empty()) q.erase(it);
        
        for (auto& e: edges[u])
        {
            indeg[e]--;
            if (indeg[e]==0)
            {
                q[cost[e]].push_back(e);
            }
        }

        t++;
    }
    return 1;
}

int main()
{
    int n;
    cin >> n;

    vi outdeg(n);
    vi cost(n);
    vector<vi> redges(n);
    rep(i,n)
    {
        cin >> cost[i];
        int v;
        cin >> v;
        rep(j,v)
        {
            int k;
            cin >> k;
            k--;
            redges[i].emplace_back(k);
            outdeg[k]++;
        }
    }

    int t = n-1;
    priority_queue<pair<ll,ll>> pq;
    rep(i,n)
    {
        if (outdeg[i]==0) pq.emplace(-cost[i],i);
    }
    ll ans = 0;
    while (pq.size())
    {
        ll d,u;
        tie(d,u) = pq.top(); pq.pop();
        ans = max((-d)+t,ans);
        for (auto& e : redges[u])
        {
            outdeg[e]--;
            if(outdeg[e]==0)
            {
                pq.emplace(-cost[e],e);
            }
        }

        t--;
    }

    cout << ans;
    return 0;
}
