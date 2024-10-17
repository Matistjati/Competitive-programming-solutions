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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct mintree {
	typedef p2 T;
	static constexpr T unit = p2(inf, inf);
	T f(T a, T b)
	{
		int min1 = inf, min2 = inf;

		for (int val : {a.first, a.second, b.first, b.second}) {
			if (val < min1) {
				min2 = min1; // update second largest
				min1 = val;  // update largest
			}
			else if (val < min2) {
				min2 = val;  // update second largest if it's not the largest
			}
		}

		return p2(min1, min2);
	} // (any associative fn)
	vector<T> s; int n;
	mintree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		e++;
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};
struct maxtree {
	typedef p2 T;
	static constexpr T unit = p2(-inf, -inf);
	T f(T a, T b)
	{
		int max1 = -inf, max2 = -inf;

		for (int val : {a.first, a.second, b.first, b.second}) {
			if (val > max1) {
				max2 = max1; // update second largest
				max1 = val;  // update largest
			}
			else if (val > max2) {
				max2 = val;  // update second largest if it's not the largest
			}
		}

		return p2(max1, max2);
	} // (any associative fn)
	vector<T> s; int n;
	maxtree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		e++;
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

#define FAST_INPUT 1
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


signed main()
{
	fast();

	int n, q;
	read(n), read(q);

	vi nums(n);
	rep(i, n) read(nums[i]);
	gc();

	mintree posmin(n);
	mintree negmin(n);
	maxtree posmax(n);
	maxtree negmax(n);

	rep(i, n)
	{
		if (nums[i]>0)
		{
			posmin.update(i, p2(nums[i], inf));
			posmax.update(i, p2(nums[i], -inf));
		}
		else if(nums[i]<0)
		{
			negmin.update(i, p2(-nums[i], inf));
			negmax.update(i, p2(-nums[i], -inf));
		}
	}

	vi posp(n);
	vi negp(n);
	vi zerop(n);
	rep(i, n)
	{
		if (nums[i] > 0) posp[i]++;
		if (nums[i] < 0) negp[i]++;
		if (nums[i] == 0) zerop[i]++;
	}
	repp(i, 1, n) posp[i] += posp[i - 1];
	repp(i, 1, n) negp[i] += negp[i - 1];
	repp(i, 1, n) zerop[i] += zerop[i - 1];

	auto sum = [](vi& pref, int l, int r)
	{
		if (l) l = pref[l - 1];
		return pref[r] - l;
	};

	while (q--)
	{
		int l, r;
		read(l);
		read(r);
		l--; r--;

		int p = nums[l] * nums[r];
		if (p==0)
		{
			cout << 0 << "\n";
			continue;
		}
		l++;
		r--;
		int ans = -inf;
		if (sum(zerop, l, r) > 0) ans = max(ans, 0LL);
		if (p<0)
		{
			// largest positive, largest abs val negative
			if (sum(posp, l, r) > 0 && sum(negp, l, r) > 0)
			{
				ans = max(ans, p * posmax.query(l, r).first * -negmax.query(l, r).first);
			}
			else if (ans<0)
			{
				// two positive or two negative
				if (sum(posp, l, r) >= 2) // 2 smallest positive
				{
					p2 a = posmin.query(l, r);
					ans = max(ans, p * a.first * a.second);
				}
				if (sum(negp, l, r) >= 2) // 2 smallest abs val negative
				{
					p2 a = negmin.query(l, r);
					ans = max(ans, p * a.first * a.second);
				}
			}
			

			
		}
		else
		{
			// two positive or two negative
			if (sum(posp,l,r)>=2) // 2 largest positive
			{
				p2 a = posmax.query(l, r);
				ans = max(ans, p * a.first * a.second);
			}
			if (sum(negp,l,r)>=2) // 2 largest abs val negative
			{
				p2 a = negmax.query(l, r);
				ans = max(ans, p * a.first * a.second);
			}
			
			if (ans < 0 && sum(posp, l, r) > 0 && sum(negp, l, r) > 0) // smallest positive, smallest abs value negative
			{
				ans = max(ans, p * posmin.query(l, r).first * -negmin.query(l, r).first);
			}
		}
		cout << ans << "\n";
	}

	return 0;
}
