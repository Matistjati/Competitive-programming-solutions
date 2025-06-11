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
#define assert(x) if (!(x)) __debugbreak()
#endif

const int BIG = int(3e18 + 20);

inline bool isproductbig(long long num1, long long num2) {
	if (num1 == 0 || num2 == 0)
		return false;

	if (num1 > std::numeric_limits<long long>::max() / num2)
		return true;

	return num1 * num2 > 3e18;
}

struct bigint
{
	int v;
	bigint(int x) : v(x) {}
	bigint() : v(0) {}

	bigint operator+(const bigint& other)
	{
		if (v + other.v >= BIG) return bigint(BIG);
		return bigint(v + other.v);
	}

	bigint operator*(const bigint& other)
	{
		if (isproductbig(v, other.v)) return bigint(BIG);
		return bigint(v * other.v);
	}
};


string include = "#include \"main.hpp\"";

vector<bigint> nodesize;

vi isfile;
vector<string> lines;
vi includelines;
void walk(int layer, int pos)
{
	while (true)
    {
        if (pos < includelines[0] || layer == -1)
        {
            cout << lines[pos] << "\n";
            return;
        }
        if (pos - includelines[0] < nodesize[layer].v)
        {
            pos -= includelines[0];
            layer--;
            continue;
        }

        auto getprev = [&](int mid)
        {
            return mid == 0 ? 0LL : includelines[mid - 1];
        };

        int lo = -1, hi = sz(includelines);
        while (lo + 1 < hi)
        {
            int mid = (lo + hi) / 2;
            int p = pos - includelines[mid] + mid - mid * nodesize[layer].v;

            if (p < nodesize[layer].v)
                hi = mid;
            else
                lo = mid;
        }

        if (hi == sz(includelines))
        {
            int p = pos - includelines.back() + hi - hi * nodesize[layer].v;
            cout << lines[includelines.back() + p] << "\n";
            return;
        }

        int p = pos - includelines[hi] + hi - hi * nodesize[layer].v;
        int middlepart = includelines[hi] - getprev(hi);
        int pp = p + middlepart;

        if (pp < middlepart)
        {
            cout << lines[getprev(hi) + pp] << "\n";
            return;
        }
        else if (p < nodesize[layer].v)
        {
            pos = p;
            layer--;
            continue;
        }
        assert(0);
    }
}

signed main()
{
	fast();

	int n, k, q;
	cin >> n >> k >> q;
	cin.ignore();
	lines.resize(n);
	repe(l, lines) getline(cin, l);

	rep(i, n)
	{
		if (lines[i] == include) includelines.push_back(i);
	}

	int numinclude = 0;
	rep(i, n) numinclude += lines[i] == include;

	if (numinclude == 0)
	{
		while (q--)
		{
			int p;
			cin >> p;
			p--;
			cout << lines[p] << "\n";
		}
		return 0;
	}

	nodesize.push_back(n);
	vector<bigint> nodenuminclude;

	nodenuminclude.push_back(numinclude);

	rep(i, 1000)
	{
		nodesize.push_back(nodesize.back() + nodenuminclude.back() * (n - 1));
		nodenuminclude.push_back(nodenuminclude.back() * numinclude);
	}

	vector<string> before;
	vector<string> after;
	bool crossed = 0;
	rep(i, n)
	{
		if (lines[i] == include)
		{
			crossed = true;
			continue;
		}
		if (crossed) after.push_back(lines[i]);
		else before.push_back(lines[i]);
	}

	while (q--)
	{
		int p;
		cin >> p;
		p--;

		if (numinclude == 1)
		{
			bigint includepos = bigint(sz(before)) * (k + 1);
			if (p < includepos.v)
			{
				cout << before[p % sz(before)] << "\n";
			}
			else
			{
				p -= includepos.v;
				if (p == 0)
				{
					cout << include << "\n";
				}
				else
				{
					p--;
					cout << after[p % sz(after)] << "\n";
				}
			}
		}
		else
		{
			// the first time we don't go leftmost, k will be small

			int first_big = 0;
			while (nodesize[first_big].v != BIG) first_big++;
			int layer = k - 1;
			if (first_big <= layer)
			{
				int delta = layer - first_big;
				if (p < delta * sz(before))
				{
					cout << before[p % sz(before)] << "\n";
					continue;
				}
				p -= delta * sz(before);
				layer = first_big;
				while (p >= includelines[0] && layer != -1)
				{
					if (p - includelines[0] < nodesize[layer].v)
					{
						layer--;
						p -= includelines[0];
					}
					else break;
				}
			}

            assert(layer < 100);
			walk(layer, p);
		}
	}

	return 0;
}
