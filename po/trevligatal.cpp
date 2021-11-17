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

int ans(vector<vector<vector<int>>>& memo, string& numbers, int index, int s, bool allOff)
{
    int& v = memo[index][s % 3][allOff];
    if (v != -1)
    {
        return v;
    }
    if (index == numbers.size())
    {
        return s % 3 == 0;
    }

    int ret = 0;

    if (!(allOff && numbers[index] == '0'))
    {
        ret = (ret + ans(memo, numbers, index + 1, s, false)) % int(1e9);
    }
    ret = (ret + ans(memo, numbers, index + 1, s - (numbers[index] - '0'), allOff)) % int(1e9);


    v = ret;
    return ret % int(1e9);
}


int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    string s;
    read(s);

    int a = 0;
    rep(i, s.size())
    {
        a += s[i] - '0';
    }

    vector<vector<vector<int>>> memo(s.size()+1, vector<vector<int>>(3,vector<int>(2,-1)));
    write((ans(memo, s, 0, a, true) - 1 + count(all(s),'0'))%int(1e9));

    return 0;
}