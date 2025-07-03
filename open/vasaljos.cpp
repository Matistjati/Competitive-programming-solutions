#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

map<vi, p2> bestchoice;
map<vi, int> memo;
int brute(vi& masks, int n)
{
    if (memo.count(masks)) return memo[masks];
    bool is_monotone = 0;
    rep(i, n)
    {
        repp(j, i + 1, n)
        {
            bool good = 1;
            repe(m, masks)
            {
                good &= (m & (1 << i)) > 0 && (m & (1 << j)) > 0;
                if (!good) break;
            }
            if (good)
            {
                is_monotone = 1;
                bestchoice[masks] = { i,j };
                goto end;
            }
        }
    }
end:;

    if (is_monotone) return 1;
    
    int ret = inf;

    rep(i, n)
    {
        repp(j, i + 1, n)
        {
            vi split;
            repe(m, masks)
            {
                if (!((m & (1 << i)) > 0 && (m & (1 << j)) > 0))
                {
                    split.push_back(m);
                }
            }
            if (sz(split) < sz(masks))
            {
                int v = 1 + brute(split, n);
                if (v<ret)
                {
                    bestchoice[masks] = { i,j };
                    ret = v;
                }
            }
        }
    }

    return memo[masks] = ret;
}

signed main()
{
    fast();

    //int k = 6;
    //vi masks;
    //rep(i, 1 << k)
    //{
    //    if (popcount((unsigned long long)i) == k / 2)
    //    {

    //        masks.push_back(i);
    //    }
    //}
    //cout << brute(masks, k) << "\n";

    //rep(_, 10)
    //{
    //    int a = bestchoice[masks].first;
    //    int b = bestchoice[masks].second;
    //    cout << a << " " << b << "\n";
    //    vi split;
    //    repe(m, masks)
    //    {
    //        if (!((m & (1 << a)) > 0 && (m & (1 << b)) > 0))
    //        {
    //            split.push_back(m);
    //        }
    //    }
    //    masks = split;
    //}


    string goal = "Ljos!";

    int n;
    cin >> n;

    map<p2, string> cache;
    auto ask = [&](int i, int j)
        {
            if (i > j) swap(i, j);
            if (cache.count(p2(i, j))) return cache[p2(i, j)];
            cout << i << " " << j << endl;
            string res;
            cin >> res;
            if (res == goal) exit(0);
            return cache[p2(i,j)]=res;
        };

    int i = 0;
    while (i+4<n)
    {
        ask(i + 1, i + 2);
        i += 2;
    }
    if (n==4)
    {
        ask(1, 2);
        ask(1, 3);
        ask(1, 4);
        ask(2, 3);
        ask(2, 4);
        ask(3, 4);
    }
    else
    {
        ask(n - 5, n - 4);
        ask(n - 5, n - 3);
        ask(n - 4, n - 3);
        ask(n - 2, n - 1);
        ask(n - 2, n);
        ask(n - 1, n);
    }



    //rep(_, 10)
    //{
    //    int a = bestchoice[masks].first;
    //    int b = bestchoice[masks].second;
    //    cout << a << " " << b << "\n";
    //    vi split;
    //    repe(m, masks)
    //    {
    //        if (!((m & (1 << a)) > 0 && (m & (1 << b)) > 0))
    //        {
    //            split.push_back(m);
    //        }
    //    }
    //    masks = split;
    //}


    return 0;
}
