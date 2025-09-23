using namespace std;
#include <bits/stdc++.h>
// #pragma GCC target("aes")
// #include <wmmintrin.h>
// #include <smmintrin.h>

using ll = long long;
using ull = uint64_t;

using vi = vector<ll>;
using vvi = vector<vi>;

#define rep(i,b) for (int i = 0; i < (b); i++)
#define repp(i,a,b) for (int i = (a); i < (b); i++)
#define all(x) begin(x),end(x)
#define sz(x) ((int)x.size())

// ull hsh(ll x) {
//     auto inp = _mm_set1_epi64((ull)x);
//     auto key = _mm_set1_epi64(8273647);
//     auto out = _mm_aescdec_si128(inp,key);
//     return _mm_extract_epi64(out, 0);
// }
// template<class T>
// struct HashMap {
//     int ;
//     vector<pair<ull, T>> v;
//     HashMap(int b) : b(b), v(1<<b,make_pair(0,-1)) {}
//     T& operator[](ull x) {
//         x=hsh(x);
//         ull y = x >> (64-b), m=(1<<b)-1;
//         while (v[y].first && v[y].first != x) ++y &= m;
//         v[y].first = x;
//         return v[y].second;
//     }
// }

int signpreserve=0;
vvi mult(2);
vector<vector<pair<int,char>>> add(2);
unordered_map<ull, char> memo;
unordered_map<ull, char> choice;

vi addodd;
vi multeven;
vector<pair<int,char>> signpres;

const bool FIRST = 0;
const bool SECOND = 1;
// is this winning state?
bool dp(bool player, bool even, int n_add_odd, int n_mul_even, int signpreserves)
{
    if (n_add_odd == 0 && n_mul_even == 0 && signpreserves == 0)
    {
        if (player==FIRST) return !even;
        return even;
    }
    ull ind = player;
    ind += 2*even;
    ind += ull(301)*2*n_add_odd;
    ind += ull(301)*301*2*n_mul_even;
    ind += ull(301)*301*301*2*signpreserves;
    if (memo.count(ind)) return memo[ind];
    char& v = memo[ind];

    bool losing = true;

    if (n_add_odd)
    {
        if (!dp(!player, !even, n_add_odd-1, n_mul_even, signpreserves)) losing=false, choice[ind]=0;
    }
    if (n_mul_even)
    {
        if (!dp(!player, 1, n_add_odd, n_mul_even-1,signpreserves)) losing=false, choice[ind]=1;
    }
    if (signpreserves)
    {
        if (!dp(!player, even, n_add_odd, n_mul_even, signpreserves-1)) losing=false, choice[ind]=2;
    }
    // cout << "player= " << player
    //  << ", even = " << even
    //  << ", n_add_odd = " << n_add_odd
    //  << ", n_mul_even = " << n_mul_even
    //  << ", signpreserves = " << signpreserves
    //  << ", losing = " << losing;
    // if (choice.count(ind)) cout << ", choice = "<< int(choice[ind]);
    // cout << '\n';



    return v = (!losing);
}


int main() {
    int n;
    cin >> n;

    rep(i,n)
    {
        char t;
        int num;
        cin >> t >> num;

        if(t=='+')
        {
            if (num%2) addodd.push_back(num);
            else signpres.emplace_back(num, '+');
        }
        else
        {
            if (num%2==0) multeven.push_back(num);
            else signpres.emplace_back(num, '*');
            
        }
    }
    int num;
    cin >> num;

    bool res = dp(FIRST, !(num%2), sz(addodd), sz(multeven), sz(signpres));
    dp(SECOND, !(num%2), sz(addodd), sz(multeven), sz(signpres));
    cout << (res ? "me" : "you") << '\n';
    bool player = res ? FIRST : SECOND;
    bool even = num%2==0;

    auto make_move = [&]()
    {
        ull ind = player;
        ind += 2*even;
        ind += ull(301)*2*sz(addodd);
        ind += ull(301)*301*2*sz(multeven);
        ind += ull(301)*301*301*2*sz(signpres);

        cerr << "odd " << sz(addodd) << ", multeven " << sz(multeven) << ", signpres: " << sz(signpres) << '\n';
        if (!choice.count(ind))
        {
            dp(player, even, sz(addodd), sz(multeven), sz(signpres));
            dp(!player, even, sz(addodd), sz(multeven), sz(signpres));
        }
        int c = choice[ind];
        
        if (c==0)
        {
            cout << "+ " << addodd.back() << endl;
            addodd.pop_back();
            even=!even;
        }
        if (c==1)
        {
            cout << "* " << multeven.back() << endl;
            multeven.pop_back();
            even=1;
        }
        if (c==2)
        {
            auto [a,t] = signpres.back();
            signpres.pop_back();
            cout << t << " " << a << endl;
        }
    };

    if (res)
    {
        make_move();
    }

    while (sz(addodd) || sz(multeven) || sz(signpres))
    {
        char t;
        int v;
        cin >> t >> v;
        auto it = find(all(signpres), make_pair(v, t));
        if (it!=end(signpres))
        {
            signpres.erase(it);
        }
        else
        {
            if (t=='+') addodd.erase(find(all(addodd), v)), even=!even;
            else multeven.erase(find(all(multeven), v)), even=1;
        }

        if (addodd.empty() && multeven.empty() && signpres.empty()) break;
        make_move();
    }

    return 0;

}
