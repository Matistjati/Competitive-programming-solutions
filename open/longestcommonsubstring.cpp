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

int n;
int curr = 1;
struct Node
{
    int cnt = 0;
    int v = -1;
    map<char, Node*> children;
    Node() {}

    void insert(deque<char>& s, int i)
    {
        if (v != curr)
        {
            cnt++;
            v = curr;
        }
        if (i == sz(s)) return;
        if (children.find(s[i]) == children.end())children[s[i]] = new Node();
        children[s[i]]->insert(s, i + 1);
    }
    int best(int d)
    {
        int ret = cnt == n ? d : 0;
        repe(c, children) ret = max(ret, c.second->best(d + 1));
        return ret;
    }
};

signed main()
{
    fast();

    cin >> n;

    Node* root = new Node();
    rep(i, n)
    {
        string s;
        cin >> s;
        deque<char> q;
        rep(j, sz(s)) q.push_back(s[j]);
        while (sz(q))
        {
            root->insert(q, 0);
            q.pop_front();
        }
        curr++;
    }
    cout << root->best(0);

    return 0;
}
