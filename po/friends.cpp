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

set<p2> intervals;
ll Score = 0;

inline ll evalInterval(p2 interval)
{
    return pow(interval.first - interval.second + 1, 2);
}

void init(int n, int l, int P[])
{
    vi p(P, P+n);

    sort(all(p));

    int curr = p[0];
    int currBegin = p[0];

    repp(i, 1, p.size())
    {
        if (p[i] == curr+1)
        {
            curr = p[i];
        }
        else
        {
            intervals.insert(mp(curr, currBegin));
            currBegin = p[i];
            curr = p[i];
        }
    }


    intervals.insert(mp(p[n - 1], currBegin));

    repe(interval, intervals)
    {
        Score += evalInterval(interval);
    }
}

void removeFriend(int pos)
{
    auto it = intervals.lower_bound({ pos,-1 });

    p2 interval = *it;
    intervals.erase(it);


    Score -= evalInterval(interval);

    if (pos == interval.second)
    {
        interval.second++;
        if (interval.second <= interval.first)
        {
            Score += evalInterval(interval);
            intervals.insert(interval);
        }
    }
    else if (pos == interval.first)
    {
        interval.first--;
        if (interval.first >= interval.second)
        {
            Score += evalInterval(interval);
            intervals.insert(interval);
        }
    }
    else
    {
        p2 left = mp(pos - 1, interval.second);
        p2 right = mp(interval.first, pos + 1);
        Score += evalInterval(left);
        Score += evalInterval(right);
        intervals.insert(left);
        intervals.insert(right);
    }
}

void addFriend(int pos)
{
    // Cases:
    // Alone
    // To left -> one larger
    // To right -> one larger
    // To left and to right -> merge

    auto itRight = intervals.lower_bound(mp(pos, -1));
    p2 intRight = (itRight != intervals.end()) ? *itRight : mp(inf,inf);
    bool toLeft = pos + 1 == intRight.second;


    auto itLeft = prev(itRight);
    p2 intLeft = (itLeft != intervals.end()) ? *itLeft : mp(inf, inf);
    bool toRight = pos - 1 == intLeft.first;

    if (!toLeft && !toRight)
    {
        p2 interval = { pos,pos };
        Score += evalInterval(interval);
        intervals.insert(interval);
    }
    else if (toLeft && !toRight)
    {
        Score -= evalInterval(intRight);
        p2 interval = mp(intRight.first, intRight.second-1);
        Score += evalInterval(interval);

        intervals.erase(itRight);
        intervals.insert(interval);
    }
    else if (!toLeft && toRight)
    {
        Score -= evalInterval(intLeft);
        p2 interval = mp(intLeft.first+1, intLeft.second);
        Score += evalInterval(interval);

        intervals.erase(itLeft);
        intervals.insert(interval);
    }
    else if (toLeft && toRight)
    {
        Score -= evalInterval(intLeft);
        Score -= evalInterval(intRight);
        intervals.erase(itLeft);
        intervals.erase(itRight);

        p2 interval = mp(intRight.first, intLeft.second);

        Score += evalInterval(interval);
        intervals.insert(interval);
    }
    else
    {
        cout << "ligma";
    }
}

void jump(int A, int B)
{
    removeFriend(A);
    addFriend(B);
}

long long score()
{
    return Score;
}


//int main() {
//    int N, L, Q, ign;
//    ign = scanf("%d%d%d", &N, &L, &Q);
//    readvector(int, P, N);
//
//    init(N, L, P.data());
//    for (int i = 0; i < Q; ++i) {
//        int type;
//        ign = scanf("%d", &type);
//        if (type == 0) {
//            int A, B;
//            ign = scanf("%d%d", &A, &B);
//            jump(A, B);
//        }
//        else if (type == 1) printf("%lld\n", score());
//        else assert(false && "Invalid query type");
//    }
//    ign = ign;
//}



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
