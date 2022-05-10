#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define dread(type, a) type a; cin >> a
#define write(a) cout << (a) << endl
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))


inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}


struct Node
{
    int index;
    unordered_set<int> remaining;
    unordered_map<int,double> values;
    double sum;
    int edges;
};

double howmany(vector<Node>& connections, vector<double>& attacks, int n, int parent)
{
    Node& node = connections[n];
    double s = node.sum;

    for (auto it = node.remaining.cbegin(); it != node.remaining.cend() /* not hoisted */; /* no increment */)
    {
        if (*it == parent)
        {
            it++;
            continue;
        }

        double many = howmany(connections, attacks, *it, n);
        node.sum += many;

        s += many;
        node.values[*it] = many;

        it = node.remaining.erase(it++);    // or "it = m.erase(it)" since C++11
    }

    if (node.values[parent] != -inf)
    {
        s -= node.values[parent];
    }
    
    if (parent != -1)
    {
        s /= max(1, (int)node.edges - 1);
    }
    if (parent == -1)
    {
        s += attacks[n];
    }
    else
    {
        s += attacks[n] / node.edges;
    }
    

    return s;
}


int main()
{
    fast();

    int n;
    read(n);
    vector<Node> connections(n + 1, Node());

    bool is_simple = true;
    rep(i, n-1)
    {
        dread(int, a);
        dread(int, b);

        if (a+1!=b)
        {
            is_simple = false;
        }

        connections[a].remaining.insert(b);
        connections[b].remaining.insert(a);
        connections[a].values[b] = -inf;
        connections[b].values[a] = -inf;
    }

    

    int k;
    read(k);
    
    vector<double> indirectAttacks(n + 1);
    rep(i, k)
    {
        dread(int, target);
        dread(double, strength);
        indirectAttacks[target] += strength;
    }

    for (int i = 1; i < n + 1; i++)
    {
        connections[i].index = i;
        connections[i].edges = connections[i].remaining.size();
        connections[i].sum = 0;
    }

    vector<double> directAttacks(n + 1);

    cout << fixed << setprecision(31);
    vector<double> ans(n+1);
    vector<int> order(n + 1);
    for (int i = 1; i < n + 1; i++)
    {
        order[i] = i;
    }


    for (int i = 1; i < n + 1; i++)
    {
        int j = i;

        Node n = connections[i];

        ans[j] = howmany(connections, indirectAttacks, j, -1);
    }

    for (int i = 1; i < n + 1; i++)
    {
        cout << ans[i] << "\n";
    }

    return 0;
}