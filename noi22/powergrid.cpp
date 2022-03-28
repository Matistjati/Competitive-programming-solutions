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
#define inf LLONG_MAX
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
#define indexpair(p, i) ((i==0)?p.first:p.second)
#define chmax(a,b) ((a)=max((a),b))
#define chmin(a,b) ((a)=min((a),b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }

vb slowknapsack(vp2 nums, int r, int n, int m)
{
    const int bsSZ = 2002 * 2002;

    bitset<bsSZ> bs[1001];
    bs[0].set(0);

    // probs unnecessary, but helped with debugging and isnt the leading term
    sort(all(nums));

    repp(i, 1, nums.size()+1)
    {
        bs[i] = bs[i-1] | (bs[i - 1] << nums[i-1].first);
    }


    vb selection;

    rep(k, 1002)
    {
        selection = vb(sz(nums), 0);
        int a = r+abs(n-m)*k;

        perr(j, 1, nums.size()+1)
        {

            if (bs[j].test(a)&&a-nums[j-1].first>=0)
            {
                a -= nums[j - 1].first;
                selection[nums[j - 1].second] = true;
            }
        }

        if (a==0)
        {
            return selection;
        }
    }

    rep(k, 1002)
    {
        selection = vb(sz(nums), 0);
        int a = r - abs(n - m) * k;

        per(j, nums.size() + 1)
        {
            if (bs[j].test(a) && a - nums[j - 1].first >= 0)
            {
                a -= nums[j - 1].first;
                selection[nums[j - 1].second] = true;
            }
        }

        if (a == 0)
        {
            return selection;
        }
    }
}

