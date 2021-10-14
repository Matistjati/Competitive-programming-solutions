#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>


using namespace std;

#define ll long long
#define p2 pair<ll, ll>
#define p3 tuple<ll, ll, ll>
#define vi vector<ll>
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)


inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

inline int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

vector<int> farey_sequence(int many, int maxV)
{
    int n = 0;
    int m = 1;
    int c = 1;
    int d = many;

    vector<int> solutions(717958);

    while (c <= many)
    {
        int k = (many + m) / d;
        int oldn = n;
        int oldm = m;
        n = c;
        m = d;
        c = k * c - oldn;
        d = k* d - oldm;



        if (n <= m/2)
        {
            int gcd = 1;
            if (m % 3 == mod(-n,3))
            {
                gcd = 3;
            }
            int mm = m * m;
            int nn = n * n;
            int a = mm - m * n + nn;
            a /= gcd;
            int b = 2 * m * n - nn;
            b /= gcd;
            int c = mm - nn;
            c /= gcd;

            int m = 1;
            while (m*a <= maxV && m*b <= maxV && m*c <= maxV)
            {
                solutions[max({ m * a, m * b, m * c })]++;
                m++;
            }
        }

    }

    return solutions;
}

int main()
{
    fast();



    vector<int> sol = (farey_sequence(893, 200000));
    vector<int> prefix(717958);
    int s = 0;
    rep(i, prefix.size())
    {
        s += sol[i];
        prefix[i] = s;
    }

    string in;
    while (getline(cin, in))
    {
        write(prefix[stoi(in)]);
    }

    return 0;
}