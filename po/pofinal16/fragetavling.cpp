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
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread4(int, n, m, k, b);

    vector<pair<int, int>> questions(n);
    vector<vector<int>> groups(m);
    rep(i, n)
    {
        cin >> questions[i].first;
        cin >> questions[i].second;
        questions[i].second--;
        groups[questions[i].second].push_back(questions[i].first);
    }

    rep(i, m)
    {
        sort(all(groups[i]), greater<int>());
        for (int j = 1; j < groups[i].size(); j++)
        {
            groups[i][j] += groups[i][j - 1];
        }
    }


    vector<vector<int>> dp(m+1, vector<int>(k+1,0));

    for (int M = 1; M < m+1; M++)
    {
        for (int K = 0; K < k+1; K++)
        {
            for (int i = 0; i < groups[M - 1].size()+1; i++)
            {

                if (K + i > k)
                {
                    break;
                }

                int inc = (i == 0) ? 0 : groups[M - 1][i-1];
                if (i == groups[M-1].size())
                {
                    inc += b;
                }

                dp[M][K + i] = max(dp[M][K + i], dp[M - 1][K] + inc);
            }
        }

    }

    cout << dp[m][k];

    cout << endl;
    _Exit(0);
}