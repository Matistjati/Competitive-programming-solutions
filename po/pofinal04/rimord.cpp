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
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif

    dread(int, n);
    dread(int, v);
    dread(string, word);

    set<char> vowels = { 'A','E','I','O','U','Y' };
    int beginning = 0;
    int prev = 0;
    map<string, set<string>> rhymes;
    rep(i, n)
    {
        if (setcontains(vowels, word[i]))
        {
            int end = -1;
            int nv = 0;
            for (int j = i; j < n; j++)
            {
                if (setcontains(vowels, word[j]))
                {
                    nv++;
                    if (nv == v)
                    {
                        end = j;
                        break;
                    }
                }
            }
            if (nv < v)
            {
                break;
            }


            string rhyme = word.substr(i, end - i + 1);
            if (!setcontains(rhymes, rhyme))
            {
                rhymes[rhyme] = {};
            }
            for (int j = 1; j < i - prev + 1; j++)
            {
                string pre = word.substr(i - j, j);
                rhymes[rhyme].insert(pre);
            }

            prev = i + 1;
        }
    }

    ll most = -inf;
    repe(group, rhymes)
    {
        most = max(most, (ll)group.second.size());
    }
    write(most + 1);


    return 0;
}