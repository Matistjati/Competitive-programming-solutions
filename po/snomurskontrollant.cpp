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
#define repp(i, low, high) for (ll i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

void die()
{
    cout << "NO" << endl;
    _Exit(0);
}

inline void endpointcheck(vp2& row, int w)
{
    if (row[0].first != 0)
    {
        die();
    }

    if (row[row.size()-1].first + row[row.size()-1].second != w)
    {
        die();
    }
}

inline void holecheck(vp2& row, vp2& prevRow)
{
    if (prevRow.size()==0)
    {
        return;
    }
    int j = 0;
    int prev = row[0].second;
    repp(i, 1, row.size())
    {
        p2 curr = row[i];
        if (curr.first != prev)
        {
            while (true)
            {
                p2 p = prevRow[j];
                if (p.first+p.second > prev)
                {
                    if (p.second+p.first>=curr.first)
                    {
                        break;
                    }
                    else
                    {
                        die();
                    }
                }

                j++;
                if (j >= prevRow.size())
                {
                    return;
                }
            }
        }
        prev = curr.first + curr.second;
    }
}

inline void edgecheck(vp2& row, vp2& prevRow, int w)
{
    if (prevRow.size() == 0)
    {
        return;
    }
    int j = 0;
    repp(i, 0, row.size())
    {
        p2 curr = row[i];
        if (curr.first != 0)
        {
            while (true)
            {
                p2 p = prevRow[j];
                if (p.first + p.second > curr.first-1)
                {
                    if (p.first <= curr.first)
                    {
                        break;
                    }
                    else
                    {
                        die();
                    }
                }

                j++;
                if (j >= prevRow.size())
                {
                    return;
                }
            }
        }

        int t = curr.first + curr.second;
        if (t != w)
        {
            while (true)
            {
                p2 p = prevRow[j];
                if (p.first + p.second > t)
                {
                    if (p.first <= t)
                    {
                        break;
                    }
                    else
                    {
                        die();
                    }
                }

                j++;
                if (j >= prevRow.size())
                {
                    return;
                }
            }
        }
    }
}

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, w, h);

    vector<p2> prevRow;
    rep(i, h)
    {
        dread(int, n);
        vector<p2> row(n);
        rep(i, n)
        {
            dread2(int, start, length);
            row[i] = { start,length };
        }

        endpointcheck(row, w);
        holecheck(row, prevRow);
        edgecheck(row, prevRow, w);

        prevRow = row;
    }

    write("YES");

    cout << endl;
    _Exit(0);
}