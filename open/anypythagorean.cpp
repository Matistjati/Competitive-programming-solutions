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

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif


signed main()
{
    fast();

    int n;
    cin >> n;
    repp(j, 1, n/2+1)
    {
        repp(i, j+1, n/2+1)
        {
            if (gcd(i,j)==1)
            {
                int a = i * i - j * j;
                int b = 2 * i * j;
                int c = i * i + j * j;
                if (a == 0 || b == 0 || c == 0) continue;
                if (n%(a+b+c)==0)
                {
                    int k = n / (a + b + c);
                    cout << a * k << " " << b * k << " " << c * k;
                    return 0;
                }
            }
        }
    }
    cout << "0 0 0";

    return 0;
}
