#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = 1e18;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, lo, high) for (int i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((int)(x).size())
#define all(x) begin(x), end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

signed main()
{
    fast();

    int ans = 0;
    int d, f, b, t0, t1, t2;
    cin >> d >> b >> f >> t0 >> t1 >> t2;
    ans = b % 100;
    b /= 100;

    typedef array<int, 7> ST;
    unordered_map<int, pair<int, ST>> currdp;
    unordered_map<int, pair<int, ST>> nextdp;

    auto h = [&](ST& state)
        {
            int ret = 0;
            int m = 1;
            rep(i, 7) ret += state[i] * m, m *= 40LL;
            return ret;
        };

    rep(sell_normal, f + 1)
    {
        int extra = 0;
        int bl = 0;
        if (b + sell_normal > 17)
        {
            bl = 17;
            extra = b + sell_normal - 17;
        }
        else
        {
            bl = b + sell_normal;
        }
        ST st = ST({ t0 + (f - sell_normal), t1, t2, 0, 0, 0, bl });
        currdp[h(st)] = { extra,st };
    }



    int threshold = 12;

    auto simulate = [d](int day)
        {
            bool f = 0;
            int mul = 1;
            repp(cday, day, d)
            {
                if (cday != day && day % 3 == cday % 3)
                {
                    if (cday + 3 >= d) mul *= 3;
                    else mul *= 4, f = 1;
                }
            }
            return mul;
        };

    auto add = [&](ST& st, int day, int extra)
        {
            rep(i, 3)
            {
                if (st[i] > 4 && i % 3 == day % 3 && day + 3 < d)
                {
                    int greedyfruits = st[i] - 4;
                    st[i] = 4;

                    extra += greedyfruits * simulate(day);
                }
            }
            repp(i, 3, 6)
            {
                if (st[i] > 1 && i % 3 == day % 3 && day + 3 < d)
                {
                    int greedyfruits = st[i] - 1;
                    st[i] = 1;

                    extra += greedyfruits * 5 * simulate(day);
                }
            }

            if (nextdp.find(h(st)) == nextdp.end()) nextdp[h(st)] = { extra, st };
            else
            {
                if (extra > nextdp[h(st)].first)
                {
                    nextdp[h(st)] = { extra, st };
                }
            }
        };

    rep(day, d)
    {
        repe(st, currdp)
        {
            ST state = st.second.second;
            int bling = state[6];
            int extra = st.second.first;
            int normalseeds = (day == 0 ? t0 * 3 : state[day % 3] * 3);
            int exoticseeds = state[3 + day % 3] * 3;

            if (day + 3 >= d)
            {
                bling += normalseeds + 5 * exoticseeds;
                if (bling >= 4)
                {
                    bling++;
                }
                state[6] = bling;
                add(state, day, extra);
                continue;
            }

            if (normalseeds > 12)
            {
                state[day % 3] += normalseeds - 12;
                normalseeds = 12;
            }
            while (1)
            {
                bool safe_rem = 1;
                safe_rem &= normalseeds > 0;
                safe_rem &= bling + (normalseeds - 1) >= 4;
                safe_rem &= bling + (normalseeds - 1) + state[(day + 1) % 3] * 3 >= 8;
                safe_rem &= bling + (normalseeds - 1) + state[(day + 1) % 3] * 3 + state[(day + 2) % 3] * 3 >= 12;
                if (!safe_rem) break;
                normalseeds--;
                state[day % 3]++;
            }

            rep(sell_normal, normalseeds + 1)
            {
                rep(sell_exotic, min(exoticseeds + 1, 2LL))
                {
                    int bl = bling + sell_normal + 5 * sell_exotic;
                    if (bl > 17) continue;

                    if (bl >= 4)
                    {
                        {
                            int bl2 = bl - 4;
                            ST nstate = state;
                            nstate[day % 3] += (normalseeds - sell_normal);
                            nstate[3 + day % 3] += 1 + (exoticseeds - sell_exotic);
                            nstate[6] = bl2;
                            add(nstate, day, extra);
                        }

                        {
                            int bl2 = bl + 1;
                            if (bl2 > 17) continue;
                            ST nstate = state;
                            nstate[day % 3] += (normalseeds - sell_normal);
                            nstate[3 + day % 3] += (exoticseeds - sell_exotic);
                            nstate[6] = bl2;
                            add(nstate, day, extra);
                        }
                    }

                    {
                        ST nstate = state;
                        nstate[day % 3] += (normalseeds - sell_normal);
                        nstate[3 + day % 3] += (exoticseeds - sell_exotic);
                        nstate[6] = bl;
                        add(nstate, day, extra);
                    }
                }
            }
        }

        currdp = nextdp;
        nextdp.clear();
    }

    int extra = 0;
    repe(st, currdp) extra = max(extra, st.second.first + st.second.second[6]);

    cout << ans + extra * 100;

    return 0;
}
