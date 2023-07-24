#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#define enablell 1

typedef long long ll;
typedef unsigned long long ull;
#if enablell
#define int ll
#define inf int(1e18)
#define float double
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

#define PBDS 0
#define _LOCAL _MSC_VER > 0
#if _LOCAL
#define gc() getchar()
#define popcount(x) __popcnt(x)
#define leading_zeros(x) _lzcnt_u32(x)
uint32_t clz(uint32_t x) { return _lzcnt_u32(x); }
uint32_t ctz(uint32_t x) { return _tzcnt_u32(x); }
#define bswap64(x) _byteswap_uint64(x)
#define assert(x) debassert(x)
#else
#define popcount(x) __builtin_popcount(x)
uint32_t clz(uint32_t x) { return __builtin_clz(x); }
uint32_t ctz(uint32_t x) { return __builtin_ctzll(x); }
#define bswap64(x) __builtin_bswap64(x)
#define gc() getchar_unlocked()
#if PBDS
using namespace __gnu_pbds;
// lower_bound is now upper_bound and vice versa (multiset). generally a bit broken
template<typename T> using indexed_multiset = tree<int, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> using indexed_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};

template<typename T, typename U> using fast_map = __gnu_pbds::gp_hash_table<T, U, chash>;
template<typename T> using fast_set = __gnu_pbds::gp_hash_table<T, null_type, chash>;
template<typename T, typename H> using fast_set_h = __gnu_pbds::gp_hash_table<T, null_type, H>;
#endif

#endif

#define FAST_INPUT 0
#define FILE_TC 1
#if FILE_TC && _LOCAL
//ifstream filein("C:\\users\\matis\\source\\repos\\comp_prog\\x64\\release\\in.txt");
ifstream filein("C:\\users\\matis\\source\\repos\\comp_prog\\x64\\debug\\in.txt");
//ifstream filein("E:\\downloads\\test_data\\test_data\\005-case05.in");
//ifstream filein("E:\\desktop\\po-repos\\swedish-olympiad-2023\\online\\tomtplanering\\data\\secret\\group10\\010-case10.in");

#define cin filein
void fast() {}
#else
inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
#endif

#if FAST_INPUT && (!FILE_TC || !_LOCAL)
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) && c != ' ' && c != '\n') { if (c == EOF) { v = -1; return; } v *= 10; v += c - '0'; } v *= sign; }
inline void read(int& u, int& v) { read(u); read(v); }
inline void read(int& u, int& v, int& k) { read(u); read(v); read(k); }
//inline void read(int& v) { char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } }
inline void read(string& s) { char c; while ((c = gc()) != EOF && c != '\n' && c != ' ') { s.push_back(c); } }
inline void readline(string& s) { char c; while ((c = gc()) != EOF && c != '\n') { s.push_back(c); } }
#else
template <typename T> inline void read(T& a) { cin >> a; }
template <typename T> inline void read(T& a, T& b) { cin >> a >> b; }
template <typename T> inline void read(T& a, T& b, T& c) { cin >> a >> b >> c; }
#endif
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; read(a)
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
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

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))

#define ceildiv(x,y) ((x + y - 1) / y)

template <typename T, typename U> inline void operator+=(pair<T, U>& l, const pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator+(const pair<T, U> l, const pair<T, U> r) { return { l.first + r.first, l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator-(const pair<T, U> l, const pair<T, U> r) { return { l.first - r.first, l.second - r.second }; }
template <typename T, typename U> inline pair<T, U> operator*(const pair<T, U> l, const int m) { return { l.first * m, l.second * m }; }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }
vector<string> split(string s, string d) { size_t k = 0, n, e = d.length(); string t; vector<string> r; while ((n = s.find(d, k)) != string::npos) { t = s.substr(k, n - k); k = n + e; r.push_back(t); } r.push_back(s.substr(k)); return r; }
ll binpow(ll a, ll b) { ll res = 1; while (b > 0) { if (b & 1) res = res * a; a = a * a; b >>= 1; } return res; }
ll binpow(ll a, ll b, ll m) { a %= m; long long res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1; } return res; } // For a < 2^31

#if 1
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]
#endif
//const ll mod = 1e9 + 7;
vp2 dirs = { {0,1},{0,-1},{1,0},{-1,0} };


