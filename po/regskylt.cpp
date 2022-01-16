#include <bits/stdc++.h>
//#include <bits/extc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define enablell 0

#define ll long long
#if enablell
#define int ll
#define inf 2e18
#else
#define inf int(2e9)
#endif
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define p2 pair<int, int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vvvp2 vector<vvp2>
#define p3 tuple<int,int,int>
#define vp3 vector<p3>
#define vvp3 vector<vp3>
#define vvvp3 vector<vvp3>
#define p4 tuple<int,int,int,int>
#define vp4 vector<p4>

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
#define debassert(expr) if (!(expr)) deb;
#else
#define noop ;
#define deb ;
#define debassert(expr) ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high; i >= 0; i--)
#define perr(i, low, high) for (int i = high; i >= low; i--)

#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define first(a) (*begin(a))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define rununtil(time) if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

template <typename T, typename U> void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

int nums[1771562];

inline int plateToNum(int P[6])
{
    int v = 0;

    int m = 1;
    #pragma GCC ivdep
    #pragma GCC unroll 6
    rep(i, 6)
    {
        v += (P[i] == -1 ? 10 : P[i]) * m;
        m *= 11;
    }
    return v;
}

int np[6];

int plate(int P[6])
{
    int matches = 0;

    matches += nums[plateToNum(P)];

    #pragma GCC ivdep
    #pragma GCC unroll 64
    rep(i, (1 << 6))
    {
        bool match = true;

        #pragma GCC ivdep
        #pragma GCC unroll 6
        rep(j, 6)
        {
            bool setBit = (i & (1 << j));
            if ((setBit && P[j] == -1))
            {
                match = false;
            }
            np[j] = (setBit) ? -1 : P[j];
        }

        if (match)
        {
            nums[plateToNum(np)]++;
        }
    }

    return matches;
}



//
//int main() {
//  int N;
//  ignore = scanf("%d", &N);
//  int P[6];
//  for (int i = 0; i < N; ++i) {
//      for (int j = 0; j < 6; ++j) {
//          ignore = scanf("%d", P + j);
//      }
//      printf("%d\n", plate(P));
//  }
//}



//int32_t main()
//{
//    fast();
//
//#if 0
//    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
//#endif
//
//
//
//
//
//    quit;
//}