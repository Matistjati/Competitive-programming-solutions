#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define ip3 tuple<int,int,int>
#define ip4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define write(a) cout << (a) << "\n"
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

inline ll hashS(string& s)
{
    ll h = 0;
    rep(i, s.size())
    {
        h += (s[i] - 'A') * (ll)pow(3, i);
    }

    return h;
}

tuple<string, int,int> simulate(string& buffer, int bufferOffset, string current)
{
    bool changed;
    int score = 0;
    do
    {
        changed = false;
        char prev = current[0];
        vector<pair<int, int>> safe;


        int beginning = 0;
        for (int i = 1; i < current.size(); i++)
        {
            if (current[i] != prev)
            {
                if (i - beginning < 3)
                {
                    safe.push_back({ beginning, i });
                }
                else
                {
                    score += (i - beginning) * 2 - 5;
                }
                beginning = i;
                prev = current[i];
            }
        }
        if (current.size()-beginning < 3)
        {
            safe.push_back({ beginning,current.size() });
        }
        else
        {
            score += (current.size() - beginning) * 2 - 5;
        }

        string nextState;

        repe(interval, safe)
        {
            for (int i = interval.first; i < interval.second; i++)
            {
                nextState += current[i];
            }
        }

        while (nextState.size() < buffer.size())
        {
            nextState += buffer[bufferOffset];
            bufferOffset++;
            bufferOffset = bufferOffset % buffer.size();
        }

        if (current != nextState)
        {
            changed = true;
        }
        current = nextState;

    } while (changed);

    return { current, score, bufferOffset };
}

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread(int, n);
    dread(string, start);

    queue<tuple<string, int,int,int>> toDo;
    toDo.push({ start, 0, 0, 0 });

    int bestScore = -inf;
    while (toDo.size())
    {
        string curr;
        int score;
        int offset;
        int depth;
        tie(curr, score, offset, depth) = toDo.front();
        toDo.pop();


        if (depth >= n)
        {
            break;
        }



        rep(i, curr.size()-1)
        {
            char ch = curr[i];
            string c = curr;

            swap(c[i], c[i + 1]);
            tuple<string, int, int> n = simulate(start, offset, c);

            if (get<1>(n) == 0)
            {
                continue;
            }

            bestScore = max(bestScore, get<1>(n) + score);



            toDo.push({ get<0>(n), get<1>(n) + score, get<2>(n), depth + 1});
        }
    }

    write(bestScore);

    cout << endl;
    _Exit(0);
}