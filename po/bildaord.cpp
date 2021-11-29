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
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define write(a) cout << (a) << endl
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

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

template <typename Out>
void split(const std::string& s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

set<string> bois;

inline int indexC(char c)
{
    return (1 << (c - 'A'));
}

int ans(set<char>& chars, map<int, set<char>>& pos, map<char, set<char>>& prev, int posrec, int n, int index, char prevC, int seen)
{
    if (__builtin_popcount(seen) == n)
    //if (_Popcount((unsigned int)seen) == n)
    {
        if (setcontains(prev, prevC))
        {
            return 0;
        }
        return 1;
    }

    int ret = 0;

    if (!setcontains(prev, prevC))
    {
        repe(c, chars)
        {
            int p = indexC(c);
            if (!(seen & p))
            {
                seen |= p;
                ret += ans(chars, pos, prev, posrec, n, index + 1, c, seen);
                seen &= ~p;
            }

        }

        repe(c, pos[index])
        {
            int p = indexC(c);
            if (!(seen & p))
            {
                seen |= p;
                ret += ans(chars, pos, prev, posrec, n, index + 1, c, seen);
                seen &= ~p;
            }
        }
    }
    else
    {
        repe(c, prev[prevC])
        {

            if (!setcontains(pos[index], c) && (posrec & indexC(c)))
            {
                continue;
            }
            int p = indexC(c);
            if (!(seen & p))
            {
                seen |= p;
                ret += ans(chars, pos, prev, posrec, n, index + 1, c, seen);
                seen &= ~p;
            }
        }
    }


    return ret;
}

int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread2(int, charN, n);

    set<char> chars;
    rep(i, charN)
    {
        chars.insert(i + 'A');
    }

    map<int, set<char>> pos;
    map<char, set<char>> prev;

    int posrec = 0;

    rep(i, n)
    {
        dread(string, rule);
        char c = rule[0];


        if (stringcontains(rule, '@'))
        {
            posrec |= indexC(c);
            chars.erase(c);
            vector<string> positions = split(rule.substr(2), ',');
            repe(pStr, positions)
            {
                int p = stoi(pStr) - 1;
                if (!setcontains(pos, p))
                {
                    pos[p] = {};
                }
                pos[p].insert(c);
            }
        }
        else
        {
            for (int i = 2; i < rule.size(); i++)
            {
                char curr = rule[i];
                if (!setcontains(prev, c))
                {
                    prev[c] = {};
                }
                prev[c].insert(curr);
            }
        }
    }

    write(ans(chars, pos, prev, posrec, charN, 0, '+', 0));

    //return 0;
    _Exit(0);
}