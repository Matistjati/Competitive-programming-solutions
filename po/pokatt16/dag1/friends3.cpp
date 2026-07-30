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

    ll curr = p[0];
    ll currBegin = p[0];

    repp(i, 1, p.size())
    {
        if (p[i] == curr+1)
        {
            curr = p[i];
        }
        else
        {
            intervals.insert(make_pair(curr, currBegin));
            currBegin = p[i];
            curr = p[i];
        }
    }

    intervals.insert(make_pair(p[n - 1], currBegin));

    repe(interval, intervals)
    {
        Score += evalInterval(interval);
    }
}

void removeFriend(ll pos)
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
        p2 left = make_pair(pos - 1, interval.second);
        p2 right = make_pair(interval.first, pos + 1);
        Score += evalInterval(left);
        Score += evalInterval(right);
        intervals.insert(left);
        intervals.insert(right);
    }
}

void addFriend(ll pos)
{
    // Cases:
    // Alone
    // To left -> one larger
    // To right -> one larger
    // To left and to right -> merge

    auto itRight = intervals.lower_bound(make_pair(pos, -1));
    p2 intRight = (itRight != intervals.end()) ? *itRight : make_pair(inf,inf);
    bool toLeft = pos + 1 == intRight.second;

    auto itLeft = prev(itRight);
    p2 intLeft = (itLeft != intervals.end()) ? *itLeft : make_pair(inf, inf);
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
        p2 interval = make_pair(intRight.first, intRight.second-1);
        Score += evalInterval(interval);

        intervals.erase(itRight);
        intervals.insert(interval);
    }
    else if (!toLeft && toRight)
    {
        Score -= evalInterval(intLeft);
        p2 interval = make_pair(intLeft.first+1, intLeft.second);
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

        p2 interval = make_pair(intRight.first, intLeft.second);

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
