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
#define FILE_TC 0
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
const ll mod = 1e9 + 7;
vp2 dirs = { {0,1},{0,-1},{1,0},{-1,0}, {0,0} };

const int MAX_PR = 31622786;
bitset<MAX_PR> isprime;
vi eratosthenesSieve(int lim = MAX_PR - 1) {
	isprime.set(); isprime[0] = isprime[1] = 0;
	for (int i = 4; i < lim; i += 2) isprime[i] = 0;
	for (int i = 3; i * i < lim; i += 2) if (isprime[i])
		for (int j = i * i; j < lim; j += i * 2) isprime[j] = 0;
	vi pr;
	repp(i, 2, lim) if (isprime[i]) pr.push_back(i);
	return pr;
}

const int target = int(2e9 + 10);

int32_t main()
{
	fast();

#if 1

	set<int> primes = { 105, 1419, 15387, 31929, 207177, 287979, 507579, 1485609, 2089257, 8413179, 10235499, 18651417, 20138379, 32812089, 44544219, 65237577, 68633979, 87393129, 134574729, 176116299, 210509529, 265786107, 320237979, 392605449, 426689979, 513769209, 790296729, 826048329, 959646507, 1129119819, 1244556249, 1637505339, 1885, 114985, 4505, 25085, 54205, 126893905, 448585, 1073305, 3077705, 3973085, 6253085, 8712985, 9271805, 15411785, 26000605, 37605385, 46999705, 72457085, 84280585, 100085785, 162913085, 213701405, 237646105, 290770505, 572905085, 656960585, 770382685, 781296905, 995762585, 1075122185, 1158590105, 1276450585, 1518477085, 1641183305, 1729, 5719, 27559, 233569, 982513, 3812599, 4293793, 4813879, 6622609, 8835799, 13534129, 22549639, 25711399, 32894743, 34878529, 41305159, 48476449, 59267089, 71550913, 96931639, 221042353, 249925249, 257519143, 265265329, 306333559, 332898769, 644074039, 732641959, 1414608769, 1614365473, 1640582839, 1667082529, 24211, 3655861, 1136972771, 59081, 23691481, 208681, 336611, 872159101, 1012121, 2263811, 3506371, 9773731, 14662681, 16596371, 31852931, 79796761, 127090931, 170383081, 372526121, 458576371, 578178931, 599938361, 994732211, 1191610211, 1262588371, 1412889731, 1659996371, 1748351011, 1793680361, 1886676121, 353977, 662998921, 1242709, 54177877, 71657209, 78225589, 167195509, 323476777, 378606709, 418637557, 483824809, 1306276309, 1539866809, 1640591017, 6985249, 38596273, 92458529, 197916193, 272174369, 1813376689, 7558219, 161164441, 1006956091, 7355239, 35347159, 43055057, 72730439, 291335089, 321767447, 1449600967, 20771801, 342116741, 2953711, 8444431, 34179391, 1164151711, 1615067791, 1743564961, 294409, 5069629, 76724569, 185245273, 222931549, 559874269, 1017436249, 19827641, 428108921, 668997041, 1715605681, 8011459, 49982899, 69207769, 92835667, 240479779, 671405827, 1007749849, 1140806899, 18578113, 1495619759, 26758057, 130692329, 1268239597, 4648261, 268578181, 1020225061, 1674819721, 6173179, 266032009, 7355671, 18175361, 104966471, 1102226791, 970578289, 367224619, 627977681, 269545249, 1826139169, 52691801, 55902529, 199708657, 976228129, 133800661, 42501439, 212122639, 375615073, 607692079, 667235531, 1455928891, 53399449, 763651289, 177055201, 1023780151, 1151271109, 1743855049, 96916279, 856970353, 953055097, 1056066169, 1324715137, 820192231, 56052361, 195850411, 939947009, 118901521, 443880589, 172947529, 604611019, 1586031409, 216821881, 758056531, 228842209, 873571459, 1348964401, 1675383631, 1299963601 };
	//set<int> primes = { 105, 1885, 114985, 4505, 1729, 5719, 27559, 24211, 3655861, 1136972771, 59081, 23691481, 208681, 336611, 872159101, 1012121, 353977, 662998921, 1242709, 6985249, 7558219, 7355239, 35347159, 43055057, 72730439, 20771801, 342116741, 2953711, 8444431, 34179391, 294409, 5069629, 76724569, 185245273, 222931549, 559874269, 1017436249, 19827641, 428108921, 668997041, 1715605681, 8011459, 49982899, 69207769, 92835667, 240479779, 671405827, 1007749849, 1140806899, 18578113, 1495619759, 26758057, 130692329, 1268239597, 4648261, 268578181, 1020225061, 1674819721, 6173179, 266032009, 7355671, 18175361, 104966471, 1102226791, 970578289, 367224619, 627977681, 269545249, 1826139169, 52691801, 55902529, 199708657, 976228129, 133800661, 42501439, 212122639, 375615073, 607692079, 667235531, 1455928891, 53399449, 763651289, 177055201, 1023780151, 1151271109, 1743855049, 96916279, 856970353, 953055097, 1056066169, 1324715137, 820192231, 56052361, 195850411, 939947009, 118901521, 443880589, 172947529, 604611019, 1586031409, 216821881, 758056531, 228842209, 873571459, 1348964401, 1675383631, 1299963601 };
	//vi primes = { 105, 735, 5145, 36015, 252105, 1764735, 12353145, 86472015, 605304105, 1419, 61017, 2623731, 112820433, 15387, 3431301, 765180123, 31929, 11717943, 207177, 287979, 507579, 1485609, 2089257, 8413179, 10235499, 1885, 54665, 1585285, 45973265, 1333224685, 4505, 238765, 12654545, 670690885, 25085, 4339705, 750768965, 54205, 15882065, 448585, 1073305, 3077705, 3973085, 6253085, 8712985, 9271805, 1729, 32851, 624169, 11859211, 225325009, 5719, 245917, 10574431, 454700533, 27559, 3499993, 444499111, 233569, 127762243, 982513, 3812599, 4293793, 4813879, 6622609, 8835799, 24211, 1718981, 122047651, 59081, 7739611, 1013889041, 208681, 64899791, 336611, 145079341, 1012121, 2263811, 3506371, 9773731, 353977, 132033421, 1242709, 6985249, 7558219, 7355239, 2953711, 8444431, 294409, 32090581, 5069629, 8011459, 4648261, 6173179, 7355671 };
	dread(int, t);
	while (t--)
	{
		dread2(int, lo, hi);
		int ans = 0;
		repe(p, primes) ans += (p >= lo && p <= hi);
		cout << ans << "\n";
	}
#else
	vi primes = eratosthenesSieve();

	rep(i, primes.size())
	{
		repp(j, i + 1, primes.size())
		{
			int x = primes[i];
			int y = primes[j];
			if ((y - x) % (x - 1) != 0) continue;
			int a = (y - x) / (x - 1);
			int b = x - a;
			debif(a == 1 && y == 2);
			//if (b < 0) continue;

			int cnt = 0;
			int xy = 1;
			int last = 1;
			while (1)
			{

				last = a * last + b;
				if (last >= isprime.size())
				{
					//assert(xy * last > target);
					break;
				}
				if (!isprime[last]) break;
				xy *= last;
				if (xy > target) break;

				cnt++;
				if (cnt >= 3) cout << xy << ", ";
				//if (cnt>=3) cout << a << " " << b << " " << xy << "\n";
			}
			//if (x*y<5000&&isprime[x*y]) cout << 1 << " " << x << " " << y << " " << x * y << "\n";
		}
		//cout << i << "\n";
	}
#endif

	quit;
}
