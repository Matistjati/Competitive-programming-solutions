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
#define dread3(type, a, b, c) dread(type, a); dread(type, b); dread(type, c)
#define dread4(type, a, b, c, d) dread(type, a); dread(type, b); dread(type, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread(type, a); dread(type, b); dread(type, c); dread(type, d); dread(type, e)
#define write(a) cout << (a) << endl
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

int possible(vector<pair<ll, pair<int, int>>>& sums, int index, int x, int y, int n)
{
    int bought = 0;
    while (x > 0 || y > 0)
    {
        bool hasBought = false;
        for (int i = index; i < sums.size(); i++)
        {
            if (x - sums[i].second.first >= 0 && y - sums[i].second.second >= 0)
            {
                bought++;
                index = i;
                x -= sums[i].second.first;
                y -= sums[i].second.second;
                hashBought = true;
                break;
            }
        }
        if (!hasBought)
        {
            break;
        }
    }
    return bought >= n;
}

int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread5(int, x, a, y, b, n);
    int bestV = -inf;
    vector<pair<ll, pair<int, int>>> sums;
    for (int i = 0; i < x + 1; i++)
    {
        for (int j = 0; j < y + 1; j++)
        {

            sums.push_back({ i * a + j * b, {i,j} });
        }
    }
    sort(all(sums));

    int low = 0;
    int high = sums.size() - 1;

    int highestPossible = (high + low / 2);

    while (true)
    {
        int index = (low + high) / 2;
        int v = sums[index].first;

        if (possible(sums, index, x, y, n))
        {
            low = index;
            highestPossible = index;
        }
        else
        {
            high = index;
        }

        if (low + 1 == high)
        {
            break;
        }

    }

    for (int i = highestPossible; i < sums.size(); i++)
    {
        if (possible(sums, i, x, y, n))
        {
            highestPossible = max(highestPossible, i);
        }

        if (i % 100 == 0)
        {
            auto End = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> Elapsed = End - Start;
            if (Elapsed.count() >= 200)
                break;
        }
    }

    cout << sums[highestPossible].first << endl;

    //return 0;
    _Exit(0);
}