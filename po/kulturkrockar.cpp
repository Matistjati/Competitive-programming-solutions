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

set<int> ans;

bitset<1010> check(vector<bitset<1010>*>& memo, vector<pair<int, int>>& meetings, bitset<1010>& correct, vector<pair<int, int>>& adjacency, int curr)
{
    if (memo[curr] != nullptr)
    {
        return *memo[curr];
    }
    bitset<1010> c;
    c.set(meetings[curr].first);
    c.set(meetings[curr].second);


    if (adjacency[curr].first != -1)
    {
        c |= check(memo, meetings, correct, adjacency, adjacency[curr].first);
    }
    if (adjacency[curr].second != -1)
    {
        c |= check(memo, meetings, correct, adjacency, adjacency[curr].second);
    }


    if (c==correct)
    {
        ans.insert(meetings[curr].first);
        ans.insert(meetings[curr].second);
    }

    memo[curr] = new bitset<1010>(c);

    return c;
}

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif


    dread2(int, n, k);

    vector<pair<int, int>> meetings(k);
    vector<vector<int>> occurences(n+1);
    rep(i, k)
    {
        dread2(int, a, b);
        meetings[i] = { a,b };
        occurences[a].push_back(i);
        occurences[b].push_back(i);
    }

    dread(int, m);

    bitset<1010> knows;
    rep(i, m)
    {
        dread(int, knower);
        knows.set(knower);
    }

    vector<pair<int, int>> adjacency(k, make_pair(-1,-1));
    rep(i, k)
    {
        pair<int, int> meeting = meetings[i];
        auto it = upper_bound(all(occurences[meeting.first]), i);
        if (it != end(occurences[meeting.first]))
        {
            adjacency[i].first = *it;
        }

        it = upper_bound(all(occurences[meeting.second]), i);
        if (it != end(occurences[meeting.second]))
        {
            adjacency[i].second = *it;
        }
    }


    bitset<1010> checked;
    bitset<1010> works;

    vector<bitset<1010>*> memo(k);
    rep(i, k)
    {
        pair<int, int> meeting = meetings[i];
        if (!checked.test(meeting.first) || !checked.test(meeting.second))
        {
            checked.set(meeting.first);
            checked.set(meeting.second);

            check(memo, meetings, knows, adjacency, i);
        }
    }

    repe(correct, ans)
    {
        cout << correct << " ";
    }

    cout << endl;
    _Exit(0);
}