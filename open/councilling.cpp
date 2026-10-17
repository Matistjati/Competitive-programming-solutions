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

struct PushRelabel {
	struct Edge {
		int dest, back;
		ll f, c;
	};
	vector<vector<Edge>> g;
	vector<ll> ec;
	vector<Edge*> cur;
	vector<vi> hs; vi H;
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n) {}

	void addEdge(int s, int t, ll cap, ll rcap = 0) {
		if (s == t) return;
		g[s].push_back({ t, (int)sz(g[t]), 0, cap });
		g[t].push_back({ s, (int)sz(g[s]) - 1, 0, rcap });
	}

	void addFlow(Edge& e, ll f) {
		Edge& back = g[e.dest][e.back];
		if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
		e.f += f; e.c -= f; ec[e.dest] += f;
		back.f -= f; back.c += f; ec[back.dest] -= f;
	}
	ll calc(int s, int t) {
		int v = sz(g); H[s] = v; ec[t] = 1;
		vi co(2 * v); co[0] = v - 1;
		rep(i, v) cur[i] = g[i].data();
		for (Edge& e : g[s]) addFlow(e, e.c);

		for (int hi = 0;;) {
			while (hs[hi].empty()) if (!hi--) return -ec[s];
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ec[u] > 0)  // discharge u
				if (cur[u] == g[u].data() + sz(g[u])) {
					H[u] = 1e9;
					for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest] + 1)
						H[u] = H[e.dest] + 1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						rep(i, v) if (hi < H[i] && H[i] < v)
						--co[H[i]], H[i] = v + 1;
					hi = H[u];
				}
				else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
					addFlow(*cur[u], min(ec[u], cur[u]->c));
				else ++cur[u];
		}
	}
	bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

		vector<string> names;
		map<string, int> partyindex;
		vector<string> parties;
		map<string, int> clubindex;
		vector<string> clubs;
		vvi edges;
		vi whichparty;
		rep(i, n) {
            string name, party;
            cin >> name >> party;
			names.push_back(name);
			if (!partyindex.count(party)) partyindex[party] = partyindex.size(), parties.push_back(party);
			whichparty.push_back(partyindex[party]);
            int deg;
            cin >> deg;
			rep(j, deg) {
                string club;
                cin >> club;
				if (!clubindex.count(club)) clubindex[club] = clubindex.size(), clubs.push_back(club), edges.push_back({});
				edges[clubindex[club]].push_back(i);
			}
		}
		int numclubs = clubs.size();
		int numparties = parties.size();
		int partysizelimit = (numclubs - 1) / 2;
		PushRelabel flow(n+n+ numclubs +2);
		// person: [0,n-1]
		// party: [n,2*n-1]
		// club: [2*n,2*n+numclubs-1]
		rep(i, n) // person to party
		{
			flow.addEdge(i, n + whichparty[i], 1);
		}
		repe(ind, partyindex) // party to sink
		{
			flow.addEdge(n+ind.second, n+n+numclubs, partysizelimit);
		}
		rep(i, edges.size())
		{
			// source to club
			flow.addEdge(n + n + numclubs + 1, 2 * n + i, 1);
			// club to person
			repe(e, edges[i])
			{
				flow.addEdge(2 * n + i, e, 1);
			}
		}
		if (flow.calc(2*n+numclubs+1, 2*n+numclubs)!=numclubs)
		{
			cout << "Impossible.\n";
		}
		else
		{
			rep(i, numclubs)
			{
				repe(e, flow.g[2 * n + i])
				{
					if (e.f>0)
					{
						cout << names[e.dest] << " " << clubs[i] << "\n";
					}
				}
			}
		}
		cout << "\n";
    }

    return 0;
}
