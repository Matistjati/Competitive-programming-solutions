#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
//#include <bits/extc++.h>

using namespace std;

#define enablell 0

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
#define read3(a,b,c) cin >> a >> b >> c
#define write(a) cout << (a) << "\n"
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
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define first(a) (*begin(a))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }


int surveillance(int B, int W, int S[1000][1000], int T[1000][1000]) {

	ll base = (ll)(31);

	vector<int> nums;
	nums.reserve(B * B);
	rep(i, B-W+1)
	{
		rep(j, B-W+1)
		{
			nums.emplace_back(S[i][j]);
		}
	}

	unordered_map<ll,ll> hashes;

	int precompSize = 1000 * 1000 + 1;
	vector<ll> powtable(precompSize);
	ll m = 1;
	rep(i, precompSize)
	{
		powtable[i] = m;
		m *= base;
	}

	vector<vector<ll>> rows(B - W + 1,vector<ll>(B));
	vector<vector<ll>> cols(B - W + 1,vector<ll>(B));

	rep(i, B)
	{

		ll hashV = 0;

		int ind = B - (B - W)-1;
		perr(j, B-W, B)
		{
			hashV += powtable[ind] * S[i][j];
			ind--;
		}
		ind = B - (B - W) - 1;

		rows[B-W][i] = hashV;

		per(j, B-1)
		{
			if (B - W - (B - 1 - j) < 0) break;
			hashV -= S[i][j + 1]*powtable[ind];
			hashV *= base;
			hashV += S[i][j-W + 1];
			rows[B-W-(B-1-j)][i] = hashV;
		}
	}

	rep(j, B)
	{

		ll hashV = 0;

		int ind = (W*W-W);
		perr(i, B - W, B)
		{
			hashV += powtable[ind] * S[i][j];
			ind-=W;
		}
		ind = W*W-W;

		cols[B - W][j] = hashV;

		per(i, B - 1)
		{
			if (B - W - (B - 1 - i) < 0) break;
			hashV -= S[i+1][j] * powtable[ind];
			hashV *= powtable[W];
			hashV += S[i-W+1][j];
			cols[B - W - (B - 1 - i)][j] = hashV;
		}
	}


	// B security size
	rep(i, B-W+1)
	{
		ll hashV = 0;
		ll m = 1;

		rep(k, W)
		{
			hashV += rows[B-W][i + k] * m;
			m *= powtable[W];

		}

		hashes[hashV]++;

		rep(j, B-W)
		{
			hashV -= cols[i][B - j-1]*powtable[W-1];

			hashV *= base;
			hashV += cols[i][B - j - 1 - W];
			hashes[hashV]++;
		}
	}


	ll hashV = 0;
	m = 1;
	ll mul = 0;
	rep(k, W)
	{
		rep(l, W)
		{
			hashV += m * (T[k][l]);
			mul += m;
			m *= base;
		}
	}

	ll matches = 0;
	repe(num, nums)
	{
		ll hashW = hashV + (num-T[0][0]) * mul;
		matches += hashes[hashW];
		hashes[hashW] = 0;
	}


	return matches;
}


//
//int32_t main() {
//	ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
//	dread2(int, B, W);
//	int S[1000][1000], T[1000][1000];
//	rep(i, B) rep(j, B) read(S[i][j]);
//	rep(i, W) rep(j, W) read(T[i][j]);
//
//	printf("%d\n", surveillance(B, W, S, T));
//}

//int32_t main()
//{
//    fast();
//
//#if 0
//    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
//#endif
//
//
//    quit;
//}