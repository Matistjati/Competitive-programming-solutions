#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
const int inf = int(1e9);

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

struct node
{
    int value=-1, mi=-1, ind=-1,l=-1,r=-1;
    node() {}
};
int nc = 0;
node nodes[int(1e6)];

int get_mi(int x) { return x!=-1 ? nodes[x].mi : inf; }

int find_leftmost(int ind, int& k)
{
    node& x = nodes[ind];
    int ret = inf;
    if (get_mi(x.l)<=k)
    {
        ret = find_leftmost(x.l, k);
    }
    else if (x.value <= k)
    {
        k -= x.value;
        x.value = inf;
        ret = x.ind;
    }
    else if (get_mi(x.r) <= k) ret = find_leftmost(x.r, k);
    
    x.mi = min(min(get_mi(x.l), get_mi(x.r)), x.value);
    return ret;
}

int build(int l, int r, vi& nums)
{
    if (l > r) return -1;
    if (l == r)
    {
        nodes[nc].ind = l;
        nodes[nc].value = nodes[nc].mi = nums[l];
        return nc++;
    }
    int mid = (l + r) / 2;
    int ret = nc++;
    node& x = nodes[ret];
    x.ind = mid;
    x.value = nodes[ret].mi = nums[mid];
    x.l = build(l, mid - 1, nums);
    x.r = build(mid + 1, r, nums);
    x.mi = min(min(get_mi(x.l), get_mi(x.r)), x.value);
    return ret;
}

inline char gc() { // like getchar()
    static char buf[1 << 16];
    static size_t bc, be;
    if (bc >= be) {
        buf[0] = 0, bc = 0;
        be = fread(buf, 1, sizeof(buf), stdin);
    }
    return buf[bc++]; // returns 0 on EOF
}

int readInt() {
    int a, c;
    while ((a = gc()) < 40);
    if (a == '-') return -readInt();
    while ((c = gc()) >= 48) a = a * 10 + c - 480;
    return a - 48;
}

signed main()
{
	fast();

    int n, k;
    n = readInt();
    k = readInt();
    
    vi nums(n);
    rep(i, n) nums[i]=readInt();
    int root = build(0, n - 1, nums);

    vi ans(n, -1);
    rep(i,n)
    {
        int l = k;
        while (1)
        {
            int ind = find_leftmost(root, l);
            if (ind == inf) break;
            ans[ind] = i;
        }
    }
    rep(i, n) cout << ans[i] << " ";

	return 0;
}
