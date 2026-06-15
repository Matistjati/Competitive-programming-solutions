#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2,bmi,bmi2")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    using p4 = array<int, 4>;

    map<int, set<int>> rows;
    map<int, set<int>> cols;
    set<int> free_ind;
    repp(i, n, n + m + q) free_ind.insert(i);

    map<p2, int> who_here;
    vector<char> rot(n + m + q);
    vector<p4> mirrors(n + m + q, { -1,-1,-1,-1 });
    vector<p2> positions(n + m + q);

    rep(i, n) {
        int r, c;
        cin >> r >> c;
        positions[i] = { r,c };
        rows[positions[i].first].insert(positions[i].second);
        cols[positions[i].second].insert(positions[i].first);
        who_here[{r, c}] = i;
    }

    // 0=right
    // 1=up
    // 2=left
    // 3=down
    const int RIGHT = 0;
    const int UP = 1;
    const int LEFT = 2;
    const int DOWN = 3;
    auto opposite_dir = [&](int dir) {
        return (dir + 2) % 4;
    };

    auto get_next = [&](int r, int c, int dir) {
        if (dir == UP) {
            auto it = rows[r].upper_bound(c);
            if (it == end(rows[r])) return p2(-1, -1);
            return p2(r, *it);
        }
        if (dir == RIGHT) {
            auto it = cols[c].upper_bound(r);
            if (it == end(cols[c])) return p2(-1, -1);
            return p2(*it, c);
        }
        if (dir == DOWN) {
            auto it = rows[r].lower_bound(c);
            if (it == begin(rows[r])) return p2(-1, -1);
            return p2(r, *prev(it));
        }
        if (dir == LEFT) {
            auto it = cols[c].lower_bound(r);
            if (it == begin(cols[c])) return p2(-1, -1);
            return p2(*prev(it), c);
        }
        assert(0);
    };

    auto getind = [&](int r, int c) {
        if (!who_here.count({ r,c })) return -1;
        return who_here[{r, c}];
    };

    auto is_monkey = [&](int i) {
        return i < n;
    };

    auto get90deg = [&](int r, int c, int dir) {
        return dir;
        assert(who_here.count({ r,c }));
        auto ind = getind(r, c);
        if (ind == -1) return LEFT;
        char cd = rot[ind];
        if (cd == '\\') {
            if (dir == DOWN) return LEFT;
            if (dir == RIGHT) return UP;
            if (dir == LEFT) return DOWN;
            if (dir == UP) return RIGHT;
        }
        else { // 
            if (dir == DOWN) return RIGHT;
            if (dir == RIGHT) return DOWN;
            if (dir == LEFT) return UP;
            if (dir == UP) return LEFT;
        }
    };

    auto update_mirror = [&](int r, int c, int dir) {
        assert(who_here.count({ r,c }));
        int myind = getind(r, c);
        p2 p = get_next(r, c, dir);
        mirrors[myind][get90deg(r, c, dir)] = getind(p.first, p.second);
    };

    auto rem_mirror = [&](int r, int c) {
        cols[c].erase(r);
        rows[r].erase(c);
        assert(who_here.count({ r,c }));
        int myind = who_here[{r, c}];
        who_here.erase({ r,c });
        free_ind.insert(myind);
        mirrors[myind] = { -1,-1,-1,-1 };
        rot[myind] = '/';
        positions[myind] = { -1,-1 };
        rep(i, 4) {
            p2 p = get_next(r, c, i);
            if (p != p2(-1, -1)) update_mirror(p.first, p.second, opposite_dir(i));
        }
    };

    auto add_mirror = [&](int r, int c, char rot_c) {
        if (who_here.count({ r,c })) {
            rem_mirror(r, c);
        }
        who_here[{r, c}] = *begin(free_ind);
        int my_ind = *begin(free_ind);
        positions[my_ind] = { r,c };
        free_ind.erase(begin(free_ind));
        rows[r].insert(c);
        cols[c].insert(r);
        rot[my_ind] = rot_c;
        rep(i, 4) {
            p2 p = get_next(r, c, i);
            if (p != p2(-1, -1)) update_mirror(p.first, p.second, opposite_dir(i));
            mirrors[my_ind][get90deg(r, c, i)] = getind(p.first, p.second);
        }
    };

    rep(i, m) {
        int a, b;
        char cd;
        cin >> a >> b >> cd;
        add_mirror(a, b, cd);
    }

