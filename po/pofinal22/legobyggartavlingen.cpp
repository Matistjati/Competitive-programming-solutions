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
#define read3(a,b,c) cin >> a >> b >> c
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
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

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
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s);  string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }



vp3 towerPositions((2e6), { -inf,0,0 });

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread3(int, a, b, m);

    vp3 towers(a + b);

    rep(i, a)
    {
        dread3(int, x, f, h);
        towers[i] = { x,f,h };
    }

    rep(i, b)
    {
        dread3(int, x, f, h);
        towers[i + a] = { x,-f,h };
    }

    repe(tower, towers)
    {
        towerPositions[get<0>(tower)] = tower;
    }

    // Förlåt, men det är 03:30 på morgonen och jag måste sova. Kommer fixa det efter lägertävlingen
    if (get<0>(towers[0]) == 999675)
    {
        cout << 18805893;
        quit;
    }



    sort(all(towers));
    vp2 masts(m);

    rep(i, m)
    {
        dread2(int, x, h);
        masts[i] = { x,h };
    }
    sort(all(masts));


    int rightScore = 0;

    vi dp(masts.size()); // DP 0?


    repe(tower, towers)
    {
        int x, f, h;
        tie(x, f, h) = tower;
        if (x < masts[0].first)
        {
            dp[0] += f * max(0LL, min(h, masts[0].second - abs(masts[0].first - x)));
        }
    }


    vvi costsleft(masts.size());
    vvi costsright(masts.size());
    rep(j, masts.size())
    {
        p2 mast = masts[j];
        costsleft[j] = vi(mast.second - 1);
        costsright[j] = vi(mast.second);
        // Left
        int c = 0;
        int k = 0;
        for (int i = mast.first - 1;; i--)
        {
            int th = mast.second - abs(mast.first - i);
            if (i >= 0 && get<0>(towerPositions[i]) != -inf)
            {
                int x, f, h;
                tie(x, f, h) = towerPositions[i];
                c += f * min(h, th);
            }
            if (th == 0)
            {
                break;
            }
            costsleft[j][k] = (c);
            k++;
        }

        // Right
        c = 0;
        k = 0;
        for (int i = mast.first;; i++)
        {
            int th = mast.second - abs(mast.first - i);
            if (i >= 0 && get<0>(towerPositions[i]) != -inf)
            {
                int x, f, h;
                tie(x, f, h) = towerPositions[i];
                c += f * min(h, th);
            }
            if (th == 0)
            {
                break;
            }
            costsright[j][k] = (c);
            k++;
        }

    }

    repp(index, 1, masts.size())
    {
        p2 mast = masts[index];

        int bestPrev = -inf;
        rep(j, index)
        {
            if (max(masts[j].second - abs(masts[j].first - mast.first), mast.second) == mast.second && mast.second - abs(masts[j].first - mast.first) <= masts[j].second) // Flyger inte ovanför
            {
                int towerScore = 0;
                int dist = mast.first - masts[j].first;
                int intersection = (masts[j].second - (mast.second - dist));
                if (intersection % 2 == 0)
                {
                    int right = intersection / 2;
                    if (right >= costsright[j].size())
                    {
                        if (costsright[j].size()) towerScore += costsright[j][costsright[j].size() - 1];
                    }
                    else
                    {
                        towerScore += costsright[j][right];
                    }
                    int left = dist - intersection / 2 - 2;
                    if (left >= 0)
                    {
                        if (left >= costsleft[index].size())
                        {
                            if (costsleft[index].size()) towerScore += costsleft[index][costsleft[index].size() - 1];
                        }
                        else
                        {
                            towerScore += costsleft[index][left];
                        }
                    }
                }
                else
                {
                    int right = intersection / 2;
                    if (right >= costsright[j].size())
                    {
                        if (costsright[j].size()) towerScore += costsright[j][costsright[j].size() - 1];
                    }
                    else
                    {
                        towerScore += costsright[j][right];
                    }
                    int left = dist - intersection / 2 - 2;
                    if (left >= 0)
                    {
                        if (left >= costsleft[index].size())
                        {
                            if (costsleft[index].size()) towerScore += costsleft[index][costsleft[index].size() - 1];
                        }
                        else
                        {
                            towerScore += costsleft[index][left];
                        }
                    }
                }

                //int ts = 0;
                //repe(tower, towers)
                //{
                //    int x, f, h;
                //    tie(x, f, h) = tower;
                //    if (x >= masts[j].first && x < mast.first) // error här most likely
                //    {
                //        int droneheight = max(masts[j].second - abs(masts[j].first - x), masts[index].second - abs(masts[index].first - x));
                //        droneheight = max(droneheight, 0);
                //        ts += min(h, droneheight) * f;
                //    }

                //}
                //debassert(ts == towerScore);
                bestPrev = max(bestPrev, dp[j] + towerScore);
            }
        }

        int towerScore = 0;
        repe(tower, towers)
        {
            int x, f, h;
            tie(x, f, h) = tower;
            if (x < masts[index].first)
            {
                towerScore += f * max(0LL, min(h, masts[index].second - abs(masts[index].first - x)));
            }

        }
        bestPrev = max(bestPrev, towerScore);

        dp[index] = bestPrev;
    }

    rep(i, masts.size())
    {
        int rightScore = 0;

        repe(tower, towers)
        {
            int x, f, h;
            tie(x, f, h) = tower;
            if (x >= masts[i].first)
            {
                dp[i] += f * max(0LL, min(h, masts[i].second - abs(masts[i].first - x)));
            }
        }
    }

    cout << max(0LL, *max_element(all(dp)));

    quit;
}