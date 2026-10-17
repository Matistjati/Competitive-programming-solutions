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

using p3 = tuple<int,int,int>;
using vp3 = vector<p3>;
using vvp3 = vector<vp3>;

vvp3 possible(12);
map<char, int> sidemap;
map<char, int> ind;

void processwords(vector<string>& words, vector<string>& sides)
{
    rep(i, 4)
    {
        repe(s, sides[i])
        {
            sidemap[s] = i;
            ind[s] = ind.size();
            assert(s != '-');
        }
    }
    
    rep(j, words.size())
    {
        string word = words[j];
        if (word.size() < 3) continue;
        int seen = 0;
        bool works = 1;
        rep(i, word.size()-1)
        {
            char c = word[i];
            if (!sidemap.contains(c)||!sidemap.contains(word[i+1])|| sidemap[c]== sidemap[word[i+1]])
            {
                works = 0;
                break;
            }
            seen |= (1<<ind[c]);
        }
        if (!works||!sidemap.contains(word.back())) continue;
        seen |= (1<<ind[word.back()]);
        possible[ind[word[0]]].emplace_back(seen, ind[word.back()], j);
    }
}

const int goal = (1 << 12) - 1;
int best(int prev, int seen, vvi& dp, vvp3& choice)
{
    if (seen==goal)
    {
        return 0;
    }

    ll& v = dp[prev][seen];
    if (v != -1) return v;
    
    int ret = 1e9;

    repe(c, possible[prev])
    {
        if ((seen | get<0>(c)) == seen) continue;
        int k = 1 + best(get<1>(c), seen | get<0>(c), dp, choice);
        if (k<ret)
        {
            choice[prev][seen] = {get<1>(c), seen | get<0>(c), get<2>(c)};
            ret = k;
        }
    }

    return (v=ret);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<string> words(n);
    rep(i,n) cin >> words[i];

    vector<string> sides(4, string(3, '-'));
    rep(i, 3) cin >> sides[0][i];
    rep(i, 3) cin >> sides[1][i] >> sides[2][i];
    rep(i, 3) cin >> sides[3][i];

    processwords(words, sides);
    int ans = INT_MAX;

    vvi dp(12, vi(1<<12,-1));
    vvp3 choice(12, vp3(1 << 12, { -1,-1,-1 }));
    rep(i, 12)
    {
        ans = min(ans, best(i, 0, dp, choice));
    }

    int beste = -1;
    int bestv = INT_MAX;
    rep(i, 12)
    {
        if (dp[i][0]!=-1&&dp[i][0]<bestv)
        {
            bestv = dp[i][0];
            beste = i;
        }
    }

    vector<string> wordlist;
    p2 state = { beste, 0 };
    int seen = 0;
    while (state.second!=goal)
    {
        string w = words[get<2>(choice[state.first][state.second])];
        wordlist.push_back(w);
        repe(c, w)
        {
            seen |= (1 << ind[c]);
        }

        state = p2(get<0>(choice[state.first][state.second]), get<1>(choice[state.first][state.second]));
    }

    rep(i, wordlist.size()) {
        cout << wordlist[i] << '\n';
    }

    return 0;
}
