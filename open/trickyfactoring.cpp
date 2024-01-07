#pragma GCC optimize("Ofast,inline,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")

#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#define enablell 1

typedef long long ll;
typedef unsigned long long ull;
#if enablell
#define int ll
#define inf int(1e18)
#else
const int inf = int(2e9);
#endif
typedef vector<ull> vull;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
typedef pair<int, int> p2;
typedef vector<p2> vp2;
typedef vector<vp2> vvp2;
typedef vector<vvp2> vvvp2;
typedef tuple<int, int, int> p3;
typedef vector<p3> vp3;
typedef vector<vp3> vvp3;
typedef vector<vvp3> vvvp3;
typedef tuple<int, int, int, int> p4;
typedef vector<p4> vp4;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)

#define _LOCAL _MSC_VER > 0
#if _LOCAL

#define assert(x) debassert(x)
#define popcount(x) __popcnt(x)
uint32_t ctz(uint32_t x) { return _tzcnt_u32(x); }
#else
#define popcount(x) __builtin_popcountll(x)
uint32_t ctz(uint32_t x) { return __builtin_ctzll(x); }

#if 0
namespace pbds
{
	using namespace __gnu_pbds;

	template<typename T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
	template<typename T, typename U> using indexed_map = tree<T, U, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

	struct chash { // large odd number for C
		const uint64_t C = ll(4e18 * acos(0)) | 71;
		ll operator()(ll x) const { return __builtin_bswap64(x * C); }
	};
	template<typename T, typename U> using fast_map = __gnu_pbds::gp_hash_table<T, U, chash>;
	template<typename T> using fast_set = __gnu_pbds::gp_hash_table<T, null_type, chash>;
	template<typename T, typename H> using fast_set_h = __gnu_pbds::gp_hash_table<T, null_type, H>;
}
using namespace pbds;
#endif
#endif

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
#define FAST_INPUT 0
#if FAST_INPUT && !_LOCAL
#define gc() getchar_unlocked()
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) && c != ' ' && c != '\n') { if (c == EOF) { v = -1; return; } v *= 10; v += c - '0'; } v *= sign; }
inline void read(int& u, int& v) { read(u); read(v); }
inline void read(int& u, int& v, int& k) { read(u); read(v); read(k); }
//inline void read(int& v) { char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } }
inline void read(string& s) { char c; while ((c = gc()) != EOF && c != '\n' && c != ' ') { s.push_back(c); } }
inline void readline(string& s) { char c; while ((c = gc()) != EOF && c != '\n') { s.push_back(c); } }
#else
template <typename T> inline void read(T& a) { cin >> a; }
inline void read(p2& a) { cin >> a.first >> a.second; }
#endif

#define quit cout << flush; _Exit(0);
void readinput() {} // Recursion base case
template<typename T, typename... Args> void readinput(T& arg, Args&... args) { read(arg); readinput(args...); }
#define dread(type, ...) type __VA_ARGS__; readinput(__VA_ARGS__);
template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (T& u : v) read(u); return is; }
#define _ << " " <<

#ifdef _DEBUG
#define noop cout << "";
#define deb __debugbreak();
#define debassert(expr) if(!(expr)) deb;
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
#define debif(expr) ;
#define debassert(expr) ;
#endif

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))

#define ceildiv(x,y) ((x + y - 1) / y)
ll binpow(ll a, ll b) { ll res = 1; while (b > 0) { if (b & 1) res = res * a; a = a * a; b >>= 1; } return res; }
ll binpow(ll a, ll b, ll m) { a %= m; long long res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1; } return res; } // For a < 2^31

template <typename T, typename U> inline void operator+=(pair<T, U>& l, const pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator+(const pair<T, U> l, const pair<T, U> r) { return { l.first + r.first, l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator-(const pair<T, U> l, const pair<T, U> r) { return { l.first - r.first, l.second - r.second }; }
template <typename T, typename U> inline pair<T, U> operator*(const pair<T, U> l, const int m) { return { l.first * m, l.second * m }; }
vector<string> split(string s, string d) { size_t k = 0, n, e = d.length(); string t; vector<string> r; while ((n = s.find(d, k)) != string::npos) { t = s.substr(k, n - k); k = n + e; r.push_back(t); } r.push_back(s.substr(k)); return r; }

#if 1
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]
#endif
const ll mod = 1e9 + 7;
vp2 dirs = { {0,1},{0,-1},{1,0},{-1,0} };

// Also has modmul

// Slow version for msvc. both compute a*b%k, which is hard if a*b>2^63
#if _LOCAL
const int bits = 1;
// if all numbers are less than 2^k, set bits = 64-k
const ull po = 1ULL << bits;
ull modmul(ull a, ull b, ull c) {
	ull x = a * (b & (po - 1)) % c;
	while ((b >>= bits) > 0) {
		a = (a << bits) % c;
		x += (a * (b & (po - 1))) % c;
		x %= c;
	}
	return x % c;
}

#else
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
#endif
// b^e % mod
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 },
		s = ctz(n - 1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a % n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n - 1 && i != s) return 0;
	}
	return 1;
}
ull pollard(ull n) {
	auto f = [n](ull x) { return modmul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || gcd(prd, n) == 1) {
		if (x == y) x = ++i, y = f(x);
		if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
		x = f(x), y = f(f(y));
	}
	return gcd(prd, n);
}
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (isPrime(n)) return { n };
	ull x = pollard(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(), all(r));
	return l;
}
// Helper function
void setDivisors(ull n, ull i, vector<ull>& divisors, vector<pair<ull, ull>>& factors) {
	ull j, x, k;
	for (j = i; j < factors.size(); j++) {
		x = factors[j].first * n;
		for (k = 0; k < factors[j].second; k++) {
			divisors.push_back(x);
			setDivisors(x, j + 1, divisors, factors);
			x *= factors[j].first;
		}
	}
}
// Get all factor from a list of primes
vector<ull> getDivisors(vector<ull> primes)
{
	unordered_map<ull, ull> primeCount;
	repe(prime, primes) primeCount[prime]++;
	vector<pair<ull, ull>> factorCount;
	repe(p, primeCount) factorCount.emplace_back(p);
	vector<ull> ret;
	setDivisors(1, 0, ret, factorCount);
	ret.push_back(1);
	return ret;
}

int32_t main()
{
	fast();

#if 0 && _LOCAL
	ifstream instream("C:\\users\\matis\\source\\repos\\comp_prog\\x64\\debug\\in.txt");
	cin.rdbuf(instream.rdbuf());
#endif



	dread(int, aa, bb);

	vull a = factor(aa);
	vull b = factor(bb);

	map<int, int> divcnt;
	repe(v, a) divcnt[v]++;
	repe(v, b) divcnt[v]++;

	int ans = 1;
	repe(v, divcnt) ans *= v.second + 1;

	cout << (ans + 1) / 2 * 2;

	quit;
}