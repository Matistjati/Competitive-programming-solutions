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

template <typename Out>
void split(const std::string& s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

bool possible(vector<set<int>>& connections, vector<int>& order, vector<bool>& visited, int& index, int curr)
{
    if (index == order.size())
    {
        return true;
    }
    if (visited[curr])
    {
        return true;
    }
    else
    {
        visited[curr] = true;
    }

    bool ret = true;

    rep(i, connections[curr].size()-(index!=1))
    {
        if (index == order.size())
        {
            return ret;
        }
        if (setcontains(connections[curr], order[index]))
        {
            index++;
            ret &= possible(connections, order, visited, index, order[index-1]);
        }
        else
        {
            if (!ret)
            {
                return false;
            }

            bool bottom = true;
            repe(con, connections[curr])
            {
                if (!visited[con])
                {
                    bottom = false;
                    break;
                }
            }
            return bottom;
        }
    }
    return ret;
}

int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread2(int, n, e);
    vector<set<int>> connections(n, set<int>());
    rep(i, e)
    {
        dread2(int, a, b);
        connections[a].insert(b);
        connections[b].insert(a);
    }

    string search;
    getline(cin, search);
    if (search == "")
    {
        getline(cin, search);
    }
    vector<string> parts = split(search, ' ');
    vector<int> order(parts.size());
    rep(i, parts.size())
    {
        order[i] = stoi(parts[i]);
    }

    vector<bool> visited(n);
    int index = 1;
    if (order.size()!=n)
    {
        write("NO");
        return 0;
    }
    write(possible(connections, order, visited, index, order[0]) ? "YES":"NO");



    return 0;
}