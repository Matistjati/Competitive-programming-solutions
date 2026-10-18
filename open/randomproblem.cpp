#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,popcnt")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    int n;
    cin >> n;
    vi nums(n);
    rep(i,n) cin >> nums[i];

    using bset = bitset<1000>;
    vector<bset> occs(10);
    rep(i,n) occs[nums[i]][i]=1;
    mt19937 rng(42);
    int target = (n+39)/40+1;
    bset nmask;
    rep(i,n) nmask[i]=1;
    rep(i,n) {
        int a = nums[i];
        repp(j,i+1,n-1) {
            int b = nums[j];
            int delta = j-i;
            bset starting = occs[a] & (occs[b]>>delta);
            if (starting.count() < target) continue;
            auto check = [&](int k, bool print) {
                int c = nums[k];
                bset shifted_b = ((occs[b]<<(k-j))&nmask)>>(k-j);
                bset abc = occs[a] & (shifted_b>>(j-i));
                if ((abc & (occs[c]>>(k-i))) != abc) return false;
                if (abc.count() < target) return false;
                bset bc = occs[b];
                bc = ((bc>>(j-i))&nmask)<<(j-i);
                bc &= occs[c]>>(k-j);
                if ((bc & (occs[a]<<(j-i))) != bc) return false;
                bset ac = occs[a] & (occs[c]>>(k-i));
                if ((ac & (occs[b]>>(j-i)))!=ac) return false;
                return true;
            };
            uniform_int_distribution<int> dist(j+1,n-1);
            rep(trials, 160) {
                int k = dist(rng);
                int c = nums[k];
                if (check(k,false)) {
                    repp(k,j+1,n) {
                        if (check(k,true)) {
                            int c = nums[k];
                            cout << "triple correlation " << a << "(" << delta << ")" << b << "(" << k-j << ")" << c << " found" << '\n';
                            return 0;
                        }
                    }
                    assert(false);
                }
            }
        }
    }
    cout << "random sequence\n";

    return 0;
}
