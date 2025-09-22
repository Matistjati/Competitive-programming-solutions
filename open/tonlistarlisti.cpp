#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

struct Tree
{
	vi tot_len;
	vi tot_listens;
	Tree(int n) : tot_len(n*4), tot_listens(n*4) {}

	void set_len(int x, int l, int r, int i, int v)
	{
		if (l == r) return void(tot_len[x] = v);
		int mid = (l + r) / 2;
		if (i <= mid) set_len(x * 2, l, mid, i, v);
		else set_len(x * 2 + 1, mid + 1, r, i, v);
		tot_len[x] = tot_len[x * 2] + tot_len[x * 2 + 1];
	}

	int rightmost(int x, int l, int r, ll amount)
	{
		if (l == r)
		{
			assert(amount < tot_len[x]);
			return l - 1;
		}
		int mid = (l + r) / 2;
		if (amount < tot_len[x * 2]) return rightmost(x * 2, l, mid, amount);
		return rightmost(x * 2 + 1, mid + 1, r, amount - tot_len[x * 2]);
	}

	void add(int x, int l, int r, int ql, int qr, ll amount)
	{
		if (l > qr || r < ql) return;
		if (l >= ql && r <= qr) return void(tot_listens[x]+=amount);
		int mid = (l + r) / 2;
		add(x * 2, l, mid, ql, qr,amount);
		add(x * 2 + 1, mid + 1, r, ql, qr,amount);
	}

	ll query(int x, int l, int r, int i)
	{
		if (l == r) return tot_listens[x];
		ll ret = 0, mid=(l+r)/2;
		if (i <= mid) return tot_listens[x] + query(x * 2, l, mid, i);
		else return tot_listens[x] + query(x * 2 + 1, mid + 1, r, i);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	ll tot_len = 0;

	int q;
	cin >> q;
	int n = q;
	Tree tree(n);
	int curr_first = n-1;

	map<string, int> idx;
	map<string, int> extra_add;
	map<string, int> length;
	map<string, bool> in_playlist;

	while (q--)
	{
		char t;
		cin >> t;
		if (t == 'L')
		{
			string name;
			ll l;
			cin >> name >> l;
			if (!idx.count(name)) extra_add[name] = 0, in_playlist[name]=false;
			length[name] = l;
			if (in_playlist[name])
			{
				int ind = idx[name];
				extra_add[name] += tree.query(1, 0, n - 1, ind); //query
				tree.set_len(1, 0, n - 1, ind, 0);
				tot_len -= length[name];
				in_playlist[name] = 0;
			}
			else
			{
				in_playlist[name] = 1;
				idx[name] = curr_first--;
				tot_len += l;
				tree.set_len(1, 0, n - 1, idx[name], l);
			}
		}
		else if (t == 'P')
		{
			ll l;
			cin >> l;
			ll lazy_add = l / tot_len;
			ll free_listen = l % tot_len;
			ll rightmost = tree.rightmost(1, 0, n - 1, free_listen);
			tree.add(1, 0, n - 1, curr_first + 1, rightmost, 1);
			tree.add(1, 0, n - 1, curr_first + 1, n-1, lazy_add);
		}
		else if (t == 'Q')
		{
			string name;
			cin >> name;

			if (idx.count(name))
			{
				ll ans = extra_add[name];
				if (in_playlist[name]) ans+= tree.query(1, 0, n - 1, idx[name]);
				cout << ans << '\n';
			}
			else cout << "0\n";
		}
		else assert(0);
	}


	return 0;
}
