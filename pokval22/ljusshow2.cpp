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


inline int evaluateSquare(vector<vector<bool>>& query, vector<int>& top, vector<int>& left)
{
    int s = 0;
    rep(i, query.size())
    {
        rep(j, query[0].size())
        {
            if (query[i][j])
            {
                s += (top[i] | left[j]) == 0b111;
            }
            else
            {
                s += (top[i] | left[j]) != 0b111;
            }
        }
    }
    return s;
}

map<int, string> permToS = { {0b001,"BB"},{0b010,"GG"},{0b100,"RR"},{0b110,"RG"},{0b101,"RB"},{0b011,"GB"} };

//RGB
//RR
//GG
//BB
//RG
//GB
//RB
//                                  BB      GG   RR     RG    RB   GB
const vector<int> permutations = { 0b001,0b010,0b100,0b110,0b101,0b011 };

inline pair<int, int> bestrow(vector<bool>& row, vector<int>& top)
{



    int mostperm = -inf;
    int bestPerm = -1;
    repe(perm, permutations)
    {
        int s = 0;
        rep(i, row.size())
        {
            if (row[i])
            {
                s += (top[i] | perm) == 0b111;
            }
            else
            {
                s += (top[i] | perm) != 0b111;
            }
        }
        if (s > mostperm)
        {
            mostperm = s;
            bestPerm = perm;
        }
    }

    return { mostperm,bestPerm };
}

vector<int> bestleft;
vector<int> besttop;
int bestV = -inf;
auto Start = std::chrono::high_resolution_clock::now();

bool recur(vector<vector<bool>>& query, vector<int>& top, vector<int>& order, int d)
{
    if (d > 2)
    {
        auto End = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> Elapsed = End - Start;
        if (Elapsed.count() >= 10500)
        {
            return false;
        }
    }
    if (top.size() == query[0].size())
    {
        auto End = std::chrono::high_resolution_clock::now();

        vector<int> left(query.size());
        int s = 0;
        rep(i, query.size())
        {
            pair<int, int> p = bestrow(query[i], top);
            s += p.first;
            left[i] = p.second;
        }
        if (s > bestV)
        {
            bestV = s;
            bestleft = left;
            besttop = vector<int>(top);
        }
        return true;
    }

    repe(perm, order)
    {
        top.push_back(perm);
        bool b = recur(query, top, order, d - 1);
        top.pop_back();
        if (!b)
        {
            return false;
        }
    }
    return true;
}


void solvesmall(vector<vector<bool>>& query, int t)
{
    vector<int> s = { 0b001 };
    vector<int> permcopy(permutations);
    if (t == 8)
    {
        repe(perm, permutations)
        {
            s[0] = perm;
            recur(query, s, permcopy, query[0].size());
        }
    }
    else if (t == 1)
    {
        vector<int> perms = { 0b110,0b101,0b011,0b001,0b010,0b100 };
        repe(perm, perms)
        {
            s[0] = perm;
            recur(query, s, permcopy, query[0].size());
        }
    }
    else if (t == 6)
    {
        //9.3vector<int> perms = { 0b011,0b110,0b101,0b001,0b010,0b100 };
        vector<int> perms = { 0b101,0b001,0b011,0b110,0b010,0b100 };
        repe(perm, perms)
        {
            s[0] = perm;
            recur(query, s, perms, query[0].size());
        }
    }
    else
    {
        repe(perm, permutations)
        {
            s[0] = perm;
            recur(query, s, permcopy, query[0].size());
        }
    }

}

void solvelarge(vector<vector<bool>>& query)
{
    int i = 0;
    vector<int> top(query[0].size());
    mt19937 rng(0);
    uniform_int_distribution<int> dist(0, 5);
    vector<int> left(query.size());
    while (true)
    {
        rep(i, query[0].size())
        {
            top[i] = permutations[dist(rng)];
        }


        int s = 0;
        rep(i, query.size())
        {
            vector<bool>& row = query[i];
            int mostperm = -inf;
            int bestPerm = -1;
            repe(perm, permutations)
            {
                int s = 0;
                rep(i, row.size())
                {
                    if (row[i])
                    {
                        s += (top[i] | perm) == 0b111;
                    }
                    else
                    {
                        s += (top[i] | perm) != 0b111;
                    }
                }
                if (s > mostperm)
                {
                    mostperm = s;
                    bestPerm = perm;
                }
            }
            s += mostperm;
            left[i] = bestPerm;
        }
        if (s > bestV)
        {
            bestV = s;
            bestleft = left;
            besttop = vector<int>(top);
        }

        if (i % 1000 == 0)
        {
            auto End = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> Elapsed = End - Start;
            if (Elapsed.count() >= 10500)
            {
                return;
            }
        }
    }

}

vector<int> bestlefttrue;
vector<int> besttoptrue;
int bestVtrue = -inf;