// No, I'm not proud of this mess
// But I'm not gonna clean it up either, I wanna sleep
// Main idea: generate about 10000 sets of size 1e5-10 and store them in a hashmap (we remove and insert one element to get new set)
// Then generate lots of small set and check for collision. Works well for all n>30, since collisions will be numerous by then
// For smaller n, we have to resort to brute force by using meet in the middle
void doit(int n, int p, vi& nums, int t)
{
	int smallsz = 10;
	if (n < 21) smallsz = n / 2;
	vvb table;
	unordered_map<int, int> hashset;

	vp2 versions;

	auto prep = [&]()
	{
		vi indices(n * 2);
		int v = 1;
		int ind = 0;
		while (ind < n - smallsz)
		{
			indices[ind] = 1;
			v = (v * nums[ind]) % p;
			ind++;
		}
		cerr << "table 1 built in " << elapsedmillis() << "\n";
		//resettimer();

		int k = 50000;
		rep(i, k)
		{
			while (1)
			{
				int a = randint(1, n * 1.5);
				if (!indices[a]) continue;
				v = (v * binpow(nums[a], p - 2, p)) % p;
				int rem = a;
				indices[a] = 0;
				versions.push_back(p2(rem, -1));
				break;
			}


			while (1)
			{
				int a = randint(0, n * 1.5);
				if (indices[a]) continue;
				indices[a] = 1;
				versions.back().second = a;
				v = (v * nums[a]) % p;
				break;
			}

			hashset[v] = versions.size() - 1;
		}
	};
	prep();


	cerr << "table 2 built in " << elapsedmillis() << "\n";
	//resettimer();

	vi choice(n * 2, -1);
	int ver = 0;
	while (1)
	{
		if (elapsedmillis() > 100) return;
		ver++;
		int k = 0;
		int v = 1;
		while (k < smallsz)
		{
			int a = randint(n * 1.5, n * 2 - 1);
			if (choice[a] == ver) continue;
			choice[a] = ver;
			v = (v * nums[a]) % p;
			k++;
		}
		int inv = (t * binpow(v, p - 2, p)) % p;
		if (setcontains(hashset, inv))
		{
			cerr << "won after " << elapsedmillis() << "seconds";
			//resettimer();

			vb ans(n * 2);
			rep(i, n * 2) if (choice[i] == ver) ans[i] = 1;

			int ver = hashset[inv];
			unordered_set<int> indices;
			int ind = 0;
			while (indices.size() < n - smallsz)
			{
				indices.insert(ind);
				ind++;
			}
			rep(i, ver + 1)
			{
				indices.erase(versions[i].first);
				indices.insert(versions[i].second);
			}

			repe(ind, indices)
			{
				ans[ind] = 1;
			}

			int cnt = 0;
			int prod = 1;
			rep(i, n * 2)
			{
				if (ans[i])
				{
					cnt++;
					prod = (prod * nums[i]) % p;
				}
			}

			/*assert(prod == t);
			assert(cnt == n);*/
#if !_LOCAL
			rep(i, ans.size())
			{
				cout << ans[i];
			}
#endif
			quit;
		}

	}
}

int32_t main()
{
	fast();

	dread2(int, n, p);

	readvector(int, nums, n * 2);
	vi orignums = nums;
	dread(int, t);

	if (n <= 12)
	{
		while (true)
		{
			vi chosen(n * 2);
			int k = 0;
			int v = 1;
			while (k < n)
			{
				int a = randint(0, n * 2 - 1);
				if (chosen[a]) continue;
				chosen[a] = 1;
				v = (v * nums[a]) % p;
				k++;
			}

			if (v == t)
			{
				rep(i, n * 2)
				{
					cout << chosen[i];
				}
				quit;
			}
		}
	}
	else if (n <= 20)
	{
		vi l;
		vi r;

		rep(i, n) l.push_back(nums[i]);
		repp(i, n, n * 2) r.push_back(nums[i]);

		unordered_map<int, int> lside;
		rep(mask, 1 << l.size())
		{
			int v = 1;
			rep(i, l.size()) if (mask & (1 << i)) v = (v * l[i]) % p;
			lside[v] = mask;
		}

		rep(mask, 1 << r.size())
		{
			int v = 1;
			rep(i, r.size()) if (mask & (1 << i)) v = (v * r[i]) % p;
			v = (t * binpow(v, p - 2, p)) % p;
			if (setcontains(lside, v) && popcount(mask) + popcount(lside[v]) == n)
			{
				rep(i, l.size())
				{
					if (lside[v] & (1 << i)) cout << "1";
					else cout << "0";
				}
				rep(i, r.size())
				{
					if (mask & (1 << i)) cout << "1";
					else cout << "0";
				}
				quit;
			}

		}



	}
	else
	{
		cerr << "read input " << elapsedmillis() << "\n";
		resettimer();
		while (1)
		{
			resettimer();

			doit(n, p, nums, t);
		}

	}

	quit;
}