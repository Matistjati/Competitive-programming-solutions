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


struct RollbackUF {
	vi e; vector<p2> st;
	RollbackUF(int n) : e(n, -1) {}
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : find(e[x]); }
	int time() { return sz(st); }

	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		st.push_back({ a, e[a] });
		st.push_back({ b, e[b] });
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

struct Edge { int a, b; ll w; };
struct Node { /// lazy skew heap node
	Edge key;
	Node* l, * r;
	ll delta;
	void prop() {
		key.w += delta;
		if (l) l->delta += delta;
		if (r) r->delta += delta;
		delta = 0;
	}
	Edge top() { prop(); return key; }
};
Node* merge(Node * a, Node * b) {
	if (!a || !b) return a ? a : b;
	a->prop(), b->prop();
	if (a->key.w > b->key.w) swap(a, b);
	swap(a->l, (a->r = merge(b, a->r)));
	return a;
}
void pop(Node * &a) { a->prop(); a = merge(a->l, a->r); }

ll dmst(int n, int r, vector<Edge>&g) {
	RollbackUF uf(n);
	vector<Node*> heap(n);
	for (Edge e : g) heap[e.b] = merge(heap[e.b], new Node{ e });
	ll res = 0;
	vi seen(n, -1), path(n), par(n);
	seen[r] = r;
	vector<Edge> Q(n), in(n, { -1,-1 }), comp;
	deque<tuple<int, int, vector<Edge>>> cycs;
	repp(s, 0, n) {
		int u = s, qi = 0, w;
		while (seen[u] < 0) {
			if (!heap[u]) return -1;
			Edge e = heap[u]->top();
			heap[u]->delta -= e.w, pop(heap[u]);
			Q[qi] = e, path[qi++] = u, seen[u] = s;
			res += e.w, u = uf.find(e.a);
			if (seen[u] == s) { /// found cycle, contract
				Node* cyc = 0;
				int end = qi, time = uf.time();
				do cyc = merge(cyc, heap[w = path[--qi]]);
				while (uf.join(u, w));
				u = uf.find(u), heap[u] = cyc, seen[u] = -1;
				cycs.push_front({ u, time, {&Q[qi], &Q[end]} });
			}
		}
		repp(i, 0, qi) in[uf.find(Q[i].b)] = Q[i];
	}

	return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;
	vector<Edge> edges;
	rep(i, n)
	{
		ll item, dur;
		cin >> item >> dur;
		edges.emplace_back(item, i+1, dur);
		rep(j, n + 1)
		{
			ll v;
			cin >> v;
			edges.emplace_back(j, i+1, v);
		}
	}
	cout << dmst(n+1, 0, edges) << '\n';

    return 0;
}
