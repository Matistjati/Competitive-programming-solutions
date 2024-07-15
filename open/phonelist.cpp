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
#define assert(x) if (!(x)) __debugbreak()
#endif

struct Node
{
    map<char, Node*> children;
    bool marked = false;

    void insert(int i, string& s)
    {
        if (i == sz(s))
        {
            marked = true;
            return;
        }
        if (children.find(s[i]) == children.end()) children[s[i]] = new Node();
        children[s[i]]->insert(i + 1, s);
    }

    bool bad()
    {
        if (marked && sz(children)) return 1;
        repe(c, children) if (c.second->bad()) return 1;
        return 0;
    }
};

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        Node* root = new Node();
        rep(i, n)
        {
            string s;
            cin >> s;
            root->insert(0, s);
        }

        if (root->bad()) cout << "NO\n";
        else cout << "YES\n";
    }

    return 0;
}
