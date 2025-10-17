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

enum NodeType
{
	concat, shuffled, sorted, arr
};

struct Node
{
	NodeType type;
	Node *lc, *rc;
	vector<int> content;
	bool attach_node(Node* u)
	{
		if (!lc)
		{
			lc = u;
			return type != concat;
		}
		else if (!rc) {
			rc = u;
			return true;
		}
		else assert(0);
	}
};

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	string a, b;
	cin >> a >> b;

	auto parse = [](string s_in)
	{
		deque<char> s(all(s_in));
		Node* root=0;
		stack<Node*> waiting_nodes;
		while (sz(s))
		{
			Node* u=0;
			char t = s.front();
			if (t == 'c')
			{
				string c = "concat(";
				rep(i, sz(c)) s.pop_front();
				u = new Node();
				u->type = concat;
			}
			else if (t == 's' && s[1] == 'o')
			{
				string c = "sorted(";
				rep(i, sz(c)) s.pop_front();
				u = new Node();
				u->type = sorted;
			}
			else if (t == 's' && s[1] == 'h')
			{
				string c = "shuffle(";
				rep(i, sz(c)) s.pop_front();
				u = new Node();
				u->type = shuffled;
			}
			else if (t == '[')
			{
				// read until next ]

				u = new Node();
				u->type = arr;
				s.pop_front();
				while (1)
				{
					string num;
					while (s.front() != ',' && s.front() != ']')
					{
						num += s.front();
						s.pop_front();
					}
					u->content.push_back(stoi(num));
					if (s.front() == ']')
					{
						s.pop_front();
						break;
					}
					s.pop_front();
				}
			}
			else if (t == ')' || t==',') s.pop_front();
			else assert(0);

			if (!u) continue;
			if (sz(waiting_nodes))
			{
				if (waiting_nodes.top()->attach_node(u))
				{
					waiting_nodes.pop();
				}
				if (u->type!=arr) waiting_nodes.push(u);
			}
			else
			{
				if (!root) root = u;
				waiting_nodes.push(u);
			}
		}
		assert(root);
		return root;
	};
	
	Node* roota = parse(a);
	Node* rootb = parse(b);

	auto gather_free = [&](this auto gather_free, Node* u, vector<int>& res)
	{
		if (u->type==arr)
		{
			res.insert(res.end(), all(u->content));
			return;
		}
		if (u->lc) gather_free(u->lc, res);
		if (u->rc) gather_free(u->rc, res);
	};

	auto is_monotone = [&](vector<int>& s)
	{
		bool good = 1;
		repe(v, s) good &= v == s[0];
		return good;
	};

	auto gather = [&](this auto gather, Node* u, vector<Node*>& res)
	{
		if (u->type == shuffled)
		{
			vector<int> gathering;
			gather_free(u, gathering);
			Node* u = new Node();
			sort(all(gathering));
			u->type = is_monotone(gathering) ? arr : shuffled;
			u->content = gathering;
			res.push_back(u);
			return;
		}
		if (u->type==sorted)
		{
			vector<int> gathering;
			gather_free(u, gathering);
			sort(all(gathering));
			u->type = arr;
			u->content = gathering;
			res.push_back(u);
			return;
		}
		if (u->type==arr)
		{
			res.push_back(u);
			return;
		}
		if (u->lc) gather(u->lc, res);
		if (u->rc) gather(u->rc, res);
	};
	vector<Node*> resa, resb;
	gather(roota, resa);
	gather(rootb, resb);

	auto normalize = [&](vector<Node*> nodes)
	{
		vector<Node*> res;
		res.push_back(nodes[0]);
		repp(i, 1, sz(nodes))
		{
			Node* u = nodes[i];
			if (u->type==arr)
			{
				if (res.back()->type == arr)
				{
					res.back()->content.insert(res.back()->content.end(), all(u->content));
				}
				else
				{
					res.push_back(u);
				}
			}
			else
			{
				if (res.back()->type == arr)
				{
					res.push_back(u);
				}
				else
				{
					res.push_back(u);
				}
			}
		}


		return res;
	};

	resa = normalize(resa);
	resb = normalize(resb);

	bool equal = 1;
	if (sz(resa) != sz(resb))
	{
		equal = 0;
	}
	else
	{
		rep(i, sz(resa))
		{
			equal &= resa[i]->content == resb[i]->content;
			equal &= resa[i]->type == resb[i]->type;
		}
	}

	cout << (equal ? "equal" : "not equal") << '\n';

	return 0;
}
