#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

int buffer = 20000;
struct UF
{
	vi par;
	vi size;
	int p;
	UF(int n) : par(n + buffer), size(n + buffer, 1), p(n)
	{
		rep(i, n + buffer)par[i] = i;
	}
	int addnode() { return p++; }
	int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
	void merge(int a, int b)
	{
		a = find(a); b = find(b);
		if (a == b) return;
		if (size[a] < size[b]) swap(a, b);
		par[b] = a;
		size[a] += size[b];
	}
};

map<string, int> nameind;
struct Node
{
	int isterminal;
	map<char, Node*> children;
	int ufnode;

	Node() : isterminal(-1), ufnode(-1) {}

	void insert(string& s, int ind, int whoami)
	{
		if (ind == s.size())
		{
			isterminal = whoami;
			return;
		}
		if (ind == 3) return;
		if (children[s[ind] - 'a'] == nullptr) children[s[ind] - 'a'] = new Node();
		children[s[ind] - 'a']->insert(s, ind + 1, whoami);
	}

	void addedges(UF& uf, string& s, int par, int ind)
	{
		if (ind == s.size()) return;
		if (par == -1 && ind == 3)
		{
			if (ufnode == -1) par = ufnode = uf.addnode();
			else par = ufnode;
		}
		if (par == -1 && isterminal != -1) par = isterminal;
		if (par != -1) uf.merge(par, nameind[s]);
		if (children[s[ind] - 'a'] != nullptr) children[s[ind] - 'a']->addedges(uf, s, par, ind + 1);
	}
};

signed main()
{
	fast();

	//ifstream in("C:\\Users\\Matis\\Desktop\\comp_prog\\x64\\debug\\in.txt");
	//cin.rdbuf(in.rdbuf());

	int n;
	cin >> n;

	UF uf(n * 2);
	vector<p2> neg;
	Node* root = new Node();
	vector<string> words;
	rep(i, n)
	{
		string a, _, b;
		cin >> a >> _ >> b;
		reverse(all(a));
		reverse(all(b));
		if (nameind.find(a) == nameind.end())nameind[a] = nameind.size();
		if (nameind.find(b) == nameind.end())nameind[b] = nameind.size();
		root->insert(a, 0, nameind[a]);
		root->insert(b, 0, nameind[b]);
		words.emplace_back(a);
		words.emplace_back(b);
		if (_ == "is")
		{
			uf.merge(nameind[a], nameind[b]);
		}
		else
		{
			neg.emplace_back(nameind[a], nameind[b]);
		}
	}
	repe(w, words) root->addedges(uf, w, -1, 0);

	bool consistent = 1;
	repe(no, neg) consistent &= uf.find(no.first) != uf.find(no.second);
	cout << (consistent ? "yes" : "wait what?");

	return 0;
}
