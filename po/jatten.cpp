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

#define readpush(type,a) type temp; read(temp); a.push_back(temp);
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


bool collinear(int x1, int y1, int x2,
    int y2, int x3, int y3)
{
    // Calculation the area of
    // triangle. We have skipped
    // multiplication with 0.5
    // to avoid floating point
    // computations
    int a = x1 * (y2 - y3) +
        x2 * (y3 - y1) +
        x3 * (y1 - y2);

    return a == 0;
}

bool checkTypeOfTriangle(int a, int b, int c) {
    int sqa = a;
    int sqb = b;
    int sqc = c;

    if (sqa == sqb + sqc ||
        sqb == sqc + sqa ||
        sqc == sqa + sqb) {
        return false;
    }
    else if (sqa > sqc + sqb ||
        sqb > sqa + sqc ||
        sqc > sqa + sqb) {
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif


    dread2(int, n, m);

    dread2(int, x1, y1);
    dread2(int, x2, y2);
    uniform_int_distribution<int> dist1(0, n - 1);
    uniform_int_distribution<int> dist2(0, m - 1);
    uniform_real_distribution<double> randomAngle(0, 6.28318530718);
    mt19937 rng;

    double d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    d /= 1.9;
    pair<int, int> mid = { (x1 + x2) / 2,(y1 + y2) / 2 };
    rep(i, 1e5)
    {
        double angle = randomAngle(rng);
        int x3 = mid.first+d*cos(angle);
        int y3 = mid.second+d*sin(angle);

        double a = (pow(x1 - x2, 2) + pow(y1 - y2, 2));
        double b = (pow(x1 - x3, 2) + pow(y1 - y3, 2));
        double c = (pow(x3 - x2, 2) + pow(y3 - y2, 2));

        vector<double> sides = { a,b,c };
        sort(all(sides));
        if (sides[0] + sides[1] < sides[2])
        {
            if (sqrt(sides[0]) + sqrt(sides[1]) <= sqrt(sides[2]))
            {
                continue;
            }
            if (x3 < 0 || x3 >= n || y3 < 0 || y3 >= m)
            {
                continue;
            }
            cout << x3 << " " << y3 << "\n";
            return 0;
        }
    }

    rep(i, 1e9)
    {
        int x3 = dist1(rng);
        int y3 = dist2(rng);

        double a = (pow(x1 - x2, 2) + pow(y1 - y2, 2));
        double b = (pow(x1 - x3, 2) + pow(y1 - y3, 2));
        double c = (pow(x3 - x2, 2) + pow(y3 - y2, 2));

        vector<double> sides = { a,b,c };
        sort(all(sides));
        if (sides[0] + sides[1] < sides[2])
        {
            if (sqrt(sides[0]) + sqrt(sides[1]) <= sqrt(sides[2]))
            {
                continue;
            }
            if (x3 < 0 || x3 >= n || y3 < 0 || y3 >= m)
            {
                continue;
            }
            cout << x3 << " " << y3 << "\n";
            return 0;
        }
    }


    _Exit(0);
}