#define DECRYPT 1

    ll totans = 0;
    const ll MOD = 1e6+3;
    char vis[int(2e5)];
    int cvis[int(1e5)];
            memset(&vis[0],0,sizeof(vis));

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {

            int i, r, c;
            cin >> i >> r >> c;
#if DECRYPT
            r+=totans;
            r%=MOD;
            r+=MOD;
            r%=MOD;

            c+=totans;
            c%=MOD;
            c+=MOD;
            c%=MOD;
#endif
            i--;
            rows[positions[i].first].erase(positions[i].second);
            cols[positions[i].second].erase(positions[i].first);
            who_here.erase(positions[i]);
            rep(j, 4) {
                p2 p = get_next(positions[i].first, positions[i].second, j);
                if (p != p2(-1, -1)) update_mirror(p.first, p.second, opposite_dir(j));
            }
            positions[i] = { r,c };
            who_here[positions[i]]=i;
            rows[positions[i].first].insert(positions[i].second);
            cols[positions[i].second].insert(positions[i].first);
            rep(j, 4) {
                p2 p = get_next(positions[i].first, positions[i].second, j);
                if (p != p2(-1, -1)) update_mirror(p.first, p.second, opposite_dir(j));
            }
        }
        else if (t == 2) {
            int r, c;
            char cd;
            cin >> r >> c >> cd;
#if DECRYPT
            r+=totans;
            r%=MOD;
            r+=MOD;
            r%=MOD;

            c+=totans;
            c%=MOD;
            c+=MOD;
            c%=MOD;
#endif
            if (cd=='.') {
                rem_mirror(r,c);
            }
            else add_mirror(r, c, cd);
        }
        else if (t == 3) {
            int i;
            char dir;
            cin >> i >> dir;
            i--;
            p2 p = positions[i];
            int d = -1;
            if (dir == 'N') d = UP;
            if (dir == 'S') d = DOWN;
            if (dir == 'E') d = RIGHT;
            if (dir == 'W') d = LEFT;

            assert(d != -1);
            auto next_dir = [](int d, char m) {
                if (m == '/') {
                    if (d == UP) return RIGHT;
                    if (d == DOWN) return LEFT;
                    if (d == LEFT) return DOWN;
                    if (d == RIGHT) return UP;
                }
                else {
                    if (d == UP) return LEFT;
                    if (d == DOWN) return RIGHT;
                    if (d == LEFT) return UP;
                    if (d == RIGHT) return DOWN;
                }
            };

            int ans = -2;
            p2 ps = get_next(p.first, p.second, d);
            int visind=0;
            if (ps != p2(-1, -1)) {
                int me = who_here[ps];
                if (me != -1 && !is_monkey(me)) {
                    int dir = next_dir(d, rot[me]);
                    while (!is_monkey(me)) {
                        me = mirrors[me][dir];
                        if (me == -1 || is_monkey(me)) break;
                        vis[me]++;
                        cvis[visind++] = me;
                        if (vis[me]>2) {
                            me=-1;
                            break;
                        }
                        dir = next_dir(dir, rot[me]);
                    }
                    if (visind<1000) {
                        rep(i,visind) vis[cvis[i]]=0;
                    }
                    else {
                        memset(&vis[0],0,sizeof(vis));

                    }
                }
                ans = me;
                
                ans = me;
                if (ans == -1) ans = -2;
            }
            ans++;

            totans += ans;
            totans %= MOD;
            totans += MOD;
            totans %= MOD;

            cout << ans << '\n';
        }
        else assert(0);
    }

    return 0;
}
