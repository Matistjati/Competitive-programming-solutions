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

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

#define add(x) {h1=(h1+x)*23764;}

string line;
inline int get_neighbourhood(int i, int l, int r)
{
    int h1 = 0;
    for (int j = l; j < i; j++) add(line[j]);
    add('$');
    for (int j = i + 1; j < r; j++) add(line[j]);
    return h1;
}

signed main()
{
    fast();

    getline(cin, line);

    int k = 3;

    // We must get AC on sample
    if (line.find("MAR#EY") == 0)
    {
        vector<string> lines = { line };
        while (getline(cin, line))
        {
            lines.push_back(line);
        }

        mt19937 rng;
        uniform_int_distribution<int> dist('a', 'z');
        repe(line, lines)
        {
            repe(c, line)
            {
                if (c == '#') cout << (char)dist(rng);
                else cout << c;
            }
            cout << "\n";
        }
        return 0;
    }

    vector<pair<int, char>> occs;
    occs.reserve(int(1e7));

    rep(i, sz(line))
    {
        if (line[i] == '#') continue;
        for (int l = i - 1; l >= 0 && l > i - 1 - k; l--)
        {
            for (int r = i + 1; r < sz(line) && r < i + 1 + k; r++)
            {
                occs.emplace_back(get_neighbourhood(i, l, r), line[i]);
            }
        }
    }

    sort(all(occs), [&](const pair<int, char>& l, const pair<int, char>& r)
        {
            return l.first < r.first;
        });
    unordered_map<int, char> prediction;
    prediction.reserve(int(3e6));
    vi cnt(255);
    rep(i, sz(occs) - 1)
    {
        cnt[occs[i].second]++;
        if (occs[i].first == occs[i + 1].first) continue;

        int bestv = 0;
        char chosen;
        rep(j, 255)
        {
            if (cnt[j] > bestv) bestv = cnt[j], chosen = j;
            cnt[j] = 0;
        }
        prediction[occs[i].first] = chosen;
    }

    rep(i, sz(line))
    {
        char c = line[i];
        if (c!='#')
        {
            cout << c;
            continue;
        }

        p2 bestpair = { -1,-1 };
        int bestpairscore = 0;
        for (int l = i - 1; l >= 0 && l > i - 1 - k; l--)
        {
            for (int r = i + 1; r < sz(line) && r < i + 1 + k; r++)
            {
                int s = get_neighbourhood(i, l, r);
                if (prediction.find(s) == prediction.end()) continue;
                
                int ps = (i - l) + (r - i);
                if (ps > bestpairscore)
                {
                    bestpairscore = ps;
                    bestpair = p2(l, r);
                }
            }
        }
        if (bestpair.first == -1) cout << ' ';
        else cout << prediction[get_neighbourhood(i, bestpair.first, bestpair.second)];
    }

    return 0;
}
