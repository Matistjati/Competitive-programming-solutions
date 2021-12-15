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
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(b):(a))

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

void topsort(vvi& adjacent, vi& order, vb& visited, int n, int& index)
{
    if (visited[n])
    {
        return;
    }
    else
    {
        visited[n] = true;
    }

    repe(adj, adjacent[n])
    {
        if (!visited[adj])
        {
            topsort(adjacent, order, visited, adj, index);
        }
    }

    order[index] = n;
    index--;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Release\\in.txt");
#endif

    dread2(int, n, p);

    vvi adjacent(n);

    rep(i, p)
    {
        dread(int, m);

        readvector(int, order, m);

        per(i, m-1)
        {
            per(j, i - 1)
            {
                int g = order[i];
                int l = order[j];
                adjacent[g].emplace_back(l);
            }
        }
    }

    vector<int> order(n);
    vb visited(n);
    int index = n - 1;

    rep(i, n)
    {
        topsort(adjacent, order, visited, i, index);
    }


    vector<pair<int, int>> longest(n, { 1,-1 });

    repe(i, order)
    {
        repe(adj, adjacent[i])
        {
            if (longest[adj].first < longest[i].first+1)
            {
                longest[adj] = { longest[i].first + 1,i };
            }

        }
    }

    auto it = max_element(all(longest));
    pair<int, int> curr = *it;

    write(curr.first);
    cout << (it - begin(longest)) << " ";

    while (curr.second!=-1)
    {
        cout << curr.second << " ";
        curr = longest[curr.second];
    }

    quit;
}
