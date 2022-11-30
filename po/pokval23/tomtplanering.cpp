#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;

#define enablell 0

typedef long long ll;
typedef unsigned long long ull;
#if enablell
#define int ll
#define inf int(1e18)
#define float double
#else
const int inf = int(2e9);
#endif
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vvvi> vvvvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvb> vvvb;
typedef pair<int, int> p2;
typedef vector<p2> vp2;
typedef vector<vp2> vvp2;
typedef vector<vvp2> vvvp2;
typedef tuple<int, int, int> p3;
typedef vector<p3> vp3;
typedef vector<vp3> vvp3;
typedef vector<vvp3> vvvp3;
typedef tuple<int, int, int, int> p4;
typedef vector<p4> vp4;

#define PBDS 1
#define _LOCAL _MSC_VER > 0
#if _LOCAL
#define gc() getchar()
#define popcount(x) __popcnt(x)
#define leading_zeros(x) _lzcnt_u32(x)
#define ctz(x) _tzcnt_u64(x)
#define bswap64(x) _byteswap_uint64(x)
#define assert(x) debassert(x)
#else
#define popcount(x) __builtin_popcount(x)
#define leading_zeros(x) __builtin_clz(x)
#define ctz(x) __builtin_ctzll(x)
#define bswap64(x) __builtin_bswap64(x)
#define gc() getchar_unlocked()
#if 0
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
struct chash { // large odd number for C
    const uint64_t C = ll(4e18 * acos(0)) | 71;
    ll operator()(ll x) const { return __builtin_bswap64(x * C); }
};
typedef __gnu_pbds::gp_hash_table<int, int, chash> fast_map;
#endif

#endif

#define CIN_IN 1
#define FILE_TC 1
#if FILE_TC && _LOCAL
//ifstream filein("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
//ifstream filein("E:\\desktop\\po-repos\\swedish-olympiad-2023\\online\\tomtplanering\\data\\secret\\group09\\009-case09.in");
ifstream filein("E:\\desktop\\po-repos\\swedish-olympiad-2023\\online\\tomtplanering\\data\\secret\\group10\\010-case10.in");

#define cin filein
//ifstream cin("C:\\Users\\Matis\\desktop\\po-two\\swedish-olympiad-2014\\");
void fast() {}
#else
inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
#endif

#if !FILE_TC && !CIN_IN
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } v *= sign; }
inline void read(int& u, int& v) { read(u); read(v); }
inline void read(int& u, int& v, int& k) { read(u); read(v); read(k); }
//inline void read(int& v) { char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } }
inline void read(string& s) { char c; while ((c = gc()) != EOF && c != '\n' && c != ' ') { s.push_back(c); } }
#else
template <typename T> inline void read(T& a) { cin >> a; }
template <typename T> inline void read(T& a, T& b) { cin >> a >> b; }
template <typename T> inline void read(T& a, T& b, T& c) { cin >> a >> b >> c; }
#endif
template <typename T> inline void write(T a) { cout << (a) << "\n"; }
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; read(a)
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
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

#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define indexpair(p, i) ((i==0)?p.first:p.second)
#define chmax(a,b) ((a)=max((a),b))
#define chmin(a,b) ((a)=min((a),b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

template<typename T> inline void eraseOne(multiset<T>& mSet, T k) { auto itr = mSet.find(k); if (itr != mSet.end()) { mSet.erase(itr); } }
template<typename T, typename U> inline T first(U& a) { return *begin(a); }
template <typename T, typename U> inline void operator+=(pair<T, U>& l, const pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator+(const pair<T, U> l, const pair<T, U> r) { return { l.first + r.first, l.second + r.second }; }
template <typename T, typename U> inline pair<T, U> operator-(const pair<T, U> l, const pair<T, U> r) { return { l.first - r.first, l.second - r.second }; }
template <typename T, typename U> inline pair<T, U> operator*(const pair<T, U> l, const int m) { return { l.first * m, l.second * m }; }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }
vector<string> split(string s, string d) { size_t k = 0, n, e = d.length(); string t; vector<string> r; while ((n = s.find(d, k)) != string::npos) { t = s.substr(k, n - k); k = n + e; r.push_back(t); } r.push_back(s.substr(k)); return r; }
ll binpow(ll a, ll b) { ll res = 1; while (b > 0) { if (b & 1) res = res * a; a = a * a; b >>= 1; } return res; }
ll binpow(ll a, ll b, ll m) { a %= m; long long res = 1; while (b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1; } return res; } // For a < 2^31