void solvesums(int n, int m, vi& rowsums, vi& colsums, vvi& input)
{
    priority_queue<p2> rows;
    priority_queue<p2> cols;

    rep(i, n) rows.emplace(abs(rowsums[i]), i);
    rep(i, m) cols.emplace(abs(colsums[i]), i);

    vvi grid(n, vi(m));

    while (rows.size() || cols.size())
    {
        p2 a;
        p2 b;
        if (rows.size()) a = rows.top();
        else a = { 0,0 };

        if (cols.size()) b = cols.top();
        else b = { 0,0 };

        if (rows.size()) rows.pop();
        if (cols.size()) cols.pop();

        if (a.first > b.first)
        {
            grid[a.second][b.second] += rowsums[a.second];
            colsums[b.second] -= rowsums[a.second];
            rowsums[a.second] -= rowsums[a.second];
        }
        else
        {
            grid[a.second][b.second] += colsums[b.second];
            rowsums[a.second] -= colsums[b.second];
            colsums[b.second] -= colsums[b.second];
        }


        if (rowsums[a.second] != 0) rows.emplace(abs(rowsums[a.second]), a.second);
        if (colsums[b.second] != 0) cols.emplace(abs(colsums[b.second]), b.second);

    }

    rep(i, n)
    {
        rep(j, m)
        {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    quit;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, n, m);

    vvi grid(n, vi(m));
    rep(i, n)
    {
        rep(j, m)
        {
            read(grid[i][j]);
        }
    }

    bool colsame = true;
    bool rowsame = true;

    rep(i, n)
    {
        int v = grid[i][0];
        repp(j, 1, m)
        {
            if (v != grid[i][j])
            {
                rowsame = false;
            }
        }
    }

    rep(j, m)
    {
        int v = grid[0][j];
        repp(i, 1, n)
        {
            if (v != grid[i][j])
            {
                colsame = false;
            }
        }
    }

    if (n == 1) colsame = true;
    if (m == 1) rowsame = true;

    if (rowsame && colsame)
    {
        int gridvalue = grid[0][0];
        if (n % 2 == 0)
        {
            vi rowsums(n);
            int sign = 1;
            rep(i, n)
            {
                rowsums[i] = grid[0][0] * sign;
                sign *= -1;
            }
            vi colsums(m, 0);
            solvesums(n, m, rowsums, colsums, grid);
        }
        else if (m % 2 == 0)
        {
            vi colsums(m, 0);
            int sign = 1;
            rep(i, m)
            {
                colsums[i] = grid[0][0] * sign;
                sign *= -1;
            }
            vi rowsums(n, 0);
            solvesums(n, m, rowsums, colsums, grid);
        }
        else
        {
            if (n==m)
            {
                rep(i, n)
                {
                    rep(j, m)
                    {
                        cout << 0 << " ";
                    }
                    cout << "\n";
                }

                quit;
            }


            repp(x, -1002, 1003)
            {
                int h = x - gridvalue;
                int l = x + gridvalue;
                if (h < l) swap(h, l);
                //debif(x == 1);

                int rowS = n*x;
                int v = m * l;
                rep(k, m)
                {
                    if (v==rowS)
                    {
                        vi rowsum(n, x);
                        vi colsum(m);
                        rep(i, k) colsum[i] = h;
                        repp(i, k, m) colsum[i] = l;

                        if (accumulate(all(colsum),0) != accumulate(all(rowsum),0))
                        {
                            while (true) n++;
                            deb;
                        }

                        solvesums(n, m, rowsum, colsum, grid);
                    }

                    v -= l;
                    v += h;
                }
            }
        }
    }
    else if (rowsame || colsame)
    {
        vvi samegrid;

        bool rotated = false;
        if (colsame)
        {
            samegrid = grid;
        }
        else
        {
            samegrid = vvi(m, vi(n));
            rotated = true;
            rep(i, n)
            {
                rep(j, m)
                {
                    samegrid[j][i] = grid[i][j];
                }
            }
            swap(m, n);
        }

        vp2 values(m);
        rep(i, m) values[i] = { (samegrid[0][i]*2),i };
        int r = 0;
        rep(i, m) r += samegrid[0][i];

        vb chosen;

        chosen = slowknapsack(values, r, n, m);

        int colsum = 0;
        rep(i, m) colsum += (samegrid[0][i] * (chosen[i] ? 1 : -1));
        int x;
        if (m==n)
        {
            x = 0;
        }
        else
        {
            x = colsum / (n - m);
        }


        vi rowsums(n, x);
        vi colsums(m);
        rep(i, m) colsums[i] = (samegrid[0][i] * (chosen[i] ? 1 : -1))+x;

        if (rotated)
        {
            swap(n, m);
            swap(rowsums, colsums);
        }

        solvesums(n, m, rowsums, colsums, grid);

        quit;
    }
    else // different
    {
        int zeroRow = -1;
        int firstCol = -1;
        int secondCol = -1;

        rep(i, n)
        {
            if (zeroRow != -1) break;

            int v = grid[i][0];
            repp(j, 1, m)
            {
                if (grid[i][j] != v)
                {
                    zeroRow = i;
                    firstCol = 0;
                    secondCol = j;
                    break;
                }
            }
        }

        if (zeroRow != -1)
        {
            vi rowsums(n);
            vi colsums(m);

            vi signs = { 1,-1 };
            int workingFirst = 0;
            int workingSecond = 0;

            bool works = true;
            int nonzeroRow;
            rep(firstSign, 2)
            {
                rep(secondSign, 2)
                {
                    works = true;

                    nonzeroRow = -1;

                    rep(i, n)
                    {
                        if (i == zeroRow) continue;

                        set<int> a = { grid[i][firstCol] + grid[zeroRow][firstCol] * signs[firstSign],-grid[i][firstCol] + grid[zeroRow][firstCol] * signs[firstSign] };
                        set<int> b = { grid[i][secondCol] + grid[zeroRow][secondCol] * signs[secondSign],-grid[i][secondCol] + grid[zeroRow][secondCol] * signs[secondSign] };

                        vi c;
                        set_intersection(all(a), all(b), back_inserter(c));

                        if (c.empty())
                        {
                            works = false;
                            break;
                        }

                        if (c.size() > 1)
                        {
                            deb;
                        }

                        if (first(c) != 0) nonzeroRow = i;

                        rowsums[i] = first(c);
                    }


                    if (works)
                    {
                        debif(nonzeroRow == -1);

                        rep(i, m)
                        {
                            bool works = false;
                            rep(row, n)
                            {
                                if (row == zeroRow || (rowsums[row] == rowsums[zeroRow] && grid[row][i] == grid[zeroRow][i])) continue;

                                set<int> a = { grid[zeroRow][i],-grid[zeroRow][i] };
                                set<int> b = { -(grid[row][i] - rowsums[row]),-(-grid[row][i] - rowsums[row]) };

                                vi c;
                                set_intersection(all(a), all(b), back_inserter(c));

                                if (c.empty())
                                {
                                    continue;
                                }

                                if (c.size() > 1)
                                {
                                    deb;
                                }

                                works = true;
                                colsums[i] = first(c);
                                break;
                            }

                            if (!works)
                            {
                                deb;
                            }
                        }


                        int x = 0;

                        if (n == m)
                        {
                            x = 0;
                            //deb;
                        }
                        else
                        {
                            x = (accumulate(all(colsums), 0) - accumulate(all(rowsums), 0)) / (n - m);
                            debif(((accumulate(all(colsums), 0) - accumulate(all(rowsums), 0)) % (n - m)) != 0);
                        }

                        rep(i, n) rowsums[i] += x;
                        rep(i, m) colsums[i] += x;

                        if (accumulate(all(rowsums), 0) != accumulate(all(colsums), 0))
                        {
                            works = false;
                        }

                    }

                    if (works)
                    {
                        goto done;
                    }
                }
            }

        done:;

            // it should work
            solvesums(n, m, rowsums, colsums, grid);
        }
    }

    quit;
}