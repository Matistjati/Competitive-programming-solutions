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
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define __builtin_popcount popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

struct rational
{
	int a, b;
	rational operator+(rational other)
	{
		int l = lcm(b, other.b);
		return rational(a * l / b + other.a * l / other.b, l);
	}
	rational operator*(rational other)
	{
		return rational(a * other.a, b * other.b);
	}
	rational operator/(rational other)
	{
		return *this * rational(other.b, other.a);
	}
	rational(int x, int y)
	{
		int g = gcd(x, y);
		a = x / g;
		b = y / g;
	}
};

signed main()
{
	fast();

	int t;
	cin >> t;
	while (t--)
	{
		int n, k, a, b;
		cin >> n >> k >> a >> b;
		int v = b * n / a - n;
		if (v <= 0)
		{
			cout << "-1\n";
			continue;
		}

		rational d = rational({ b,a }) + rational(-1, 1);
		d = rational(d.b, d.a);
		int ans = 0;
		// runs in t*sqrt(1e9). each loop iteration, v increases by 1
		// 1+2+3+4+5+6+7...+x=1e9 => x ~ sqrt(1e9)
		while (k > 0)
		{
			int v = b * n / a - n;

			// result of simplifying multiple expressions
			// basically answers the question: what is the smallest integer delta > n s.t. v(delta)>v(n)
			int delta = ((n*d.b / d.a + 1) * d.a + d.b - 1) / d.b - n;
			int numrounds = (delta + v - 1) / v;
			if (numrounds * v >= k)
			{
				ans += (k + v - 1) / v;
				break;
			}
			k -= v * numrounds;
			n += v * numrounds;
			ans += numrounds;
		}
		cout << ans << "\n";
	}

	return 0;
}
