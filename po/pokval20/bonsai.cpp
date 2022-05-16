#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

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
#define dread2(type, a, b) dread(type, a); dread(type, b)
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
    set<pair<int,int>> times;
    set<pair<int,int>> summedTimes;
    map<int, int> branchToIndex;
    int edges;
    int nlargest;
    int lowestIndex;
    ll time;
};

int constructtree(vector<Node>& connections, int curr, int parent)
{
    Node& node = connections[curr];
    int c = node.edges - (parent != -1);
    bool changed = false;
    for (auto it = node.remaining.cbegin(); it != node.remaining.cend() /* not hoisted */; /* no increment */)
    {
        if (*it == parent)
        {
            it++;
            continue;
        }

        int time = constructtree(connections, *it, curr);

        changed = true;
        node.times.insert({ -time, *it });

        it = node.remaining.erase(it++);    // or "it = m.erase(it)" since C++11
    }


    int ret = 0;


    int i = 1;
    if (node.remaining.size() == 0)
    {
        if (changed)
        {
            repe(t, node.times)
            {
                node.branchToIndex[t.second] = i;
                node.summedTimes.insert({ (ll)(-(- t.first + i)) , i});
                i++;
            }

        }

        int largest = (*begin(node.summedTimes)).first;
        int index = parent == -1 ? inf : node.branchToIndex[parent];
        repe(t, node.summedTimes)
        {
            if (t.second == index)
            {
                continue;
            }
            ret = max(ret, (-t.first) - (index < t.second));
            if (t.first != largest)
            {
                break;
            }
        }
    }
    else
    {
        repe(t, node.times)
        {
            if (t.second != parent)
            {
                ret = max(ret, (-t.first + i));
                i++;
            }
        }
    }


    ret = max(c, ret);


    return ret;
}

int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread(int, n);
    vector<Node> connections(n);
    rep(i, n)
    {
        dread(int, c);
        rep(j, c)
        {
            dread(int, con);
            connections[i].remaining.insert(con);
        }
    }

    rep(i, connections.size())
    {
        Node& n = connections[i];
        n.index = i;
        n.edges = n.remaining.size();
    }

    int ans = inf;

    rep(i, n)
    {
        ans = min(ans, constructtree(connections, i, -1));
    }
    write(ans);

    return 0;
}