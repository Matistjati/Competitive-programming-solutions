#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct dsu {
	vector<int> id, size, smallest;
	stack<stack<pair<int&, int>>> st;

	dsu(int n) : id(n), size(n, 1), smallest(n) {
		iota(id.begin(), id.end(), 0);
		iota(smallest.begin(), smallest.end(), 0);
		st.emplace();
	}

	void save(int& x) { st.top().emplace(x, x); }

	void checkpoint() { st.emplace(); }

	void rollback() {
		while (st.top().size()) {
			auto [end, val] = st.top().top(); st.top().pop();
			end = val;
		}
		st.pop();
	}

	int find(int a) { return a == id[a] ? a : find(id[a]); }

	void unite(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);
		save(size[a]), save(id[b]), save(smallest[a]);
		size[a] += size[b], id[b] = a;
		smallest[a] = min(smallest[a], smallest[b]);
	}

	int get_smallest(int a) {
		return smallest[find(a)];
	}

	void update(pair<int, int> p) {
		checkpoint();
		unite(p.first, p.second);
	}
};

// assumes all priorities are distinct
template<typename DS, typename UPD> struct priority_queue_ds {
	DS D;
	vector<tuple<UPD, int, int>> upd; // {u, p, idx_in_pos}
	set<pair<int, int>> st;
	vector<int> pos;

	priority_queue_ds(int n) : D(n) {}

	void update(UPD u, int p) { // O(log n + T(n))
		D.update(u);
		st.emplace(p, pos.size());
		upd.emplace_back(u, p, pos.size());
		pos.push_back(upd.size() - 1);
	}

	int find(int a) { // O(T(n))
		return D.find(a);
	}
	
	int size(int a) { // O(T(n))
		return D.size[D.find(a)];
	}
	
	int stable_leader(int a) { // O(T(n))
		return D.smallest[D.find(a)];
	}

	void pop() { // O(log n + k T(n))
		int k = 1, min_p; // k = number of pops we will do
		vector<tuple<UPD, int, int>> small, big;
		auto it = st.end();
		for (int qt = 0; qt++ < (k + 1) / 2;) {
			it--;
			min_p = it->first;
			int i = pos[it->second];
			if (qt > 1) big.push_back(upd[i]);
			k = max<int>(k, upd.size() - i);
		}

		for (int i = 0; i < k; i++) {
			D.rollback();
			auto [u, p, idx] = upd.rbegin()[i];
			if (p < min_p) small.emplace_back(u, p, idx);
		}

		st.erase(prev(st.end()));
		upd.erase(upd.end() - k, upd.end());

		small.insert(small.end(), big.rbegin(), big.rend());
		for (auto [u, p, idx] : small) {
			D.update(u);
			upd.emplace_back(u, p, idx);
			pos[idx] = upd.size() - 1;
		}
	}
};

struct Node
{
	int l, r;
	Node* lc = 0, * rc = 0;
	int sum = 0;
	int cc = 0;

	Node(int l, int r) : l(l), r(r) {}

	void pointadd(int i, int v)
	{
		if (l == r) return sum += v, void(cc = (v>0));
		int mid = (l + r) / 2;
		if (i <= mid)
		{
			if (!lc) lc = new Node(l, mid);
			lc->pointadd(i, v);
		}
		else
		{
			if (!rc) rc = new Node(mid + 1, r);
			rc->pointadd(i, v);
		}
		sum = 0;
		cc = 0;
		if (rc) sum += rc->sum, cc += rc->cc;
		if (lc)
		{
			cc += lc->cc;
			if (rc && rc->cc % 2 == 1) sum -= lc->sum;
			else sum += lc->sum;
		}
	}
};


signed main()
{
	fast();


	int n, q;
	cin >> n >> q;

	Node* root = new Node(0, 2e10);

	priority_queue_ds<dsu, pair<int, int>> PQ(n);
	priority_queue<array<int, 3>> pq;

    auto insert = [&](int u, int mul)
    {
		int leader = PQ.stable_leader(u);
		int compsz = PQ.size(leader);
        int ind = compsz * (n + 1) + leader;
        //cout << (mul == 1 ? "+" : "-") << compsz << ", leader" << leader << "\n";
        root->pointadd(ind, compsz * mul);
    };

    rep(i, n) insert(i, 1);
    while (q--)
	{
		char t;
		cin >> t;
		if (t == 'a')
		{
			int u, v, p;
			cin >> u >> v >> p;
			u--; v--;
            pq.push({ p,u,v });
            
            if (PQ.find(u)!= PQ.find(v))
            {
                insert(u, -1);
                insert(v, -1);
				PQ.update({ u, v }, p);
                insert(u, 1);
            }
			else PQ.update({ u, v }, p);
		}
		if (t == 'r')
		{
            auto [p, u, v] = pq.top();
            pq.pop();

			PQ.pop();
            if (PQ.find(u) != PQ.find(v))
            {
				PQ.update({ u, v }, p);
                insert(u, -1);
				PQ.pop();
                insert(u, 1);
                insert(v, 1);				
            }
		}
		if (t == 'd')
		{
			cout << root->sum << endl;
		}
		//cout << "DEB:S=" << root->sum << endl;
	}

	return 0;
}
