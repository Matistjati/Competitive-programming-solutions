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
#include <__msvc_int128.hpp>
typedef _Signed128 big_signed;
typedef _Unsigned128 big_unsigned;
#else
typedef __int128_t big_signed;
typedef __uint128_t big_unsigned;
#endif

typedef uint64_t ull;
struct H {
	ull x; H(ull x = 0) : x(x) {}
	H operator+(H o) { return x + o.x + (x + o.x < x); }
	H operator-(H o) { return *this + ~o.x; }
	H operator*(H o) {
		auto m = (big_unsigned)x * o.x;
		return H((ull)m) + (ull)(m >> 64);
	}
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (ll)1e11 + 3; // (order ~ 3e9; random also ok)

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(const string& str) : ha(sz(str) + 1), pw(ha) {
		pw[0] = 1;
		rep(i, sz(str))
			ha[i + 1] = ha[i] * C + str[i],
			pw[i + 1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

HashInterval hs("asd");
HashInterval ht("asd");
string s, t;
int dp[302][302];
int possible(int i, int j)
{
	if (i==sz(s))
	{
		return j == sz(t);
	}
	if (j == sz(t)) return 1;
	int& v = dp[i][j];
	if (v != -1) return v;

	if (possible(i + 1, j)) return 1;
	repp(k, 1, 302)
	{
		if (j + k > sz(t)) break;
		if (i + k > sz(s)) break;

		repp(l, 1, 302)
		{
			if (j + k * l > sz(t)) break;
			if (hs.hashInterval(i, i + k) != ht.hashInterval(j + k * (l - 1), j + k * l)) break;
			if (possible(i + k, j + k * l)) return 1;
		}
	}
	return dp[i][j] = 0;
}

signed main()
{
    fast();

	memset(dp, -1, sizeof(dp));
	int n, m;
	cin >> n >> m;
	cin >> s >> t;
	hs = HashInterval(s);
	ht = HashInterval(t);
	cout << (possible(0, 0)?"yes":"no");

    return 0;
}
