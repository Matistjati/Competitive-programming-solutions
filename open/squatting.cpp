#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e6);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

const constexpr int mod = 1 << 30;
const constexpr int modv = mod - 1;

typedef unsigned long long ull;
inline ull sub(ull a, ull b)
{
	b &= modv;
	return a + mod*(a<b) - b;
}
signed main()
{
	fast();


	auto getbases = [](int b)
	{
		ull k = 1;
		rep(i, 20) k = (k * b) & modv;
		vector<ull> bases(int(3e6));
		bases[0] = k;
		repp(i, 1, sz(bases)) bases[i] = (bases[i - 1] * b) & modv;
		return bases;
	};

	vector<ull> b1 = getbases(153);
	vector<ull> b2 = getbases(2347);

	auto gethash = [](string& s, vector<ull>& base)
	{
		ull h = 0;
		rep(i, sz(s)) h = (h + s[i] * base[i]) & modv;
		return h;
	};

	int n;
	cin >> n;
	vector<string> strings(n);
	unordered_map<int, int> count;
	count.reserve(int(5e6));
	rep(_, n)
	{
		string s;
		cin >> s;
		strings[_] = s;
		ull h1 = gethash(s, b1);
		ull h2 = gethash(s, b2);
		rep(i, sz(s))
		{
			ull ha = sub(h1, s[i] * b1[i]);
			ha = (ha + '$' * b1[i]) & modv;
			ull hb = sub(h2, s[i] * b2[i]);
			hb = (hb + '$' * b2[i]) & modv;
			count[ha + (hb << 30)]++;
		}
	}

	repe(s, strings)
	{
		int cnt = 0;
		ull h1 = gethash(s, b1);
		ull h2 = gethash(s, b2);
		rep(i, sz(s))
		{
			ull ha = sub(h1, s[i] * b1[i]);
			ha = (ha + '$' * b1[i]) & modv;
			ull hb = sub(h2, s[i] * b2[i]);
			hb = (hb + '$' * b2[i]) & modv;
			cnt += count[ha+(hb<<30)];
		}
		cout << cnt-sz(s) << "\n";
	}

	return 0;
}
