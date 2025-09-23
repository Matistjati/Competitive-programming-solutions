#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
using namespace std;
#include <bits/stdc++.h>

using ll = long long;
using ull = uint64_t;

using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll,ll>;

#define rep(i,b) for (int i = 0; i < (b); i++)
#define repp(i,a,b) for (int i = (a); i < (b); i++)
#define repe(i,a) for (auto& i : a)
#define all(x) begin(x),end(x)
#define sz(x) ((int)x.size())

#pragma GCC target("aes")
#include <wmmintrin.h>
#include <smmintrin.h>

typedef uint64_t ull;
ull hsh(ll x) {
  auto inp = _mm_set1_epi64x(x);
  auto key = _mm_set1_epi64x(18246162); // any key
  auto out = _mm_aesdec_si128(inp, key);
  return _mm_extract_epi64(out, 0);
}
template<class T>
struct HashMap {
    int b;
    vector<ull> v;
    vector<T> vk;
    HashMap(int b) : b(b), v(1<<b), vk(1<<b) {}
    T& operator[](ull x) {
        x=hsh(x);
        ull y = x >> (64-b), m=(1<<b)-1;
        while (v[y] && v[y] != x) ++y &= m;
        v[y] = x;
        return vk[y];
    }
};


int main() {
    int n;
    cin >> n;
    n = min(n,28);

    vector<p2> nums(n);
    repe(v, nums) cin >> v.first >> v.second;

    int mid = n/2;
    vector<p2> firsthalf;
    vector<p2> secondhalf;

    rep(i,mid) firsthalf.push_back(nums[i]);
    repp(i,mid,n) secondhalf.push_back(nums[i]);
    const int powers[19] = {1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323,4782969,14348907,43046721,129140163,387420489};

    const int base = 5000*20;
    auto h=[base](p2 x)
    {
        return (x.first+base) *  ll(1e9) + (x.second+base);
    };

    HashMap<int> m(23);
    rep(i, powers[sz(firsthalf)])
    {
        p2 p = {0,0};
        rep(j,sz(firsthalf))
        {
            if (i / powers[j] % 3 == 1) p = {p.first+firsthalf[j].first, p.second+firsthalf[j].second};
            if (i / powers[j] % 3 == 2) p = {p.first-firsthalf[j].first, p.second-firsthalf[j].second};
        }

        if (p==p2(0,0) && i)
        {
            cout << "no\n";
            vi a;
            vi b;
            rep(j,sz(firsthalf))
            {
                if (i / powers[j] % 3 == 1) a.push_back(j);
                if (i / powers[j] % 3 == 2) b.push_back(j);
            }
            cout << sz(a) << " ";
            repe(v,a) cout << v+1 << " ";
            cout << '\n';
            cout << sz(b) << " ";
            repe(v,b) cout << v+1 << " ";
            cout << '\n';
            return 0;
        }

        m[h(p)] = i+1;
    }

    rep(i, powers[sz(secondhalf)])
    {
        p2 p = {0,0};
        rep(j,sz(secondhalf))
        {
            if (i / powers[j] % 3 == 1) p = {p.first+secondhalf[j].first, p.second+secondhalf[j].second};
            if (i / powers[j] % 3 == 2) p = {p.first-secondhalf[j].first, p.second-secondhalf[j].second};
        }

        if (p==p2(0,0) && i)
        {
            cout << "no\n";
            vi a;
            vi b;
            rep(j,sz(secondhalf))
            {
                if (i / powers[j] % 3 == 1) a.push_back(j);
                if (i / powers[j] % 3 == 2) b.push_back(j);
            }
            cout << sz(a) << " ";
            repe(v,a) cout << v+1 << " ";
            cout << '\n';
            cout << sz(b) << " ";
            repe(v,b) cout << v+1 << " ";
            cout << '\n';
            return 0;
        }

        int x = m[h(p2(-p.first,-p.second))];
        if (x&&i)
        {
            x--;
            cout << "no\n";
            vi a;
            vi b;
            rep(j,sz(secondhalf))
            {
                if (i / powers[j] % 3 == 1) a.push_back(j+sz(firsthalf));
                if (i / powers[j] % 3 == 2) b.push_back(j+sz(firsthalf));
            }
            rep(j,sz(firsthalf))
            {
                if (x / powers[j] % 3 == 1) a.push_back(j);
                if (x / powers[j] % 3 == 2) b.push_back(j);
            }
            cout << sz(a) << " ";
            repe(v,a) cout << v+1 << " ";
            cout << '\n';
            cout << sz(b) << " ";
            repe(v,b) cout << v+1 << " ";
            cout << '\n';
            return 0;
        }
    }

    cout << "yes\n";

    return 0;

}
