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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define __builtin_clz __lzcnt
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
	fast();


	int n;
	cin >> n;
	vi nums(n);
	rep(i, n) cin >> nums[i];

	if (n % 3 == 1)
	{
		int v1 = 0;
		rep(i, n - 1) v1 += nums[i];
		v1 -= 2 * nums.back();
		if (n > 4)
		{
			int k = n / 3 - 1;
			rep(i, k)
			{
				v1 -= 3 * nums[3 + i * 3];
			}
		}
		assert(v1 % 3 == 0);
		v1 /= 3;
		//cout << v1 << "\n";
		vi v;
		int k = n / 3;
		int last = v1;
		rep(i, k)
		{
			last = nums[(3 + i*3) % n] - (nums[(2 + i*3) % n] - last);
		}

		vi ans = { last,v1 };
		rep(i, n - 2)
		{
			ans.push_back(nums[(i + 1)] - ans.back() - ans[sz(ans) - 2]);
		}
		rep(i, n) cout << ans[i] << "\n";
	}
	else if (n % 3 == 2)
	{
		int v1 = 0;
		v1 -= nums[1] * 2;
		v1 -= nums[3] * 2;
		int k = n / 3 - 1;
		rep(i, k) v1 -= 2 * nums[6 + i * 3];
		v1 += nums[0];
		v1 += nums.back();
		v1 += nums[2];
		for (int i = 4; i < n - 2; i += 3)
		{
			v1 += nums[i];
			v1 += nums[i + 1];
		}
		assert((-v1) % 3 == 0);
		v1 = -v1 / 3;
		//cout << "v1:" << v1 << "\n";

		k = n / 3;
		int last = v1;
		rep(i, k)
		{
			last = nums[(4 + i*3) % n] - (nums[(3 + i*3) % n] - last);
		}
		//cout << "l: " << last;
		vi ans = { last, nums[1] - last - v1,v1 };
		rep(i, n - 3)
		{
			ans.push_back(nums[(i + 2)] - ans.back() - ans[sz(ans) - 2]);
		}
		rep(i, n) cout << ans[i] << "\n";
	}
	else
	{
		int v0_lb = 0;
		int v1_lb = 0;

		
		rep(i, n)
		{
			int t = 0;
			int k = 1;
			bool early = 0;
			rep(j, i+1)
			{
				if (k + 1 >= n)
				{
					early = 1;
					break;
				}
				t -= nums[k];
				t += nums[k + 1];
				k += 3;
			}
			if (early) break;
			v0_lb = max(v0_lb, -t);
		}
		rep(i, n)
		{
			int t = 0;
			int k = 2;
			bool early = 0;
			rep(j, i+1)
			{
				if (k + 1 >= n)
				{
					early = 1;
					break;
				}
				t -= nums[k];
				t += nums[k + 1];
				k += 3;
			}
			if (early) break;
			v1_lb = max(v1_lb, -t);
		}

		
		while (true)
		{
			vi ans = { v0_lb,v1_lb};
			rep(i, n - 2)
			{
				ans.push_back(nums[(i + 1)] - ans.back() - ans[sz(ans) - 2]);
				if (ans.back() < 0) goto end;
			}
			rep(i, n) cout << ans[i] << "\n";

			break;
		end:;
		}
	}

	return 0;
}