bool solvelargeexperimental(vector<vector<bool>>& query, int t, ll seed)
{
    int i = 0;
    int n = query.size();
    int m = query[0].size();
    map<int, int> weights = { {2,5},{3,5},{4,5},{5,5},{6,3}, {9,5},{10,5} };
    int w = weights[t];

    vector<int> top(n);


    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, 5);
    rep(i, n)
    {
        top[i] = permutations[dist(rng)];
    }

    vector<int> smalltop(weights[t]);

    vector<int> order(permutations);

    vector<vector<bool>> columns(m, vector<bool>(n));
    rep(i, n)
    {
        rep(j, m)
        {
            columns[j][i] = query[i][j];
        }
    }

    int prev = 0;
    rep(i, query[0].size() / w)
    {
        /* rep(j, w)
         {
             int k = j + i * 4;
             if (k >= query[0].size())
             {
                 return false;
             }
             smalltop[j] = query[0][k];
         }*/

        recur(query, top, order, w);

        vector<int> left = bestleft;

        int s = 0;
        rep(i, m)
        {
            vector<bool>& row = columns[i];
            int mostperm = -inf;
            int bestPerm = -1;
            repe(perm, permutations)
            {
                int s = 0;
                rep(i, row.size())
                {
                    if (row[i])
                    {
                        s += (left[i] | perm) == 0b111;
                    }
                    else
                    {
                        s += (left[i] | perm) != 0b111;
                    }
                }
                if (s > mostperm)
                {
                    mostperm = s;
                    bestPerm = perm;
                }
            }
            s += mostperm;
            top[i] = bestPerm;
        }
        if (s > bestVtrue)
        {
            bestVtrue = s;
            bestlefttrue = left;
            besttoptrue = vector<int>(top);
        }
        if (i % 1000 == 0)
        {
            auto End = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> Elapsed = End - Start;
            if (Elapsed.count() >= 10500)
            {
                return false;
            }
        }
        if (s - prev == 0)
        {
            break;
        }
        else
        {
            prev = s;
        }
    }
    return true;
}

bool solvelargeexperimentalcolfirst(vector<vector<bool>>& query, int t, ll seed)
{
    int i = 0;
    int n = query.size();
    int m = query[0].size();
    map<int, int> weights = { {2,5},{3,5},{4,5},{5,5},{6,3}, {9,5},{10,5} };
    int w = weights[t];

    vector<int> top(n);


    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0, 5);
    rep(i, n)
    {
        top[i] = permutations[dist(rng)];
    }

    vector<int> smalltop(weights[t]);

    vector<int> order(permutations);

    vector<vector<bool>> columns(m, vector<bool>(n));
    rep(i, n)
    {
        rep(j, m)
        {
            columns[j][i] = query[i][j];
        }
    }

    int prev = 0;
    rep(i, query[0].size() / w)
    {
        /* rep(j, w)
         {
             int k = j + i * 4;
             if (k >= query[0].size())
             {
                 return false;
             }
             smalltop[j] = query[0][k];
         }*/


        vector<int> left(query.size());
        rep(i, query.size())
        {
            pair<int, int> p = bestrow(query[i], top);
            left[i] = p.second;
        }



        int s = 0;
        rep(i, m)
        {
            vector<bool>& row = columns[i];
            int mostperm = -inf;
            int bestPerm = -1;
            repe(perm, permutations)
            {
                int s = 0;
                rep(i, row.size())
                {
                    if (row[i])
                    {
                        s += (left[i] | perm) == 0b111;
                    }
                    else
                    {
                        s += (left[i] | perm) != 0b111;
                    }
                }
                if (s > mostperm)
                {
                    mostperm = s;
                    bestPerm = perm;
                }
            }
            s += mostperm;
            top[i] = bestPerm;
        }
        if (s > bestVtrue)
        {
            bestVtrue = s;
            bestlefttrue = left;
            besttoptrue = vector<int>(top);
        }
        if (i % 1000 == 0)
        {
            auto End = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> Elapsed = End - Start;
            if (Elapsed.count() >= 10500)
            {
                return false;
            }
        }
        if (s - prev == 0)
        {
            break;
        }
        else
        {
            prev = s;
        }
    }
    return true;
}


