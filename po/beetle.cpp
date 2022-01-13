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
#define vvvp2 vector<vvp2>
#define vp3 vector<p3>
#define vvp3 vector<vp3>
#define vvvp3 vector<vvp3>
#define vp4 vector<p4>
#if enablell
#define inf 1e18
#else
#define inf int(2147483640)
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
#define debassert(expr) if (!(expr)) deb;

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
#define first(a) (*begin(a))

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


int test(vvvp3& dp, vi& water, int leftMost, int rightMost, bool left, int t, int m, int score)
{
    if (t >= m)
    {
        return score;
    }

    p3& v = dp[leftMost][rightMost][left];
    int dpIncrease, dpT, dpScore;
    tie(dpIncrease, dpT, dpScore) = v;

    if (dpIncrease != -1 && dpT < t && dpScore >= score) return -inf;
    if (dpIncrease != -1 && dpT == t) return dpIncrease+score;

    int ret = score;

    int pos = water[(left) ? leftMost : rightMost];

    int index = leftMost;
    if (index - 1 >= 0)
    {
        int arrivalT = t + abs(water[index - 1] - pos);
        ret = max(ret, test(dp, water, min(leftMost, index - 1), max(rightMost, index - 1), true, arrivalT, m, score + max(0, m - arrivalT)));
    }

    index = rightMost;
    if (index + 1 < water.size())
    {
        int arrivalT = t + abs(water[index + 1] - pos);
        ret = max(ret, test(dp, water, min(leftMost, index + 1), max(rightMost, index + 1), false, arrivalT, m, score + max(0, m - arrivalT)));
    }

    v = { ret - score,t, score };

    return ret;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, n, m);

    readvector(int, water, n);



    int free = 0;

    sort(all(water));

    auto it = lower_bound(all(water), 0);

    int index;
    if (it == water.end())
    {
        water.emplace_back(0);
        index = water.size()-1;
    }
    else if (*it != 0)
    {
        it = water.insert(it, 0);
        index = it - water.begin();
    }
    else
    {
        free = m;
        index = it - water.begin();
    }


    n = water.size();

    vvvp3 bounds(n, vvp3(n, vp3(2, { -1,-1, -1 })));
    cout << test(bounds, water, index, index, false, 0, m, 0) + free;

    quit;
}