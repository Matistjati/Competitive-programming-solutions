#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct rational
{
	int a, b;
	rational(int a, int b) : a(a), b(b)
	{
		assert(b != 0);
		normalize();
	}

	rational operator+(const rational& other) const
	{
		int l = lcm(b, other.b);
		return rational(a * l / b + other.a * l / other.b, l);
	}
	
	rational operator-(const rational& other) const
	{
		int l = lcm(b, other.b);
		return rational(a * l / b - other.a * l / other.b, l);
	}
	
	rational operator*(const rational& other) const
	{
		return rational(a * other.a, b * other.b);
	}
	
	rational operator/(const rational& other) const
	{
		return *this*rational(other.b,other.a);
	}

	bool operator<(const rational& other) const
	{
		return a * other.b < other.a* b;
	}
	
	bool operator==(const rational& other) const
	{
		return a==other.a&&b==other.b;
	}

	void normalize()
	{
		int g = gcd(a, b);
		a /= g;
		b /= g;
		if (b < 0) // Make the denominator positive
		{
			a = -a;
			b = -b;
		}
	}
};


typedef multiset<rational> state;
int gethash(state& s)
{
	int b = 1;
	const int mod = int(1e9 + 7);
	int h = 0;
	repe(u, s)
	{
		h = (h + u.a * b) % mod;
		b *= 23756237;
		h = (h + u.b * b) % mod;
		b *= 23756237;
	}
	h = (h + sz(s) * b) % mod;
	return h;
}
signed main()
{
	fast();
	
	int c, t;
	cin >> c >> t;
	rational goal = rational(t, 1);
	queue<state> q;
	state start;
	rep(i, c)
	{
		int u;
		cin >> u;
		start.insert(rational(u, 1));
	}
	q.emplace(start);
	unordered_map<int, tuple<int,int,int>> par1;
	par1[gethash(start)] = { -1,-1,-1 };
	unordered_map<int, int> par2;
	par1.reserve(int(1e6));
	par2.reserve(int(1e6));
	
	
	auto process = [&](multiset<rational>& origin, multiset<rational>& p, int i, int j, char op)
	{
		rational res(0,1);
		rational a = *next(origin.begin(), i);
		rational b = *next(origin.begin(), j);
		if (op == '+') res = a+b;
		if (op == '*') res = a*b;
		if (op == '-') res = a-b;
		if (op == '/')
		{
			if (b.a == 0) return;
			res = a/b;
		}
		bool swapped = 0;
		
		origin.erase(origin.find(a));
		origin.erase(origin.find(b));
		origin.insert(res);
		int h = gethash(origin);
		if (par1.find(h)==par1.end())
		{
			par1[h] = { i, j,int(op) };
			par2[h] = gethash(p);
			q.emplace(origin);
		}
		origin.erase(origin.find(res));
		origin.insert(a);
		origin.insert(b);
	};

	while (q.size())
	{
		state c = q.front();
		q.pop();

		if (sz(c)==1&&begin(c)->a==t&&begin(c)->b==1)
		{
			break;
		}

		state copy(c);
		rep(i, sz(c))
		{
			rep(j, sz(c))
			{
				if (i == j) continue;
				process(c, copy, i, j, '+');
				process(c, copy, i, j, '*');
				process(c, copy, i, j, '-');
				process(c, copy, i, j, '/');
			}
		}
	}

	vector<tuple<int, int, int>> ops;
	state SS;
	SS.insert(rational(t, 1));
	int s = gethash(SS);
	while (get<0>(par1[s])!=-1)
	{
		ops.push_back(par1[s]);
		s = par2[s];
	}
	reverse(all(ops));
	multimap<rational, string> sol;
	repe(u, start)
	{
		sol.insert(make_pair(u, to_string(u.a)));
	}

	repe(mov, ops)
	{
		int a, b, op;
		tie(a, b, op) = mov;

		rational res=rational(0,1);
		string news;
		if (op == '+') res = next(sol.begin(), a)->first + next(sol.begin(), b)->first,
			news="("+ next(sol.begin(), a)->second+"+"+ next(sol.begin(), b)->second+")";
		if (op == '*') res = next(sol.begin(), a)->first * next(sol.begin(), b)->first,
			news="("+ next(sol.begin(), a)->second+"*"+ next(sol.begin(), b)->second+")";
		if (op == '-') res = next(sol.begin(), a)->first - next(sol.begin(), b)->first,
			news="("+ next(sol.begin(), a)->second+"-"+ next(sol.begin(), b)->second+")";
		if (op == '/') res = next(sol.begin(), a)->first / next(sol.begin(), b)->first,
			news="("+ next(sol.begin(), a)->second+"/"+ next(sol.begin(), b)->second+")";

		if (a < b) swap(a, b);
		sol.erase(next(sol.begin(), a));
		sol.erase(next(sol.begin(), b));
		sol.insert(make_pair(res, news));
	}
	assert(sz(sol) == 1);
	cout << begin(sol)->second;

	return 0;
}
