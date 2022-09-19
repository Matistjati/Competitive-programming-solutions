#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>

using namespace std;

#define enablell 0

typedef long long ll;
#if enablell
#define int ll
#define inf LLONG_MAX
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

//#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define read3(a,b,c) cin >> a >> b >> c
//#define write(a) cout << (a) << "\n"
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
#define indexpair(p, i) ((i==0)?p.first:p.second)
#define chmax(a,b) ((a)=max((a),b))
#define chmin(a,b) ((a)=min((a),b))

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
inline int readintsigned() { int v = 0; int sign = 1; char c = getchar(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v * sign; }
inline int readint() { int v = 0; char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v; }
inline string readstring() { string s; char c; while ((c = getchar()) != EOF && c != '\n') { s.push_back(c); } return s; }
#if _MSC_VER > 0
#define gc() getchar()
#define popcount(x) __popcnt(x)
#define assert(x) debassert(x)
#else
#define popcount(x) __builtin_popcount(x)
#define gc() getchar_unlocked()
#if 0
#include <bits/extc++.h>
using namespace __gnu_pbds;
#endif
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return x; }
};
//typedef __gnu_pbds::gp_hash_table<int, null_type, chash> h;

#endif

struct Node {
	Node* l = 0, * r = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo, int hi) :lo(lo), hi(hi) {} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo) / 2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo) / 2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
		else if (madd)
			l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
	}
};

#define ld long double
#define pd pair<ld,ld>
#define vpd vector<pd>

inline ld dist(pd a, pd b)
{
	ld x = a.first - b.first;
	ld y = a.second - b.second;
	return sqrt(x*x+y*y);
}

pd lydialast;
pd lydiatarget;
pd shadowlast;
pd shadowtarget;
ld lastt;
ld nexttsha;
ld nexttlyd;

inline pd getpossha(ld x)
{
	ld t = (x - lastt) / (nexttsha - lastt);
	pd posb = mp(shadowlast.first + t * (shadowtarget.first - shadowlast.first), shadowlast.second + t * (shadowtarget.second - shadowlast.second));
	return posb;
}

inline pd getposlyd(ld x)
{
	ld t = (x - lastt) / (nexttlyd - lastt);
	pd posa = mp(lydialast.first + t * (lydiatarget.first - lydialast.first), lydialast.second + t * (lydiatarget.second - lydialast.second));
	return posa;
}

ld f(ld x)
{
	pd posa = getpossha(x);
	pd posb = getposlyd(x);
	return dist(posa, posb);
}

ld ternSearch(ld a, ld b) {
	assert(a <= b);
	rep(i,50)
	{
		ld m1 = a + (b - a) / 3, m2 = b - (b - a) / 3;

		if (f(m1) > f(m2)) a = m1; // (A)
		else b = m2;
	}
	//rep(i, a + 1, b + 1) if (f(a) > f(i)) a = i; // (B)
	return a;
}

void doit()
{
	for (float i = lastt; i < min(nexttlyd, nexttsha); i += 0.1)
	{
		cout << "i: "<< i << ", f(i): " << f(i) << "\n";
	}
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\joshua.jeffmarander\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif


	dread(int, n);
	vpd sha(n);
	rep(i, n)
	{
		cin >> sha[i].first;
		cin >> sha[i].second;
	}

	dread(int, m);
	vp2 lyd(m);
	rep(i, m)
	{
		cin >> lyd[i].first;
		cin >> lyd[i].second;
	}



	shadowlast = sha[0];
	lydialast = lyd[0];
	shadowtarget = sha[1];
	lydiatarget = lyd[1];

	int lydi = 1;
	int shai = 1;

	lastt = 0;
	ld ans = inf;

	while (true)
	{
		nexttsha = dist(shadowlast, shadowtarget)+lastt;
		nexttlyd = dist(lydialast, lydiatarget)+lastt;
		ld upper = min(nexttsha, nexttlyd);
		ld bestx = ternSearch(lastt, upper);
		ans = min(ans, f(bestx));

		if (abs(nexttsha-nexttlyd)<0.0001)
		{
			shai++;
			lydi++;
			if (shai == n||lydi==m)
			{
				break;
			}
			shadowlast = shadowtarget;
			shadowtarget = sha[shai];
			lydialast = lydiatarget;
			lydiatarget = lyd[lydi];
		}
		else if (nexttsha<nexttlyd)
		{
			// Shadow at new
			shai++;
			if (shai==n)
			{
				break;
			}
			shadowlast = shadowtarget;
			shadowtarget = sha[shai];
			lydialast = getposlyd(upper);
		}
		else
		{
			lydi++;
			if (lydi == m)
			{
				break;
			}
			lydialast = lydiatarget;
			lydiatarget = lyd[lydi];
			shadowlast = getpossha(upper);
		}
		lastt = upper;
	}
	cout << setprecision(15) << ans;

    quit;
}