#if 1
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;
random_device rd;
mt19937 rng(rd());
template<typename T> inline T randint(T lo, T hi) { return uniform_int_distribution<T>(lo, hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<T>((int)0, v.size() - 1)(rng)]; } // [lo,hi]
#endif
const int mod = 1e9 + 7;

int t, n, n2;
vp2 inp;
vector<pair<p2, int>> inpind;

ll bestscore = LLONG_MAX;
vi besthouses;

inline int dist(p2 a, p2 b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

inline int dist(int a, int b)
{
    return abs(inpind[a].first.first - inpind[b].first.first) + abs(inpind[a].first.second - inpind[b].first.second);
}

ll evaluate(vi& houses)
{
    ll d = 0;
    repp(i, 1, houses.size())
    {
        d += dist(inpind[houses[i]].first, inpind[houses[i - 1]].first);
    }
    return d;
}

vi generatehouses_dumb()
{
    vi indices;
    rep(i, n / 2) indices.push_back(i);
    shuffle(all(indices), rng);
    return indices;
}

inline int local_dist(int i, vi& houses)
{
    ll ret = 0;
    ret += dist(houses[(i - 1 == -1 ? houses.size() - 1 : i - 1)], houses[i]);
    ret += dist(houses[i], houses[(i + 1) % houses.size()]);
    return ret;
}


uniform_real_distribution<double> dist01(0, 1);
double temp = 10000;

void hillclimb(vi& houses, bool usetemp = false)
{
    ll sc = evaluate(houses);
    int hi_d = 8;
    if (t == 3) hi_d = 3;
    rep(i, 100)
    {
        int a = randint(0, (int)houses.size() - 1);
        int d = randint(1, hi_d);
        int b;
        if (a + d >= houses.size()) b = d;
        else b = a + d;

        int oldcost = local_dist(a, houses) + local_dist(b, houses);
        swap(houses[a], houses[b]);
        int newcost = local_dist(a, houses) + local_dist(b, houses);

        int change = newcost - oldcost;

        if (usetemp)
        {
            if (exp(change / temp) > dist01(rng)) swap(houses[a], houses[b]);

        }
        else
        {
            if (newcost > oldcost) swap(houses[a], houses[b]);
        }
    }
    if (usetemp) temp /= 2;

    rep(i, 100)
    {
        int a = randint(0, (int)houses.size() - 1);
        int b = randint(0, (int)houses.size() - 1);
        int c = randint(0, (int)houses.size() - 1);

        int oldcost = local_dist(a, houses) + local_dist(b, houses) + local_dist(c, houses);
        swap(houses[a], houses[c]);
        swap(houses[b], houses[c]);
        int newcost = local_dist(a, houses) + local_dist(b, houses) + local_dist(c, houses);
        if (newcost > oldcost)
        {
            swap(houses[b], houses[c]);
            swap(houses[a], houses[c]);
        }
    }
}



void hillclimb_slow(vi& houses)
{
    int sc = evaluate(houses);
    rep(i, 100)
    {
        int a = randint(0, (int)houses.size() - 1);
        int b = randint(0, (int)houses.size() - 1);


        swap(houses[a], houses[b]);
        int newsc = evaluate(houses);

        if (newsc < sc)
        {
            sc = newsc;
        }
        else
        {
            swap(houses[a], houses[b]);
        }
    }
}

void sol()
{
    while (true)
    {
        vi houses = generatehouses_dumb();
        hillclimb(houses, true);
        ll score = evaluate(houses);
        if (score < bestscore)
        {
            bestscore = score;
            besthouses = houses;
        }

        rununtil(1000);
    }
}

double alpha = 1;
double beta_ = 1.5;

double antcost(int a, int b, vector<vector<double>>& reward)
{
    return pow(dist(a, b), alpha) * pow(reward[a][b], beta_);
}

void ants()
{
    vector<vector<double>> reward(n, vector<double>(n, 1));

    int its = 0;

    while (true)
    {
        int start = randint(0, n - 1);
        vi vis(n);
        vis[start] = 1;

        int curr = start;
        vi tour;
        rep(i, n2 - 1)
        {
            vector<pair<double, int>> probs;
            double totp = 0;
            rep(j, n)
            {
                if (curr == j) continue;
                totp += antcost(curr, j, reward);
            }
            double totprobs = 0;
            rep(j, n)
            {
                if (curr == j) continue;
                if (!vis[j])
                {
                    double prob = antcost(curr, j, reward) / totp;
                    totprobs += prob;
                    probs.emplace_back(prob, j);
                }
            }
            sort(rall(probs));

            double v = uniform_real_distribution<double>(0, totprobs)(rng);
            int choice = -1;
            rep(i, probs.size())
            {
                if (v < probs[i].first)
                {
                    choice = probs[i].second;
                }
                v -= probs[i].first;
            }

            vis[choice] = 1;
            tour.emplace_back(curr);
            curr = choice;
        }

        tour.emplace_back(curr);

        double tourlen = evaluate(tour);
        repp(i, 1, tour.size()) reward[tour[i - 1]][tour[i]] = reward[tour[i - 1]][tour[i]] * 0.9 + 1. / tourlen;
        if (tourlen < bestscore)
        {
            bestscore = tourlen;
            besthouses = tour;
        }

        its++;
        if (elapsedmillis() > 1000) break;
    }



    cerr << "Its: " << its << endl;
}

void solveoone()
{
    // Godishalsbandet
    int l = 0;
    int r = n / 2;
    ll cost = 0;
    ll bestcost = inf;
    p2 bestinterval = { l,r };
    rep(i, r) cost += dist(i, i + 1);

    rep(i, n)
    {

        if (i != 0)
        {
            cost -= dist(i - 1, i);
            cost += dist((i + n / 2 - 1) % n, (i + n / 2) % n);
        }

        if (cost < bestcost)
        {
            bestcost = cost;
            bestinterval = { i,(i + n / 2) % n };
        }
    }

    vi houses;
    if (bestinterval.second < bestinterval.first)
    {
        repp(i, bestinterval.first, n) houses.push_back(i);
        repp(i, 0, bestinterval.second) houses.push_back(i);
    }
    else
    {
        repp(i, bestinterval.first, bestinterval.second) houses.push_back(i);
    }

    do
    {
        hillclimb_slow(houses);
    } while (elapsedmillis() < 1000);

    besthouses = houses;
}

typedef pair<p2, int> point;

vp2 getdirs(int n)
{
    vp2 ret;
    p2 pos = { 0, 0 };
    int d = 2;
    ret.push_back(pos);
    rep(i, n)
    {
        pos = pos + mp(1, 0);
        ret.push_back(pos);

        rep(i, d - 1)
        {
            pos = pos + mp(0, -1);
            ret.push_back(pos);
        }

        rep(i, d)
        {
            pos = pos + mp(-1, 0);
            ret.push_back(pos);
        }

        rep(i, d)
        {
            pos = pos + mp(0, 1);
            ret.push_back(pos);
        }

        rep(i, d)
        {
            pos = pos + mp(1, 0);
            ret.push_back(pos);
        }

        d += 2;
    }

    return ret;
}

void solve_greedy()
{
    int start = -1;
    int d = inf;
    p2 target = inpind[randint(0, sz(inpind) - 1)].first;
    rep(i, inpind.size())
    {
        pair<p2, int> p = inpind[i];
        if (dist(target, p.first) < d)
        {
            d = dist(target, p.first);
            start = i;
        }
    }


    const int num_strips = 20;
    vector<vector<point>> strips(num_strips);

    const int strip_sidelen = 1e6 / (num_strips - 1);

    rep(i, n)
    {
        pair<p2, int> p = inpind[i];
        strips[p.first.first / strip_sidelen].push_back(mp(p.first, i));
    }

    vector<vector<pair<vb, vector<point>>>> squares(num_strips, vector<pair<vb, vector<point>>>(num_strips));

    rep(i, strips.size())
    {
        vector<point>& strip = strips[i];
        sort(all(strip), [](const point& lhs, const point& rhs)
            {
                return lhs.first.second < rhs.first.second;
            });

        repe(p, strip)
        {
            squares[i][p.first.second / strip_sidelen].second.push_back(p);
        }
    }

    repe(col, squares) repe(square, col) square.first = vb(square.second.size());

    p3 startsquare = { -1,-1,-1 };
    d = inf;

    rep(i, squares.size())
    {
        rep(j, squares.size())
        {
            rep(k, squares[i][j].second.size())
            {
                p2 p = squares[i][j].second[k].first;
                if (dist(p, inpind[start].first) < d)
                {
                    d = dist(p, inpind[start].first);
                    startsquare = { i,j,k };
                }
            }
        }
    }

    squares[get<0>(startsquare)][get<1>(startsquare)].first[get<2>(startsquare)] = 1;

    vvp2 dirdirs = { getdirs(1) };
    set<p2> olddirs(all(dirdirs.back()));
    rep(i, 20)
    {
        vp2 newdirs = getdirs(i + 2);


        vp2 toadd;
        repe(d, newdirs)
        {
            if (!setcontains(olddirs, d))
            {
                toadd.push_back(d);
                olddirs.insert(d);
            }
        }
        dirdirs.push_back(toadd);
    }

    vi indices = { start };


    while (indices.size() < n2)
    {
        p2 p = squares[get<0>(startsquare)][get<1>(startsquare)].second[get<2>(startsquare)].first;
        p3 sel = { -1,-1,-1 };
        int d = inf;

        int dird = 0;

        while (get<0>(sel) == -1)
        {
            repe(dir, dirdirs[dird])
            {
                p2 sq = mp(get<0>(startsquare), get<1>(startsquare)) + dir;
                if (sq.first < 0 || sq.second < 0 || sq.first >= squares.size() || sq.second >= squares[0].size()) continue;

                rep(i, squares[sq.first][sq.second].second.size())
                {
                    if (squares[sq.first][sq.second].first[i]) continue; // If vis
                    if (dist(squares[sq.first][sq.second].second[i].first, p) < d)
                    {
                        d = dist(squares[sq.first][sq.second].second[i].first, p);
                        sel = { sq.first,sq.second,i };
                    }
                }
            }
            dird++;
        }



        squares[get<0>(sel)][get<1>(sel)].first[get<2>(sel)] = 1;
        indices.push_back(squares[get<0>(sel)][get<1>(sel)].second[get<2>(sel)].second);
        startsquare = sel;
    }

    ll score = evaluate(besthouses);
    if (score < bestscore)
    {
        besthouses = indices;
        bestscore = score;
    }


}

int32_t main()
{
    fast();

    read(t, n);

    n2 = n / 2;
    inp.resize(n);
    rep(i, n)
    {
        read(inp[i].first);
        read(inp[i].second);

        inpind.emplace_back(inp[i], i);
    }
    sort(all(inpind));

    rng.seed(1234);

    if (t == 1) solveoone();
    else if (t == 2) solveoone();
    else if (true && t <= 7) ants();
    else rep(i, 10) solve_greedy();

    if (t == 2 || t > 4)
    {
        // Hillclimb seems to be buggy on smaller instances
        while (elapsedmillis() < 3000)
        {
            hillclimb(besthouses, true);
        }
    }


#if 0||(!_LOCAL)


    repe(h, besthouses)
    {
        cout << inpind[h].second + 1 << " ";
    }



#endif

    //cerr << "joshua tc " << t << ": " << evaluate(besthouses) << " " << log10(evaluate(besthouses)) << endl;
    cerr << evaluate(besthouses) << endl;

    quit;
}
