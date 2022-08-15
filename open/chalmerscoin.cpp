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

static const unsigned char byteswap[] = {
		0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
		0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
		0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
		0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
		0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
		0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
		0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
		0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
		0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
		0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
		0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
		0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
		0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
		0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
		0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
		0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
		0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
		0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
		0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
		0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
		0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
		0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
		0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
		0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
		0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
		0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
		0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
		0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
		0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
		0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
		0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
		0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

inline ULL hashh(ULL X)
{

	vi x(64, 0);
	for (int i = 63; i >= 0; i--) x[63 - i] = (X >> i) & 1;

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
		ULL rev = __builtin_bswap64(k);
		rev = byteswap[rev & 0xFF]
			| ((ULL)byteswap[(rev >> 8) & 0xFF] << 8)
			| ((ULL)byteswap[(rev >> 16) & 0xFF] << 16)
			| ((ULL)byteswap[(rev >> 24) & 0xFF] << 24)
			| ((ULL)byteswap[(rev >> 32) & 0xFF] << 32)
			| ((ULL)byteswap[(rev >> 40) & 0xFF] << 40)
			| ((ULL)byteswap[(rev >> 48) & 0xFF] << 48)
			| ((ULL)byteswap[(rev >> 56) & 0xFF] << 56);

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

	//ULL a = _byteswap_uint64((1ULL<<40)-1);
	rep(i, numbers.size())
	{
		ULL number = 68719476736 * (ULL)numbers[i];
		ULL bestScore = ULLONG_MAX;
		ll bestK = 0;

		while (true)
		{
			rununtil(99 * (i + 1));

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