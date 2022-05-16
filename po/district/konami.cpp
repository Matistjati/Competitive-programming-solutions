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
#define dread2(type, a, b) dread(type, a); dread(type, b)
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

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread(string, konami);

    int konamiLength = 10;
    map<int, pair<int, int>> codes;

    vector<tuple<int, int, int>> waitingU;
    vector<tuple<int, int, int>> waitingN;
    vector<tuple<int, int, int>> waitingV;
    vector<tuple<int, int, int>> waitingH;
    vector<tuple<int, int, int>> waitingB;
    vector<tuple<int, int, int>> waitingA;

    map<char, vector<tuple<int, int, int>>*> cToSet = { {'U',&waitingU},{'N',&waitingN},{'V',&waitingV},{'H',&waitingH},{'B',&waitingB},{'A',&waitingA} };

    vector<char> konamiCode = { 'U','U','N','N','V','H','V','H','B','A' };

    rep(i, konami.size())
    {
        char c = konami[i];


        vector<tuple<int, int, int>> waiting = *cToSet[c];
        (*cToSet[c]) = vector<tuple<int, int, int>>();
        repe(wait, waiting)
        {
            int id, index, codeP;
            tie(id, index, codeP) = wait;

            if (codeP == 1)
            {
                codes[id] = {0 , 0 };
            }
            codes[id].first += (i - index-1);
            codes[id].second++;

            codeP++;
            if (codeP == konamiCode.size())
            {
                continue;
            }
            char nextChar = konamiCode[codeP];
            cToSet[nextChar]->push_back({id, i, codeP});
        }

        if (c == 'U')
        {
            waitingU.push_back({ i, i, 1 });
        }
    }

    int best = inf;
    repe(c, codes)
    {
        if (c.second.second == 9)
        {
            best = min(best, c.second.first);
        }
    }

    write(best);

    return 0;
}