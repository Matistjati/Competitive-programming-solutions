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

int minRotation(vi s) {
    int a = 0, N = sz(s); 
    vi c = s;
    repe(u, c) s.push_back(u);
    repp(b, 0, N) repp(k, 0, N) {
        if (a + k == b || s[a + k] < s[b + k]) { b += max(0LL, k - 1); break; }
        if (s[a + k] > s[b + k]) { a = b; break; }
    }
    return a;
}
signed main()
{
    fast();

    int n, k;
    cin >> n;
    if (n==1)
    {
        cout << "possible";
        return 0;
    }

    auto dist = [](int a, int b)
    {
        if (b > a) return b - a;
        return b + 360000 - a;
    };

    vi a(n);
    rep(i, n) cin >> a[i];
    vi b(n);
    rep(i, n) cin >> b[i];
    sort(all(a));
    sort(all(b));

    vi da;
    rep(i, n) da.push_back(dist(a[i],a[(i+1)%n]));
    vi db;
    rep(i, n) db.push_back(dist(b[i], b[(i+1)%n]));

    rotate(da.begin(), da.begin() + minRotation(da), da.end());
    rotate(db.begin(), db.begin() + minRotation(db), db.end());
    cout << (da == db ? "possible" : "impossible");
    return 0;
}
