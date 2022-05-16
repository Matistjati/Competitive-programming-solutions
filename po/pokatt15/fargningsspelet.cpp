#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define enablell 1

#define ll long long
#if enablell
#define int ll
#endif
#define vi vector<int>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vp3 vector<p3>
#define vp4 vector<p4>
#if enablell
#define inf 1e18
#else
#define inf int(1e9)
#endif

#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
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

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high; i >= 0; i--)
#define perr(i, low, high) for (int i = high; i >= low; i--)

#define readpush(type,vect) type temp; read(temp); vect.(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define insideinterval(v, interval) (v >= interval.first && v <= interval.second)
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

#define UNCOLORED 0
#define RED 1
#define BLUE 2

struct node
{
    int color;
    bool neighbourRed;
    bool neighbourBlue;
};

int n;
int m;

inline int getIndex(int index)
{
    if (m==1)
    {
        if (index < 0)
        {
            return n - 1;
        }
        else if (index == n)
        {
            return 0;
        }
        return index;
    }
    else
    {
        if (index < 0)
        {
            return 0;
        }
        else if (index >= n)
        {
            return n - 1;
        }
        return index;
    }
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    read2(n, m);

    vector<node> nodes(n);

    while (true)
    {
        dread(int, slugas);

        if (slugas==-1)
        {
            _Exit(0);
        }

        slugas--;

        nodes[slugas].color = RED;

        if (m==1)
        {
            if (slugas-1<0)
            {
                nodes[n - 1].neighbourRed = true;
            }
            else
            {
                nodes[slugas - 1].neighbourRed = true;
            }

            if (slugas+1 == n)
            {
                nodes[0].neighbourRed = true;
            }
            else
            {
                nodes[slugas + 1].neighbourRed = true;
            }
        }
        else
        {
            if (slugas - 1 >= 0)
            {
                nodes[slugas - 1].neighbourRed = true;
            }

            if (slugas + 1 < n)
            {
                nodes[slugas + 1].neighbourRed = true;
            }
        }

        int move = -1;

        rep(i, n)
        {
            if (i>0&&m==2)
            {
                if (nodes[nodes.size()-1].color == UNCOLORED && !nodes[nodes.size() - 1].neighbourBlue)
                {
                    i = n - 1;
                    if (i > 0) nodes[i - 1].neighbourBlue = true;
                    if (i < n - 1) nodes[i + 1].neighbourBlue = true;
                    nodes[i].color = BLUE;
                    move = i;
                    break;
                }
            }
            if (nodes[i].color==UNCOLORED&&!nodes[i].neighbourRed&&!nodes[i].neighbourBlue)
            {
                if (m==1)
                {
                    if (nodes[getIndex(i - 1)].neighbourRed || nodes[getIndex(i + 1)].neighbourRed)
                    {
                        nodes[getIndex(i - 1)].neighbourBlue = true;
                        nodes[getIndex(i + 1)].neighbourBlue = true;
                        nodes[i].color = BLUE;
                        move = i;
                        break;
                    }
                }
                else
                {

                    bool blocking = false;


                    if (i > 0) nodes[i - 1].neighbourBlue = true;
                    if (i < n - 1) nodes[i + 1].neighbourBlue = true;
                    nodes[i].color = BLUE;
                    move = i;
                    break;
                }
            }
        }

        if (move==-1)
        {
            rep(i, n)
            {
                if (nodes[i].color == UNCOLORED && !nodes[i].neighbourBlue)
                {
                    if (m == 1)
                    {
                        nodes[getIndex(i - 1)].neighbourBlue = true;
                        nodes[getIndex(i + 1)].neighbourBlue = true;
                        nodes[i].color = BLUE;
                        move = i;
                        break;
                    }
                    else
                    {
                        if (i > 0) nodes[i - 1].neighbourBlue = true;
                        if (i < n - 1) nodes[i + 1].neighbourBlue = true;
                        nodes[i].color = BLUE;
                        move = i;
                        break;
                    }
                }
            }
        }

        cout << move+1 << endl;
    }

    quit;
}
