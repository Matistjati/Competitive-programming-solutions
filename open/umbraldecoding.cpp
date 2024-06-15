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

#if _LOCAL
#define __builtin_popcountll popcount
#define assert(x) if (!(x)) __debugbreak()
#endif

double cube(int x)
{
    return abs(double(x) * x * x);
}

signed main()
{
    fast();

    int n, k;
    cin >> n >> k;
    vi unsafe;
    unsafe.reserve(int(1e8));
    rep(_, k)
    {
        int a, b, r;
        cin >> a >> b >> r;

        int lor = max(0LL, int(a - 931));
        int hir = min(n, int(a + 931));
        int loc = max(0LL, int(b - 931));
        int hic = min(n, int(b + 931));
        
        repp(i, lor, hir + 1)
        {
            repp(j, loc, hic + 1)
            {
                if (cube(a - i) + cube(b - j) <= r) unsafe.push_back(i * (n + 10) + j);
            }
        }
    }
    sort(all(unsafe));
    int unique = sz(unsafe)>0;
    repp(i, 1, sz(unsafe)) unique += unsafe[i] != unsafe[i - 1];
    cout << (n + 1) * (n + 1) - unique;

    return 0;
}
