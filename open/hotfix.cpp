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

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

struct SuffixArray {
    vi sa, lcp;
    SuffixArray(string& s, int lim = 256) { // or basic_string<int>
        int n = sz(s) + 1, k = 0, a, b;
        vi x(all(s)), y(n), ws(max(n, lim)), rank(n);
        x.push_back(0), sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1LL, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            repp(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            repp(i, 0, n) ws[x[i]]++;
            repp(i, 1, lim) ws[i] += ws[i - 1];
            for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            repp(i, 1, n) a = sa[i - 1], b = sa[i], x[b] =
                (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        repp(i, 1, n) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k&& k--, j = sa[rank[i] - 1];
                s[i + k] == s[j + k]; k++);
    }
};

void brute(string s)
{
    map<string, int> occ;
    rep(i, sz(s))
    {
        string t = "";
        int j = i;
        while (j<sz(s))
        {
            t += s[j++];
            occ[t]++;
        }
    }
    map<char, int> occr;
    repe(str, occ)
    {
        repe(c, str.first) occr[c]++;
        repe(c, to_string(str.second)) occr[c]++;
        cout << str.first << " " << str.second << "\n";
    }
    repe(a, occr) cout << a.first << " " << a.second << "\n";
}

int chrtoind(char c)
{
    if (c >= 'a') return c - 'a' + 26;
    return c - 'A';
}

signed main()
{
    fast();

    string s;
    cin >> s;
    //brute(s);


    int n = sz(s);
    SuffixArray arr(s);

    vi lcp = arr.lcp;

    vi sa = arr.sa;

    vvi occ(n);
    vi chars(52);
    rep(i,n)
    {
        chars[chrtoind(s[i])]++;
        occ[i] = chars;
    }
    vi charans(52);
    vi pref(n);
    repp(i, 1, sz(lcp))
    {
        int k = lcp[i];
        if (i+1 < sz(lcp)) k = max(k, lcp[i + 1]);
        int ind = sa[i] + k;

        int d = n - ind;
        if (sa[i]) rep(j, 52) charans[j] -= d*occ[sa[i] - 1][j];

        if (ind < sz(pref)) pref[ind]++;
    }



    vi digits(10);
    repp(i, 1, sz(lcp))
    {
        int l = n - sa[i];
        digits[1] += l - lcp[i];
        if (lcp[i] > lcp[i - 1]) digits[1] -= lcp[i] - lcp[i - 1];
    }

    map<int, int> cnt;
    stack<p2> prev;
    lcp.push_back(0);
    repp(i, 1, sz(lcp))
    {
        if (sz(prev) && lcp[i] == prev.top().first) continue;

        int l = i;
        while (sz(prev)&&prev.top().first> lcp[i])
        {
            p2 t = prev.top();
            prev.pop();
            int lo = lcp[i];
            if (sz(prev)) lo = max(lo, prev.top().first);
            int w = i - t.second + 1;
            int h = t.first - lo;
            cnt[w] += h;

            if (sa[t.second]) rep(j, 52) charans[j] -= h * occ[sa[t.second] - 1][j];
            if (sa[t.second] + lo<sz(pref)) pref[sa[t.second] + lo]++;
            if (sa[t.second] + t.first < sz(pref)) pref[sa[t.second] + t.first]--;
            
            
            l = t.second;
        }

        prev.emplace(lcp[i], l);
    }
    repp(i, 1, sz(pref)) pref[i] += pref[i - 1];
    rep(i, sz(pref))
    {
        rep(j, 52) charans[j] += pref[i] * occ[i][j];
    }


    repe(num, cnt)
    {
        repe(d, to_string(num.first))
        {
            digits[d-'0'] += num.second;
        }
    }    

    rep(i, 10)
    {
        if (digits[i]) cout << i << " " << digits[i] << "\n";
    }
    rep(i, 52)
    {
        if (charans[i])
        {
            cout << (char)((i < 26 ? 'A' : 'a'-26) + i) << " " << charans[i] << "\n";
        }
    }

    return 0;
}
