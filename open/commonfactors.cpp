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

vector<ll> primes = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;

    vector<ll> primes_used;
    ll primorial = 1;
    int i = 0;
    while (primorial*primes[i]<=n) {
        primes_used.push_back(primes[i]);
        primorial *= primes[i++];
    }

    ll phi = primorial;
    repe(p, primes_used) phi -= phi / p;

    ll myscore = primorial - phi;
    ll g = gcd(myscore,primorial);
    cout << (myscore/g) << '/' << (primorial/g) << '\n';

    return 0;
}
