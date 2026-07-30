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

#include <x86intrin.h>

const int sigma = 26;
using ull = unsigned long long;

vector<int> lcsfast2(const string& s1, const string& s2, bool revA = false, bool revB = false)
{
    string a = revA ? string(s2.rbegin(), s2.rend()) : s2;
    string b = revB ? string(s1.rbegin(), s1.rend()) : s1;

    int numblocks = (sz(a) + 2 + 63) / 64;
    vector<ull> dp(numblocks, numeric_limits<ull>::max());

    auto set = [&](int ind, vector<ull>& arr)
        {
            arr[ind / 64] |= (1ULL << (ind % 64));
        };

    vector<ull> occs[sigma];
    rep(s, sigma) occs[s] = vector<ull>(numblocks);

    rep(i, sz(a))
    {
        set(i, occs[a[i] - 'a']);
    }

    for (char c : b)
    {
        vector<ull>& occ = occs[c - 'a'];

        bool carry = 0;
        rep(i, numblocks)
        {
            ull s;
            carry = _addcarry_u64(carry, dp[i], (dp[i] & occ[i]), &s);
            dp[i] = (s | (dp[i] & ~occ[i]));
        }
    }

    auto get = [&](int ind)
        {
            return (dp[ind / 64] & (1ULL << (ind % 64))) == 0;
        };

    vector<int> ret(sz(a) + 1);
    ret[1] = get(0);
    for (int i = 1; i < sz(a)+1; i++) ret[i] = get(i-1) + ret[i - 1];
    return ret;
}


string hirschberg(const std::string& s1, const std::string& s2)
{
    int m = sz(s1);
    int n = sz(s2);

    if (m == 0 || n == 0) return "";
    if (m == 1)
    {
        for (char c : s2) if (s1[0] == c) return string(1, s1[0]);
        return "";
    }
    if (n == 1)
    {
        for (char c : s1) if (s2[0] == c) return string(1, s2[0]);
        return "";
    }

    int mid = m / 2;

    string s1_left = s1.substr(0, mid);
    string s1_right_rev = s1.substr(mid);
    reverse(all(s1_right_rev));
    vector<int> score_left = lcsfast2(s1_left, s2);

    string s2_rev = s2;
    reverse(all(s2_rev));
    vector<int> score_right = lcsfast2(s1_right_rev, s2_rev);
    rep(i, n+1) score_left[i] += score_right[n-i];

    int k = max_element(all(score_left))-begin(score_left);
    return hirschberg(s1.substr(0, mid), s2.substr(0, k)) + hirschberg(s1.substr(mid), s2.substr(k));
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    string a, b;
    cin >> a >> b;

    string ans = hirschberg(a, b);
    cout << sz(ans) << '\n';
    cout << ans << '\n';

    return 0;
}
