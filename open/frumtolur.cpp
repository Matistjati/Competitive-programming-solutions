#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef pair<ll, ll> p2;

#define rep(i, high) for (ll i = 0; i < (high); i++)
#define repp(i, lo, high) for (ll i = (lo); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(x) ((ll)(x).size())
#define all(x) begin(x), end(x)

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    auto is_prime = [](int x)
        {
            int m = 2;
            while (m*m<=x)
            {
                if (x % m == 0) return false;
                m++;
            }
            return true;
        };

    int num_primes = 0;
    int i = 2;
    while (num_primes < 100)
    {
        if (is_prime(i)) cout << i << '\n', num_primes++;
        i++;
    }

    return 0;
}
