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
#define vp3 vector<p3>
#define vp4 vector<p4>
#if enablell
#define inf 1e18
#else
#define inf int(2e9)
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
#define assert(expr) if (!(expr)) deb;

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


// Pretty unclean ngl, but sometimes CP be like that
void trick(int n);


inline int evaluate(int& l, int& r, int v)
{
    if ((v<l || v>r))
    {
        return 0;
    }

    return abs(v - (l + r) / 2);
}

int32_t magic_score(int n, int k, int l[], int r[])
{
    int freePoints = 0;
    int availableOnes = 0;

    vp2 dpRounds;
    vi roundSigns;
    vb roundMap(n);



    rep(i, n)
    {
        p2 p = { l[i],r[i] };

        if (p.first >= 0 && p.second >= 0)
        {
            dpRounds.emplace_back(p);
            roundSigns.emplace_back(1);
            roundMap[i] = true;
        }
        else if (p.first <= 0 && p.second <= 0)
        {
            dpRounds.emplace_back(mp(-p.second, -p.first));
            roundSigns.emplace_back(-1);
            roundMap[i] = true;
        }
        else
        {
            if (!(p.first <= 0 && p.second >= 0)) deb;

            freePoints += evaluate(p.first, p.second, 0);
            int avg = (p.first + p.second) / 2;
            if (avg < 0)
            {
                availableOnes += p.second;
            }
            else
            {
                availableOnes -= p.first;
            }
            roundMap[i] = false;
        }

    }

    int dpN = dpRounds.size() + 1;
    vvi dp(dpN, vi(k + 1, 0));

    repp(i, 1, dpN)
    {
        vi& prev = dp[i - 1];//{1,2,3,3,3,4};


        p2 p = dpRounds[i-1];


        rep(j, k + 1)
        {
            int& v = dp[i][j];

            int score = 0;

            if (j>=p.first)
            {
                score = evaluate(p.first, p.second, p.first) + prev[j - p.first];
            }

            v = max(prev[j], score);
        }
    }

    int bestScore = -inf;
    int bestIndex = -1;
    int n_ones = -1;

    vi& lastRow = dp[dpN - 1];

    rep(j, lastRow.size())
    {
        int score = lastRow[j] + min(k - j, availableOnes);
        if (score > bestScore)
        {
            bestScore = score;
            n_ones = min(k - j, availableOnes);
            bestIndex = j;
        }

    }



    int ans = bestScore + freePoints;

    vi dpRoundChoices(dpN-1);

    int iterScore = lastRow[bestIndex];
    perr(i, 0, sz(dpRounds)-1)
    {
        if (dp[i][bestIndex] == iterScore)
        {
            dpRoundChoices[i] = 0;
        }
        else
        {
            dpRoundChoices[i] = dpRounds[i].first*roundSigns[i];

            bestIndex -= dpRounds[i].first;
            iterScore -= evaluate(dpRounds[i].first, dpRounds[i].second, dpRounds[i].first);
        }
    }

    int dpRoundIndex = 0;
    int greedyRoundIndex = 0;

    //int secondScore = 0;
    rep(i,n)
    {
        // dp round
        if (roundMap[i])
        {
            trick(dpRoundChoices[dpRoundIndex]);
            //secondScore += evaluate(dpRounds[dpRoundIndex].first, dpRounds[dpRoundIndex].second, dpRoundChoices[dpRoundIndex] * roundSigns[dpRoundIndex]);
            dpRoundIndex++;
        }
        else
        {
            p2 p = { l[i],r[i] };
            //secondScore += evaluate(p.first, p.second, 0);
            if (n_ones > 0)
            {
                int avg = (p.first + p.second) / 2;
                if (avg < 0)
                {
                    int magic = min(p.second, n_ones);
                    trick(magic);
                    n_ones -= magic;
                    //secondScore += magic;
                }
                else
                {
                    int magic = -min(-p.first, n_ones);
                    trick(magic);
                    n_ones += magic;
                    //secondScore -= magic;
                }
            }
            else
            {
                trick(0);
            }

        }
    }

    //assert(ans == secondScore);

    return ans;
}

//
//static std::vector<int> output;
//void trick(int n) {
//  output.emplace_back(n);
//}
//
//int32_t main() {
//  dread2(int, N, K);
//  std::vector<int> L(N), R(N);
//  for (int i = 0; i < N; i++)
//      ignore = scanf("%d", &L[i]);
//  for (int i = 0; i < N; i++)
//      ignore = scanf("%d", &R[i]);
//  output.reserve(N);
//  int sol = magic_score(N, K, L.data(), R.data());
//  if ((int)output.size() != N) {
//      printf("error: tried to perform %d tricks, should perform %d", (int)output.size(), N);
//  }
//  else {
//      printf("%d\n", sol);
//      for (int i = 0; i < N; i++) {
//          if (i != 0) putchar(' ');
//          printf("%d", output[i]);
//      }
//      puts("");
//  }
//}


//
//int32_t main()
//{
//    fast();
//
//#if 0
//    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Release\\in.txt");
//#endif
//
//
//
//    quit;
//}
