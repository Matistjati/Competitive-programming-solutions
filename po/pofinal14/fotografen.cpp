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


int main()
{
    fast();

#if 0
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\Downloads\\pixel\\examples\\sample01.in");
#endif


    vector<int> dist = { 3,2,1,0 };
    map<char, int> charToDist = { {'H',3},{'N',2},{'V',1},{'U',0}};
    map<char, char> nextRot = { {'H','N'},{'N','V'},{'V','U'},{'U','H'}};
    map<char, vector<char>> nextN;
    repe(c, nextRot)
    {
        nextN[c.first] = vector<char>(4);
        char curr = c.first;
        rep(i, 4)
        {
            nextN[c.first][i] = curr;
            curr = nextRot[curr];
        }
    }



    dread2(int, n, k);
    dread(string, photos);
    int ans = 0;

    int extraRotations = 0;
    vector<int> rotationLoss(n);
    for (int i = n-1; i >= 0; i--)
    {
        extraRotations -= rotationLoss[i];
        int n_rotations = charToDist[nextN[photos[i]][extraRotations%4]];

        if (i<k-1 && n_rotations!=0)
        {
            cout << -1 << endl;
            _Exit(0);
        }

        extraRotations += n_rotations;
        if (i - k >= 0)
        {
            rotationLoss[i - k] = n_rotations;
        }
        ans += n_rotations;
    }

    write(ans);

    //return 0;
    _Exit(0);
}