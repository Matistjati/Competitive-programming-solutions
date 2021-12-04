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
#define ip4 tuple<int,int,int,int>
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
#define sign(a) ((a>0) ? 1 : -1)

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
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    vector<int> startState(5);
    rep(i, 5)
    {
        dread(int, n);
        startState[i] = n;
    }

    vector<int> endState(5);
    rep(i, 5)
    {
        dread(int, n);
        endState[i] = n;
    }

    set<vector<int>> visited;
    queue<pair<vector<int>,int>> toDo;
    toDo.push({ startState,0 });

    while (toDo.size())
    {
        pair<vector<int>,int> curr = toDo.front();
        toDo.pop();

        if (setcontains(visited, curr.first))
        {
            continue;
        }
        else
        {
            visited.insert(curr.first);
        }

        if (curr.first==endState)
        {
            cout << curr.second << endl;
            return 0;
        }

        rep(i, 5)
        {
            vector<int> c(curr.first);
            int n = c[i];
            c[i] = 0;
            int index = i;
            for (int j = 0; j < n; j++)
            {

                c[index]++;
                index++;
                if (index > 4)
                {
                    index = 0;
                }
            }
            toDo.push({ c,curr.second + 1 });
        }
        rep(i, 5)
        {
            vector<int> c(curr.first);
            int n = c[i];
            c[i] = 0;
            int index = i;
            for (int j = 0; j < n; j++)
            {

                c[index]++;
                index--;
                if (index < 0)
                {
                    index = 4;
                }
            }
            toDo.push({ c,curr.second + 1 });
        }
    }

    cout << endl;
    _Exit(0);
}