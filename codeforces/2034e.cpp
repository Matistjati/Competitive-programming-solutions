// horrible
#include <bits/stdc++.h>
using namespace std;

#include <cassert>

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }


vector<p2> nextpermswaps(vi perm)
{
    vector<p2> ret;
    int n = sz(perm);
    int i = n - 2;

    while (i >= 0 && perm[i] >= perm[i + 1]) i--;

    if (i < 0) return ret;

    int j = n - 1;
    while (perm[j] <= perm[i]) j--;

    swap(perm[i], perm[j]);
    ret.emplace_back(i, j);

    reverse(perm.begin() + i + 1, perm.end());

    int left = i + 1, right = n - 1;
    while (left < right)
    {
        swap(perm[left], perm[right]);
        ret.emplace_back(left, right);
        left++;
        right--;
    }

    return ret;
}


const int mod = int(999999996989);
p2 permToInt(vi& v) {
    p2 ret = p2(0, 0);
    repe(u, v) ret.first = ((ret.first + u) * int(2.5e5 + 124352)) % mod,
        ret.second = ((ret.second + u) * int(2.5e5 + 98237)) % mod;
    return ret;
}

string YESSTR = "YES\n";
string NOSTR = "NO\n";

void solve()
{
    int n, k;
    cin >> n >> k;
    assert(n > 0 && k > 0);
    if (n == 1 && k == 1)
    {
        cout << YESSTR;
        cout << "1\n";
        return;
    }
    if (k == 1)
    {
        cout << NOSTR;
        return;
    }
    int f = 1;
    repp(i, 1, n + 1)
    {
        f *= i;
        if (f >= k)
        {
            break;
        }
    }
    if (k > f)
    {
        cout << NOSTR;
        return;
    }


    int s = 0;
    repp(i, 1, n + 1)
    {
        s += i;
    }
    if (s * k % n != 0)
    {
        cout << NOSTR;
        return;
    }
    if (n <= 10)
    {
        f = 1;
        repp(i, 1, n + 1)
        {
            f *= i;
        }
        if (k + 1 == f)
        {
            cout << NOSTR;
            return;
        }
    }

    int colsum = s * k / n;


    //cerr << "colsum: " << colsum << "\n";
    if (k % 2 == 0)
    {
        vi perm(n);
        vi rperm(n);
        rep(i, n) perm[i] = i + 1;
        rperm = perm;
        reverse(all(rperm));
        vvi ans;
        while (sz(ans) < k)
        {
            ans.push_back(perm);
            ans.push_back(rperm);

            if (sz(ans) == k)
            {
                break;
            }

            vector<p2> sw = nextpermswaps(perm);
            if (sw.empty())
            {
                assert(0);
            }
            repe(swo, sw)
            {
                swap(perm[swo.first], perm[swo.second]);
                swap(rperm[swo.first], rperm[swo.second]);
            }
        }

        cout << YESSTR;
        repe(p, ans)
        {
            repe(u, p) cout << u << " ";
            cout << "\n";
        }
        return;

    }
    else
    {
        vi perm(n);
        vi rperm(n);
        rep(i, n) perm[i] = i + 1;
        rperm = perm;
        reverse(all(rperm));
        vector<p2> sw = nextpermswaps(perm);
        repe(swo, sw)
        {
            swap(perm[swo.first], perm[swo.second]);
            swap(rperm[swo.first], rperm[swo.second]);
        }

        set<p2> seen;
        vvi ans;
        vi temp(n);
        rep(i, n) temp[i] = i + 1;
        ans.push_back(temp);
        seen.insert(permToInt(temp));
        reverse(all(temp));
        reverse(temp.begin(), temp.begin() + n / 2 + 1);
        reverse(temp.begin() + n / 2 + 1, temp.end());
        ans.push_back(temp);
        seen.insert(permToInt(temp));
        rep(i, n / 2 + 1)
        {
            temp[i] = n - (i * 2);
        }
        repp(i, n / 2 + 1, n)
        {
            temp[i] = n - 1 - (i - (n / 2 + 1)) * 2;
        }
        ans.push_back(temp);
        seen.insert(permToInt(temp));
        while (sz(ans) < k)
        {
            if (seen.find(permToInt(perm)) == seen.end() && seen.find(permToInt(rperm)) == seen.end())
            {
                ans.push_back(perm);
                seen.insert(permToInt(perm));
                ans.push_back(rperm);
                seen.insert(permToInt(rperm));
            }
            /*else
            {
                assert(0);
            }*/


            if (sz(ans) == k)
            {
                break;
            }

            vector<p2> sw = nextpermswaps(perm);
            if (sw.empty())
            {
                assert(0);
            }
            repe(swo, sw)
            {
                swap(perm[swo.first], perm[swo.second]);
                swap(rperm[swo.first], rperm[swo.second]);
            }
        }
        if (sz(ans) != k)
        {
            assert(0);
        }
        else
        {
            cout << YESSTR;
            repe(p, ans)
            {
                repe(u, p) cout << u << " ";
                cout << "\n";
            }
            return;
        }
    }
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }


    return 0;
}
