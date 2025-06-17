#pragma GCC optimize("Ofast")
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

typedef unsigned long long ull;

const int maxv = 11;
const int blocksize = 950;
const int numblocks = (int(1e5) + blocksize - 1) / blocksize;
ull blocks[numblocks][maxv + 1][maxv + 1];


signed main()
{
	fast();

#if _LOCAL
	ifstream in("e:/in.txt");
	cin.rdbuf(in.rdbuf());
#endif

	int n, q;
	cin >> n >> q;
	vector<ull> nums(n);
	rep(i, n) cin >> nums[i];

	// update: O(b*maxv)
	// query: O(n/b*maxv^2)
	ull block[maxv + 1][maxv + 1];
	auto update_block = [&](int b)
		{
			if ((b + 1) * blocksize >= n) return;

			
			memset(block, 0, sizeof(block));

			repp(i, b * blocksize, (b + 1) * blocksize)
			{
				int v = nums[i];

				rep(j, maxv + 1)
				{
					ull val = 1 + block[maxv][j] - block[v][j];
					block[v][j] += val;
					block[maxv][j] += val;
				}
				block[v][v]--;
				block[maxv][v]--;
			}
			rep(i, maxv) rep(j, maxv + 1) blocks[b][i][j] = block[i][j];
		};

	rep(i, numblocks)
	{
		update_block(i);
	}

	ull lastans;
	auto solve = [&]()
		{
			ull dp[maxv];
			memset(dp, 0, sizeof(dp));

			ull newdp[maxv];
			rep(b, n / blocksize)
			{
				rep(i, maxv)
				{
                    ull t = 0;
					#pragma GCC ivdep
					rep(j, maxv)
					{
						t += dp[j] * blocks[b][i][j];
					}
					newdp[i] = t + blocks[b][i][maxv];
				}
				rep(j, maxv) dp[j] += newdp[j];
			}

			int base = n / blocksize;
			ull t = 0;
			rep(i, maxv) t += dp[i];
			repp(i, base * blocksize, n)
			{
				ull s = 1 + t - dp[nums[i]];
				dp[nums[i]] = dp[nums[i]] + s;
				t = t + s;
			}
			lastans = 1+t;
			cout << 1 + t << "\n";
		};
	solve();

	
	while (q--)
	{
		int i, v;
		cin >> i >> v;
		i--;

		nums[i] = v;
		update_block(i / blocksize);
		solve();
	}

	return 0;
}
