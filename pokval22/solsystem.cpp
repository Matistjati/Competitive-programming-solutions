#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define dread(type, a) type a; cin >> a
#define write(a) cout << (a) << endl
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))


inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

void solveq1(vector<p3>& unions, vector<pair<int, int>>& travels)
{
    repe(travel, travels)
    {
        if (travel.first > travel.second)
        {
            swap(travel.first, travel.second);
        }
        int n = 0;

        bitset<100000> in;
        repe(un, unions)
        {
            if (un[0] <= travel.first && un[1] >= travel.first)
            {
                in.set(un[2]);
            }
        }

        bitset<100000> inSecond;
        repe(un, unions)
        {
            if (un[0] <= travel.second && un[1] >= travel.second)
            {
                inSecond.set(un[2]);
            }
        }



        n += in.count() + inSecond.count() - (in & inSecond).count() * 2;

        /*repe(b, in)
        {
            if (un.first <= travel.first && un.second >= travel.first)
            {
                in.insert(un);
            }
        }*/

        write(n);
    }
}

//void solvearb(vector<p3>& unions, vector<pair<int, int>>& travels)
//{
//
//    rep(i, 1e5+1)
//    {
//
//    }
//
//}

void solvearb(vector<p3>& unions, vector<pair<int, int>>& travels)
{
    const int maxN = 100001;
    priority_queue<tuple<double, int, int>> toCheck;
    vector<bitset<maxN>*> uns(travels.size());
    vector<int> ans(travels.size());
    repe(un, unions)
    {
        toCheck.push({ -un[0],un[1],un[2] });
    }

    rep(i, travels.size())
    {
        pair<int, int> travel = travels[i];
        if (travel.first > travel.second)
        {
            swap(travel.first, travel.second);
        }
        toCheck.push({ -travel.first - 0.5,-1,i });
        toCheck.push({ -travel.second - 0.5,-2,i });
    }

    priority_queue<p3> activeIntervals;

    bitset<maxN> currentUnions;


    while (toCheck.size())
    {
        double start;
        int end, index;
        tie(start, end, index) = toCheck.top();
        start = -start;
        toCheck.pop();
        if (floor(start) != start)
        {
            start -= 0.5;
        }

        while (end < 0 && activeIntervals.size() && start > -activeIntervals.top()[0])
        {
            p3 inter = activeIntervals.top();
            activeIntervals.pop();

            currentUnions.set(inter[2], false);
            /*okPeople[inter.second].second.erase(-inter.first);
            if (okPeople[inter.second].second.empty() && okPeople[inter.second].first)
            {
                active--;
                okPeople[inter.second].first = false;
            }*/
        }

        if (end < 0)
        {
            if (end == -1)
            {
                uns[index] = new bitset<maxN>(currentUnions);
            }
            else
            {
                ans[index] = uns[index]->count() + currentUnions.count() - (*uns[index] & currentUnions).count() * 2;
                delete uns[index];
                uns[index] = nullptr;
            }
        }
        else
        {
            activeIntervals.push({ (ll)-end,(ll)start,index });
            currentUnions.set(index);
        }

    }

    int i = 0;
    repe(answer, ans)
    {
        //cout << i << " " << answer << ", data: " << min(travels[i].first, travels[i].second) << ", " << max(travels[i].first, travels[i].second) << "\n";
        cout << answer << "\n";
    }
}


int main()
{
    fast();

    //std::ifstream in("C:\\Users\\joshua.jeffmarander\\source\\repos\\Temp\\x64\\Release\\dabbed.txt");
    //std::streambuf* cinbuf = std::cin.rdbuf(); //save old buf
    //std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    int n;
    read(n);

    vector<p3> unions;


    rep(i, n)
    {
        dread(int, a);
        dread(int, b);
        unions.push_back({ a,b,i });
    }

    int q;
    read(q);
    vector<pair<int, int>> travels;
    rep(i, q)
    {
        dread(int, a);
        dread(int, b);
        travels.push_back({ a,b });
    }

    if (true)
    {
        //solveq1(unions, travels);
        solvearb(unions, travels);
    }
    else
    {
        throw new runtime_error("");
    }

    return 0;
}