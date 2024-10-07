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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vi nums(n);
        rep(i, n) cin >> nums[i];

        p2 s = p2(0, n-1);
        rep(i, n)
        {
            s.first = max(s.first, i - nums[i] + 1);
            s.second = min(s.second, i + nums[i] - 1);
        }


        if (s.first <= s.second)
        {
            bool good = 1;
            int l = s.first;
            int r = s.first;


            priority_queue<p2> rq;
            int radd = 0;

            repp(i, l+1, n)
            {
                rq.emplace(-(nums[i] - (i - l)), i);
            }

            int timer = 1;
            while (l > 0 || r < n-1)
            {
                if (sz(rq) && ((-rq.top().first)+radd==timer || l==0))
                {
                    while (r < rq.top().second)
                    {
                        r++;
                        radd++;
                        timer++;
                    }
                    if (timer > nums[rq.top().second]) good = 0;
                    while (sz(rq) && rq.top().second <= r) rq.pop();
                }
                else
                {
                    l--;
                    timer++;
                    if (nums[l] < timer) good = 0;
                }
            }

            if (good) cout << s.second - s.first + 1 << "\n";
            else cout << "0\n";
        }
        else cout << "0\n";
    }


    return 0;
}