void solvelargeexperimental2(vector<vector<bool>>& query, int t)
{
    int i = 0;
    int n = query.size();
    int m = query[0].size();
    map<int, int> weights = { {2,8}, {3,8},{4,9},{5,12}, {6,4},{9,7}, {10,7} };
    map<int, int> offsets = { {2,0},{3,0},{4,0},{5,0}, {6,0},{9,28}, {10,28} };
    map<int, int> timelimit = { {2,10500}, {3,10500},{4,10500},{5,10500}, {6,10500}, {9,10000}, {10,10500} };
    map<int, int> modcheck = { {2,1000},{3,1000},{4,1000},{5,1}, {6,1}, {9, 2}, {10, 2} };
    int w = weights[t];

    vector<int> top(m);

    vector<int> order(permutations);

    vector<vector<bool>> columns(m, vector<bool>(n));
    rep(i, n)
    {
        rep(j, m)
        {
            columns[j][i] = query[i][j];
        }
    }

    for (int i = offsets[t]; i < m / w; i++)
    {
        vector<vector<bool>> moddedquery(n, vector<bool>(w));
        rep(j, n)
        {
            rep(k, w)
            {
                if (k + i * w >= query[j].size())
                {
                    return;
                }
                moddedquery[j][k] = query[j][k + i * w];
            }
        }

        vector<int> q;
        recur(moddedquery, q, order, w);

        vector<int> left = bestleft;

        int s = 0;
        rep(k, m)
        {
            vector<bool>& row = columns[k];
            int mostperm = -inf;
            int bestPerm = -1;
            repe(perm, permutations)
            {
                int s = 0;
                rep(i, row.size())
                {
                    if (row[i])
                    {
                        s += (left[i] | perm) == 0b111;
                    }
                    else
                    {
                        s += (left[i] | perm) != 0b111;
                    }
                }
                if (s > mostperm)
                {
                    mostperm = s;
                    bestPerm = perm;
                }
            }
            s += mostperm;
            top[k] = bestPerm;
        }
        if (s > bestVtrue)
        {
            bestVtrue = s;
            bestlefttrue = left;
            besttoptrue = vector<int>(top);
        }
        if (i % modcheck[t] == 0)
        {
            auto End = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> Elapsed = End - Start;
            if (Elapsed.count() >= timelimit[t])
            {
                return;
            }
        }
    }

}


int main()
{
    fast();

    dread(int, t);
    dread(int, n);
    dread(int, m);



    vector<vector<bool>>query;
    vector<int> rowSum;
    rep(i, n)
    {
        dread(string, s);
        vector<bool> row;
        int sum = 0;
        repe(c, s)
        {
            if (c == '1')
            {
                row.push_back(0b111);
                sum++;
            }
            else
            {
                row.push_back(0);
            }
        }
        query.push_back(row);
        rowSum.push_back(sum);
    }

    if (false && (t == 0 || t == 1 || t == 2 || t == 3 || t == 4 || t == 5 || t == 6 || t == 7 || t == 8 || t == 10))
    {
        return 0;
    }

    if (t == 0 || t == 1 || t == 8)
    {
        solvesmall(query, t);

        string top = "";
        string bot = "";
        string right = "";
        string left = "";
        repe(p, besttop)
        {
            string str = permToS[p];
            top += str[0];
            bot += str[1];
        }

        repe(p, bestleft)
        {
            string str = permToS[p];
            left += str[0];
            right += str[1];
        }

        write(top);
        write(right);
        write(bot);
        write(left);
    }
    else if (t == 7)
    {
        string top = "R";
        string bot = "R";
        string right = "";
        string left = "";

        rep(i, n)
        {
            if (query[i][m - 1])
            {
                right += "G";
                left += "B";
            }
            else
            {
                right += "R";
                left += "R";
            }
        }
        write(top);
        write(right);
        write(bot);
        write(left);
    }
    else if ((t == 10))
    {
        map<int, ll> initial = { {9,4e13},{10,1e12} };
        ll i = initial[t];
        while (solvelargeexperimental(query, t, i))
        {
            i++;
        }
        string top = "";
        string bot = "";
        string right = "";
        string left = "";
        repe(p, besttoptrue)
        {
            string str = permToS[p];
            top += str[0];
            bot += str[1];
        }

        repe(p, bestlefttrue)
        {
            string str = permToS[p];
            left += str[0];
            right += str[1];
        }

        write(top);
        write(right);
        write(bot);
        write(left);
    }
    else if ((t == 9))
    {
        map<int, ll> initial = { {9,4e13},{10,1e12} };
        ll i = initial[t];
        while (solvelargeexperimentalcolfirst(query, t, i))
        {
            i++;
        }
        string top = "";
        string bot = "";
        string right = "";
        string left = "";
        repe(p, besttoptrue)
        {
            string str = permToS[p];
            top += str[0];
            bot += str[1];
        }

        repe(p, bestlefttrue)
        {
            string str = permToS[p];
            left += str[0];
            right += str[1];
        }

        write(top);
        write(right);
        write(bot);
        write(left);
    }
    else
    {
        solvelargeexperimental2(query, t);
        string top = "";
        string bot = "";
        string right = "";
        string left = "";
        repe(p, besttoptrue)
        {
            string str = permToS[p];
            top += str[0];
            bot += str[1];
        }

        repe(p, bestlefttrue)
        {
            string str = permToS[p];
            left += str[0];
            right += str[1];
        }

        write(top);
        write(right);
        write(bot);
        write(left);
    }

    return 0;
}