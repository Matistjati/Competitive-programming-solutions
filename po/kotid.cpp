#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define enablell 0

#define ll long long
#if enablell
#define int ll
#endif
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vp3 vector<p3>
#if enablell
#define inf 1e18
#else
#define inf int(1e9)
#endif

#define read(a) cin >> a
#define write(a) cout << (a) << "\n"
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define noop cout << "";
#define deb __debugbreak();
#else
#define noop ;
#define deb ;
#endif

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repp(i, low, high) for (ll i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)
#define perr(i, low, high) for (ll i = high; i >= low; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

template <typename T, typename U>
void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r)
{
    l = { l.first + r.first,l.second + r.second };
}

struct SegmentTree
{
    vi s;
    int n;
    vi indices;
    SegmentTree(int n, int defaultV) : s(n*4, defaultV), indices(n*4), n(n) {}

    void update(int node, int st, int end, int idx, int value)
    {
        if (st == end)
        {
            /*Update leaf node*/
            indices[node] = idx;
            s[node] = value;
            return;
        }

        int mid = (st + end) / 2;
        /*if index lies in the left child call update() for left child*/
        if (idx <= mid)
            update(2 * node, st, mid, idx, value);

        /*else index would lie in the right child, call update() for the right child*/
        else
            update(2 * node + 1, mid + 1, end, idx, value);

        /*after updating the children,update the current node as smallest of its children */
        s[node] = min(s[2 * node], s[2 * node + 1]);
        return;
    }


    int query()
    {

    }

    int leftmost(int node, int st, int end, int value)
    {
        if (st == end)
        {
            /*Update leaf node*/
            return indices[node];
        }

        int mid = (st + end) / 2;
        if (s[2*node] <= value)
        {
            return leftmost(node * 2, st, mid, value);
        }
        else if (s[2 * node+1] <= value)
        {
            return leftmost(node * 2 + 1, mid+1, end, value);
        }

        return inf;
    }
};


int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Release\\in.txt");
#endif

    dread2(int, n, k);
    SegmentTree tree(n, inf);
    int t = 0;
    vi queue(n,-1);
    vi people(n);
    rep(i, n)
    {
        dread(int, p);
        people[i] = p;
        tree.update(1, 0, n-1, i, p);
    }

    int toDo = n;
    rep(t, n)
    {
        int capacity = k;
        while (capacity)
        {
            int left = tree.leftmost(1, 0, n - 1, capacity);
            if (left == inf)
            {
                break;
            }

            capacity -= people[left];
            queue[left] = t;
            tree.update(1, 0, n - 1, left, inf);
            toDo--;
        }

        if (toDo==0)
        {
            break;
        }
    }

    repe(p, queue)
    {
        cout << p << " ";
    }

    quit;
}
