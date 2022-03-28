#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
//#include <bits/extc++.h>

using namespace std;

#define enablell 1

#define ll long long
#if enablell
#define int ll
#define inf 2e18
#define float double
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
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
#define debassert(expr) ;
#define debif(expr) ;
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
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s);  string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }

int ans(vi& a, vi& b, map<p2,int>& dp, int index, int n_taken, int score)
{
    if (n_taken==a.size())
    {
        return score;
    }
    if (index==b.size())
    {
        return inf;
    }
    if (index-n_taken>1)
    {
        return inf;
    }

    p2 state = mp(index, n_taken);
    if (setcontains(dp,state))
    {
        return dp[state] + score;
    }


    int ret = inf;

    ret = min(ret, ans(a, b, dp, index + 1, n_taken + 1, score + abs(a[n_taken] - b[index])));
    ret = min(ret, ans(a, b, dp, index + 1, n_taken, score));

    dp[state] = ret - score;

    return ret;

}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, n, m);



    if (m==n+1)
    {
        readvector(int, op, n);
        readvector(int, mine, m);

        sort(all(op), greater<int>());
        sort(all(mine), greater<int>());
        map<p2, int> dp;
        cout << ans(op, mine, dp, 0, 0, 0);
        quit;
        vi matching(n);

        int selection = (1 << m) - 1;

        int ans = inf;
        rep(i, m)
        {
            int sel = selection & ~(1 << i);

            int a = 0;
            int j = 0;
            rep(k, m)
            {
                if (sel & (1 << k))
                {
                    a += abs(op[j] - mine[k]);
                    j++;
                }
            }
            ans = min(ans, a);
        }

        cout << ans;
    }
    else
    {
        readvector(int, op, n);
        readvector(int, mine, m);

        sort(all(op), greater<int>());
        sort(all(mine), greater<int>());

        vi matching(n);

        rep(i, n)
        {
            matching[i] = abs(op[i] - mine[i]);
        }

        if (m == n + 1)
        {
            int mi = -1;
            int gdiff = inf;
            rep(i, n)
            {
                int diff = abs(op[i] - mine[sz(mine) - 1]) - matching[i];
                if (diff < gdiff)
                {
                    gdiff = diff;
                    mi = i;
                }
            }
            if (gdiff < 0)
            {
                matching[mi] = abs(op[mi] - mine[sz(mine) - 1]);
            }
        }

        //multiset<int> opponent;

        //rep(i, n)
        //{
        //    dread(int, op);
        //    opponent.insert(-op);
        //}

        //multiset<int> mine;

        //rep(i, m)
        //{
        //    dread(int, op);
        //    mine.insert(op);
        //}

        //int ans = 0;



        //repe(MI, opponent)
        //{
        //    int mi = -MI;

        //    auto it = mine.lower_bound(mi);

        //    if (it == mine.end()) it = prev(it);

        //    int roundAns = abs(mi - *it);

        //    if (it != mine.begin())
        //    {
        //        int secondScore = roundAns, abs(mi - *prev(it));
        //        if (secondScore < roundAns)
        //        {
        //            roundAns = secondScore;
        //            mine.erase(prev(it));
        //        }
        //        else
        //        {
        //            mine.erase((it));
        //        }
        //    }
        //    else
        //    {
        //        mine.erase((it));
        //    }
        //    ans += roundAns;
        //}

        cout << accumulate(all(matching), 0LL);
    }


    //multiset<int> opponent;

    //rep(i, n)
    //{
    //    dread(int, op);
    //    opponent.insert(-op);
    //}

    //multiset<int> mine;

    //rep(i, m)
    //{
    //    dread(int, op);
    //    mine.insert(op);
    //}

    //int ans = 0;



    //repe(MI, opponent)
    //{
    //    int mi = -MI;

    //    auto it = mine.lower_bound(mi);

    //    if (it == mine.end()) it = prev(it);

    //    int roundAns = abs(mi - *it);

    //    if (it != mine.begin())
    //    {
    //        int secondScore = roundAns, abs(mi - *prev(it));
    //        if (secondScore < roundAns)
    //        {
    //            roundAns = secondScore;
    //            mine.erase(prev(it));
    //        }
    //        else
    //        {
    //            mine.erase((it));
    //        }
    //    }
    //    else
    //    {
    //        mine.erase((it));
    //    }
    //    ans += roundAns;
    //}


    quit;
}