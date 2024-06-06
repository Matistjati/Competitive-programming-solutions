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


typedef uint64_t ull;
static int C; // initialized below

// Arithmetic mod two primes and 2^32 simultaneously.
// "typedef uint64_t H;" instead if Thue-Morse does not apply.
template<int M, class B>
struct A {
	int x; B b; A(int x = 0) : x(x), b(x) {}
	A(int x, B b) : x(x), b(b) {}
	A operator+(A o) { int y = x + o.x; return{ y - (y >= M) * M, b + o.b }; }
	A operator-(A o) { int y = x - o.x; return{ y + (y < 0) * M, b - o.b }; }
	A operator*(A o) { return { (int)(1LL * x * o.x % M), b * o.b }; }
	bool operator<(A o) const { return (ull)*this < (ull)o; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;
ull toull(const H a) { return a.x ^ (ull)a.b.x << 21; }


struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str) + 1), pw(ha) {
		pw[0] = 1;
		repp(i, 0, sz(str))
			ha[i + 1] = ha[i] * C + str[i],
			pw[i + 1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

int possible(string& s, string& t)
{
	string r = s;
	reverse(all(r));

	HashInterval hr(r);
	HashInterval hs(s);
	HashInterval ht(t);

	repp(i, 1, sz(s) + 1)
	{
		if (toull(ht.hashInterval(i, sz(t))) == toull(hs.hashInterval(0, sz(t) - i)) &&
			toull(ht.hashInterval(0, i)) == toull(hr.hashInterval(0, i)))
		{
			return i;
		}
	}

	return -1;
}

signed main()
{
	fast();

	void* v = malloc(20);
	C = ((int)v) % 1000000007; // (less than modulo)

	int t;
	cin >> t;
	while (t--)
	{
		int n, k;
		cin >> n >> k;
		string target;
		cin >> target;
		string s1;
		string s2;

		while (sz(s1) < n)
		{
			rep(i, k) s1 += "0";
			rep(i, k) s2 += "1";
			swap(s1, s2);
		}
		int a = possible(s1, target);
		if (a != -1) cout << a << "\n";
		else
		{
			a = possible(s2, target);
			cout << a << "\n";
		}
	}




	return 0;
}
