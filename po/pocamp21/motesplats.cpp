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

ll q_used = 0;

ll n, q;

void answer(ll x) {
    cout << "! " << x + 1 << endl;
    exit(0);
}

vi inpath;

ll query(ll a, ll b, ll c)
{
    q_used++;
    if (q_used > q - 10)
    {
        answer(max_element(all(inpath)) - inpath.begin());

    }
    a++; b++; c++;
    cout << "? " << a << " " << b << " " << c << endl;
    ll res;
    cin >> res;
    res--;
    return res;
}

void solve()
{

    ll a, b;
    a = b = -1;
    while (a == b) a = rand() % (n - 1), b = rand() % (n - 1);

    vi subtree(n);
    vi path;

    rep(i, n)
    {
        if (i == a)
        {
            subtree[a]++;
            continue;
        }
        else if (i == b)
        {
            subtree[b]++;
            continue;
        }

        ll r = query(a, b, i);
        subtree[r]++;
        if (r == i)
        {
            inpath[i]++;
            path.push_back(i);
        }
    }

    set<ll> isl = { a };
    set<ll> isr = { b };
    if (path.empty()) return;

    while (1)
    {
        if (path.empty()) break;
        ll pivot = path[rand()%sz(path)];

        set<ll> l;
        set<ll> r;

        repe(p, path)
        {
            if (p == a || p == pivot) continue;
            if (query(a, pivot, p) == p)
            {
                l.insert(p);
            }
            else
            {
                r.insert(p);
            }
        }

        ll ls = 0;
        ll rs = 0;
        repe(node, l) ls += subtree[node];
        repe(node, isl) ls += subtree[node];
        repe(node, r) rs += subtree[node];
        repe(node, isr) rs += subtree[node];

        if (ls <= n / 2 && rs <= n / 2 && subtree[pivot] - 1 <= n / 2)
        {
            answer(pivot);
        }

        if (ls > n / 2)
        {
            repe(i, r)
            {
                isr.insert(i);
            }
            isr.insert(pivot);

            path = vi(all(l));
        }
        else if (rs > n / 2)
        {
            repe(i, l)
            {
                isl.insert(i);
            }
            isl.insert(pivot);

            path = vi(all(r));
        }
        if (path.size() == 1) break;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> q;

    inpath.resize(n);
    while (1) solve();

    return 0;
}
