#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int distance(int x, int y)
{
    x = abs(x);
    y = abs(y);
    if (x < y) swap(x, y);
    if (x == 1 && y == 0) return 3;
    if (x == 2 && y == 2) return 4;

    int delta = x - y;
    // floor needed to round towards -inf
    if (y > delta) return delta - 2 * floor((delta - y) / 3.0);
    else return delta - 2 * floor((delta - y) / 4.0);
}

signed main()
{
    fast();

    auto bishop_possible = [](p2 pos)
    {
        return (pos.first + pos.second) % 2 == 0;
    };

    int q;
    cin >> q;
    while (q--)
    {
        string pieces;
        cin >> pieces;
        bool queen = find(all(pieces), 'Q') != pieces.end();
        bool rook = find(all(pieces), 'R') != pieces.end();
        bool bishop = find(all(pieces), 'B') != pieces.end();
        bool knight = find(all(pieces), 'N') != pieces.end();
        bool king = find(all(pieces), 'K') != pieces.end();
        bool pawn = find(all(pieces), 'P') != pieces.end();
        p2 start;
        p2 goal;
        cin >> start.first >> start.second >> goal.first >> goal.second;
        goal.first -= start.first;
        goal.second -= start.second;

        int upper_bound = inf;
        if (rook)
        {
            upper_bound = min(upper_bound, 2LL);
            if (goal.first == 0 || goal.second == 0) upper_bound = 1;

        }
        if (queen)
        {
            upper_bound = min(upper_bound, 2LL);
            if (goal.first == 0 || goal.second == 0) upper_bound = 1;
            if (abs(goal.first) == abs(goal.second)) upper_bound = 1;
        }
        vector<p2> moves;
        if (knight)
        {
            upper_bound = min(upper_bound, distance(goal.first, goal.second));
            moves.emplace_back(2, 1);
            moves.emplace_back(-2, 1);
            moves.emplace_back(2, -1);
            moves.emplace_back(-2, -1);
            moves.emplace_back(1, 2);
            moves.emplace_back(-1, 2);
            moves.emplace_back(1, -2);
            moves.emplace_back(-1, -2);
        }
        if (king)
        {
            upper_bound = min(upper_bound, max(abs(goal.first), abs(goal.second)));
            moves.emplace_back(1, 1);
            moves.emplace_back(-1, 1);
            moves.emplace_back(1, -1);
            moves.emplace_back(-1, -1);
            moves.emplace_back(0, 1);
            moves.emplace_back(1, 0);
            moves.emplace_back(0, -1);
            moves.emplace_back(-1, 0);
        }
        if (pawn)
        {
            if (goal.second == 0 && goal.first >= 0) upper_bound = min(upper_bound, goal.first);
            moves.emplace_back(1, 0);
        }
        if (bishop)
        {
            if (bishop_possible(goal)) upper_bound = min(upper_bound, 2LL);
            if (abs(goal.first) == abs(goal.second)) upper_bound = 1;
            repp(d, 1, 5)
            {
                moves.emplace_back(d, d);
                moves.emplace_back(-d, d);
                moves.emplace_back(d, -d);
                moves.emplace_back(-d, -d);
            }
            
        }

        queue<pair<int, p2>> q;
        q.emplace(0, p2(0, 0));
        set<p2> seen;
        while (sz(q)&&q.front().first<=min(6LL, upper_bound))
        {
            int d;
            p2 p;
            tie(d, p) = q.front();
            q.pop();

            p2 dg = p2(goal.first - p.first, goal.second - p.second);
            if (bishop)
            {
                if (bishop_possible(dg)) upper_bound = min(upper_bound, d + 2);
                if (abs(dg.first) == abs(dg.second)) upper_bound = min(upper_bound, d + 1);
            }
            if (knight)
            {
                upper_bound = min(upper_bound, d + distance(dg.first,dg.second));
            }
            

            if (seen.find(p) != seen.end()) continue;
            seen.insert(p);

            repe(m, moves)
            {
                p2 np = p2(p.first + m.first, p.second + m.second);
                q.emplace(d + 1, np);
            }
        }

        if (upper_bound != inf) cout << upper_bound << "\n";
        else cout << "-1\n";
    }

    return 0;
}
