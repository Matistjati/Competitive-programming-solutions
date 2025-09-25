#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = ll(1e18);
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll,ll>;

#define rep(i,b) for(int i = 0; i < (b); i++)
#define repp(i,a,b) for(int i = (a); i < (b); i++)
#define repe(i,a) for(auto& i : a)
#define sz(x) ((int)x.size())

int main() {
    ll n,m,k;
    cin >> n >> m >> k;

    vi wormhole(n);
    rep(i,k)
    {
        int x;
        cin >> x;
        x--;
        wormhole[x]=1;
    }

    vvi adj(n);
    rep(i,m)
    {
        int a,b;
        cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto djikstra = [&](ll x)
    {
        vi dist(n, inf);
        queue<p2> q;
        q.emplace(0, x);
        while (sz(q))
        {
            auto [d, u] = q.front();
            q.pop();
            if (dist[u]!=inf) continue;
            dist[u]=d;

            repe(e,adj[u])
            {
                q.emplace(d+1,e);
            }
        }
        return dist;
    };

    vi dist_home = djikstra(0);
    vi dist_dest = djikstra(n-1);
    ll ans = dist_home.back(); // we can always go straight into goal

    // home -> wormhole
    // wormhole -> goal
    ll dist_wormhole = inf;
    ll tot_wormhole_dist = 0;
    ll num_wormhole = 0;
    rep(i,n)
    {
        if (wormhole[i])
        {
            dist_wormhole = min(dist_wormhole, dist_home[i]);
            tot_wormhole_dist += dist_dest[i];
            num_wormhole++;
        }
    }

    assert(num_wormhole>=2);

    auto normalize = [](p2 x)
    {
        ll g = gcd(x.first,x.second);
        return p2(x.first/g,x.second/g);
    };
    p2 best = {ll(1e9),1};
    rep(i,n)
    {
        if (wormhole[i])
        {
            ll my_dist=dist_home[i];
            ll tot_dist = tot_wormhole_dist-dist_dest[i];
            ll wh = num_wormhole-1;
            my_dist*=wh;
            p2 p = normalize(p2(my_dist+tot_dist, wh));
            if (p.first * best.second < best.first * p.second)
            {
                best = p;
            }
        }
    }

    // cout << ans << " " << dist_wormhole << " " << tot_wormhole_dist << " " << num_wormhole << '\n';
    // ans < dist_wormhole+tot_wormhole_dist/num_wormhole
    if (best.first < ans * best.second)
    {
        cout << best.first << "/" << best.second << '\n';
    }
    else
    {
        cout << ans << "/1\n";
    }

    return 0;
}

