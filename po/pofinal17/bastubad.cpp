#include <bits/stdc++.h>

using namespace std;

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

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    int n;
    read(n);
    vvi finnish(n);
    double a = 0;
    double b = 0;
    double c = 0;

    rep(i, n)
    {
        int a1;
        int b1;
        int c1;
        int t;
        read(a1);
        a += a1;
        read(b1);
        b += b1;
        read(c1);
        c += c1;
        read(t);
        finnish[i] = {a1,b1,c1,t};
    }



    sort(finnish.begin(), finnish.end(), [](const vi& lhs, const vi& rhs)
        {
            return lhs[3] < rhs[3];
        });


    double maxValue = -inf;

    rep(i, finnish.size())
    {
        double mx = -b / (2 * a);
        double my = a * mx * mx + b * mx + c;
        if (mx > 0 && mx < finnish[i][3])
        {
            maxValue = max(maxValue, my);
        }

        my = a * finnish[i][3] * finnish[i][3] + b * finnish[i][3] + c;
        maxValue = max(maxValue, my);

        maxValue = max(maxValue, c);

        a -= finnish[i][0];
        b -= finnish[i][1];
        c -= finnish[i][2];


    }

    cout << fixed;
    cout << setprecision(15) << maxValue;

    return 0;
}