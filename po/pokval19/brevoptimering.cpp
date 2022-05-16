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
#define ip3 tuple<int,int,int>
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define write(a) cout << (a) << "\n"
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}


int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread(int, n);
    vector < pair<int, vector<pair<int, int>>>> nodes(n);
    vector<int> n_connections(n, 0);

    rep(i, n)
    {
        dread2(int, m, k);

        vector<pair<int, int>> connections;
        rep(l, k)
        {
            dread2(int, j, w);
            j--;
            n_connections[j]++;
            connections.emplace_back(make_pair(j,w));
        }

        nodes[i] = make_pair(m, connections);
    }

    vector<double> production(n);

    queue<int> todo;
    vector<int> visited(n);
    rep(i,n)
    {
        if (n_connections[i] == 0)
        {
            todo.push(i);
            production[i] = inf;
        }
    }

    while (todo.size())
    {
        int curr = todo.front();
        todo.pop();

        if (visited[curr])
        {
            continue;
        }
        else
        {
            visited[curr] = true;
        }

        double limit = nodes[curr].first;
        double incoming = production[curr];
        double out = min(limit, incoming);

        repe(edge, nodes[curr].second)
        {
            production[edge.first] += out * (edge.second/double(100));
            n_connections[edge.first]--;
            if (n_connections[edge.first] == 0)
            {
                todo.push(edge.first);
            }
        }
    }

    set<int> maxCapacity;

    rep(i,n)
    {
        if (production[i]-nodes[i].first > 1e-4)
        {
            maxCapacity.insert(i);
        }
    }

    repe(person, maxCapacity)
    {
        cout << (person+1) << " ";
    }

    cout << endl;
    _Exit(0);
}