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
#define dread3(type, a, b, c) dread(type, a); dread(type, b); dread(type, c)
#define write(a) cout << (a) << endl
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define readpush(type,vect) type temp; read(temp); vect.push_back(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,n) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))


inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

map<int, pair<double, double>> winningProb(vector<pair<int,double>>& strengths)
{
    if (strengths.size() == 1)
    {
        return { {strengths[0].first, {1, strengths[0].second}}};
    }

    std::size_t const half_size = strengths.size() / 2;
    vector<pair<int, double>> split_lo(strengths.begin(), strengths.begin() + half_size);
    vector<pair<int, double>> split_hi(strengths.begin() + half_size, strengths.end());

    map<int, pair<double, double>> bottom = winningProb(split_lo);
    map<int, pair<double, double>> top = winningProb(split_hi);

    map<int, pair<double, double>> ret;
    repe(i, bottom)
    {
        repe(j, top)
        {
            if (!setcontains(ret, i.first))
            {
                ret[i.first] = { 0, i.second.second };
            }
            if (!setcontains(ret, j.first))
            {
                ret[j.first] = { 0, j.second.second };
            }
            ret[i.first].first += 1 / (1 + exp(j.second.second - i.second.second)) * i.second.first*j.second.first;
            ret[j.first].first += 1 / (1 + exp(i.second.second - j.second.second)) * j.second.first*i.second.first;
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

    dread(int, n);
    vector<pair<int, double>> strengths(pow(2,n));
    rep(i, pow(2, n))
    {
        dread(double, strength);
        strengths[i] = { i,strength };
    }

    map<int, pair<double, double>> winner = winningProb(strengths);

    int bestPlayer = -1;
    double bestProb = -1;
    repe(player, winner)
    {
        if (player.second.first > bestProb)
        {
            bestProb = player.second.first;
            bestPlayer = player.first + 1;
        }
    }

    cout << bestPlayer << " " << fixed << setprecision(20) << bestProb << endl;

    //return 0;
    _Exit(0);
}