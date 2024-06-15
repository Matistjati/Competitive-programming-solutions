#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
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
#define fast_map map
#define assert(x) if (!(x)) __debugbreak()
#endif

typedef unsigned long long ull;

auto start = chrono::high_resolution_clock::now();
void resettimer() { start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count(); }

#if !_LOCAL
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};
__gnu_pbds::gp_hash_table<ull, pair<ull,char>, chash> par({}, {}, {}, {}, { 1 << 22 });
#else
unordered_map<ull, pair<ull,char>> par;
#endif

signed main()
{
    fast();

    int n;
    cin >> n;
    vector<string> grid(n);
    rep(i, n) cin >> grid[i];
    resettimer();

    queue<ull> q;

    ull start=0;
    repp(i, 1, n - 1) repp(j,1,n-1)
    {
        if (grid[i][j] == '.') start |= 1ULL << (i * n + j);
    }
    q.emplace(start);

    vector<p2> moves = { {0,1},{1,0},{-1,0}, {0,-1} };
    vector<char> dirs = { 0, 1, 2, 3 };
    vector<string> dirstr = { "east", "south", "north", "west"};
    while (q.size())
    {
        ull s;
        tie(s) = q.front();
        q.pop();


        if (__builtin_popcountll(s)==0)
        {
            break;
        }

        rep(i, 4)
        {
            p2 dir = moves[i];
            ull news=0;
            int a = 0;
            int b = 0;
            rep(j, 64)
            {
                if ((s & (1ULL<<j)) == 0) goto end;
                if (grid[a+dir.first][b+dir.second] == 'O')
                {
                    news |= 1ULL<<j;
                    goto end;
                }
                if (a+dir.first == 0 || b+dir.second == 0 || a+dir.first == n - 1 || b+dir.second == n - 1) goto end;
                news |= 1ULL << ((a+dir.first)*n+b+dir.second);
            end:;
                b++;
                if (b==n)
                {
                    b = 0;
                    a++;
                }
            }
            if (par.find(news)==par.end())
            {
                par[news] = { s,dirs[i] };
                q.emplace(news);
            }
        }
    }
    ull pos = 0;
    vector<string> ans;
    par[start].second = 'A';
    while (par[pos].second!='A')
    {
        ans.push_back(dirstr[par[pos].second]);
        pos = par[pos].first;
    }
    reverse(all(ans));
    repe(s, ans) cout << s << "\n";
    cerr << "millis: " << elapsedmillis() << "\n";
    cerr << "sz: " << sz(par) << "\n";

    return 0;
}
