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
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

vector<ll> simulateOne(vector<ll>& moles)
{
    vector<ll> newGen(moles.size() + 2);

    for (ll i = 0; i < moles.size(); i++)
    {
        ll a = (i > 0) ? moles[i - 1] : 0;
        ll b = moles[i];
        ll c = (i < moles.size() - 1) ? moles[i + 1] : 0;

        newGen[i + 1] = a ^ b ^ c;
    }
    newGen[0] = moles[0];
    newGen[newGen.size() - 1] = moles[moles.size() - 1];
    return newGen;
}

ll count(vector<ll>& state)
{
    ll ret = 0;

    repe(i, state) ret += i;

    return ret;
}

void chomp(vector<ll>& state)
{
    if (state.size() == 0)
    {
        return;
    }
    ll firstNonZero = 0;
    ll firstNonZeroRight = 0;
    rep(i, state.size())
    {
        if (state[i] != 0)
        {
            firstNonZero = i;
            break;
        }
    }
    per(i, state.size() - 1)
    {
        if (state[i] != 0)
        {
            firstNonZeroRight = i;
            break;
        }
    }

    state = vector<ll>(state.begin() + firstNonZero, state.begin() + firstNonZeroRight + 1);
}

ll solve(map<ll, ll>& memo, vector<ll> state, ll t)
{
    chomp(state);
    if (state.size() == 0)
    {
        return 0;
    }
    if (t == 0)
    {
        return count(state);
    }

    ll origSize = state.size();
    if (state.size() == 1 && setcontains(memo, t))
    {
        return memo[t];
    }

    ll ret = 0;

    if (t % 2 == 0)
    {
        std::size_t half_size = state.size() / 2;

        vector<ll> odd(half_size);
        vector<ll> even((state.size() + 1) / 2);
        rep(i, even.size()) even[i] = state[i * 2];
        rep(i, odd.size()) odd[i] = state[i * 2 + 1];

        ret += solve(memo, odd, t / 2) + solve(memo, even, t / 2);
    }
    else
    {
        state = simulateOne(state);
        ret += solve(memo, state, t - 1);
    }

    if (origSize == 1)
    {
        memo[t] = ret;
    }

    return ret;
}

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread(string, state);
    dread(ll, t);
    vector<ll> moles(state.size());
    ll start = moles.size() / 2;
    rep(i, state.size())
    {
        moles[i] = (state[i] == 'A');
    }

    map<ll, ll> memo;
    write(solve(memo, moles, t));

    cout << endl;
    _Exit(0);
}