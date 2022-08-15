#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>

using namespace std;

#define enablell 1

#define ll long long
#if enablell
#define int ll
#define inf 2e18
#define float double
#else
#define inf int(2e9)
#endif
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define p2 pair<int, int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vvvp2 vector<vvp2>
#define p3 tuple<int,int,int>
#define vp3 vector<p3>
#define vvp3 vector<vp3>
#define vvvp3 vector<vvp3>
#define p4 tuple<int,int,int,int>
#define vp4 vector<p4>

#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define write(a) cout << (a) << "\n"
#define writevi(v) rep(_, v.size()) {cout << v[_] << " ";} cout << "\n"
#define writev(v) rep(_, v.size()) {cout << v[_] << "\n";}
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define noop cout << "";
#define deb __debugbreak();
#define debassert(expr) if (!(expr)) deb;
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
#define debassert(expr) ;
#define debif(expr) ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, start, end) for (int i = start; i < end; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define vectorcontains(vec, x) (find(vec.begin(), vec.end(), x) != vec.end())
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
//#define first(a) (*begin(a))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s);  string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }
inline int startswith(const string& s, const string& prefix) { return s.rfind(prefix, 0) == 0; }

inline int readint() { int v = 0; char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v; }

#define _LOCAL _MSC_VER > 0
#if _LOCAL
#define BIGINT unsigned ll
#else
#define BIGINT __int128_t
#endif

#define N 64
#define bset bitset<N>


template<std::size_t K>
void reverse(std::bitset<K>& b) {
	for (std::size_t i = 0; i < K / 2; ++i) {
		bool t = b[i];
		b[i] = b[K - i - 1];
		b[K - i - 1] = t;
	}
}

#define ULL unsigned ll

inline ULL hashh(ULL X)
{

	vi x(64,0);
	for (int i = 63; i >= 0; i--) x[63-i] = (X >> i) & 1;

	vector<int> weirdNumber = { 1, 1, 0, 0, 1, 1, 0, 1 };
	rep(i, 512) {
		ll y = 4 * x[i % 64] + 2 * x[(i + 2) % 64] + x[(i + 10) % 64];
		x[i % 64] = weirdNumber[y];
	}

	unsigned ll k = 0;
	reverse(all(x));
	rep(i, 64) k += x[i] * (1ULL << i);

	rep(i, 16)
	{
		ULL rev = 0;
		ULL n = k;
		for (int i = 63; i >= 0; i--) {
			rev |= (n & 1) << i;
			n >>= 1;
		}
		bool carry = false;
		if (rev > ULLONG_MAX - k) carry = true; // `a + x` would overflow
		k += rev;
		k ^= 12157665459056928801ULL;
		if (carry)
		{
			k = (k >> 1) | (1ULL << 63);
		}
	}

	return k;
}


int32_t main()
{
	fast();

#if 0
	//ifstream cin("C:\\Users\\Christian\\in.txt");
#endif

	ULL lower = 0, higher = 68719476736ULL;
	random_device rd;
	mt19937 rng(rd());
	uniform_int_distribution<ULL> dist(lower, higher);

	vector<ULL> numbers(10);

	rep(i, numbers.size()) {
		dread(ULL, num);
		numbers[i] = num;
	}


	rep(i, numbers.size())
	{
		ULL number = 68719476736 * (ULL)numbers[i];
		ULL bestScore = ULLONG_MAX;
		ll bestK = 0;

		while (true)
		{
			rununtil(99 * (i+1));

			ll k = dist(rng);
			ULL score = hashh(number + k);

			if (score < bestScore)
			{
				bestScore = score;
				bestK = k;
			}
		}

		write((ULL)bestK);
	}

	quit;
}