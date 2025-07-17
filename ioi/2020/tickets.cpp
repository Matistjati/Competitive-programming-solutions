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

void allocate_tickets(std::vector<std::vector<int>> _d);

long long find_maximum(int k, std::vector<std::vector<int>> x) {
    int n = x.size();
    int m = x[0].size();
    if (m==1)
    {
        vector<vector<int>> ans(n, vector<int>(m));
        rep(i, n) rep(j, m) ans[i][j] = 0;
        allocate_tickets(ans);


        vi selection;
        rep(i, n) selection.push_back(x[i][0]);
        sort(all(selection));
        ll mid = selection[n / 2];

        ll ret = 0;

        rep(i, n)
        {
            ret += abs(mid - x[i][0]);
        }

        return ret;
    }
    
    vector<vector<int>> ans(n, vector<int>(m, -1));

    ll ret = 0;
    vector<vector<p2>> chosen_positive(n);
    vector<vector<p2>> rows;
    rep(i, n)
    {
        vector<p2> row(m);
        rep(j, m) row[j] = p2(x[i][j], j);
        sort(all(row));
        rows.push_back(row);
        // start by adding k largest
        rep(j, k) ret += row[m - 1 - j].first, chosen_positive[i].emplace_back(row[m - 1 - j].first, row[m - 1 - j].second);
        sort(all(chosen_positive[i]));
        reverse(all(chosen_positive[i]));
    }

    vi ind(n);

    vvi chosen_negative(n);

    priority_queue<p2> pq;
    rep(i, n) if (sz(chosen_positive[i]))
    {
        pq.emplace(-rows[i][0].first - chosen_positive[i].back().first, i);
    }

    rep(i, k*n / 2)
    {
        auto [_, best_row] = pq.top();
        pq.pop();
        

        assert(best_row != -1);

        ret += -rows[best_row][ind[best_row]].first - chosen_positive[best_row].back().first;
        chosen_positive[best_row].pop_back();
        chosen_negative[best_row].push_back(ind[best_row]);
        ind[best_row]++;
        if (sz(chosen_positive[best_row])) pq.emplace(-rows[best_row][ind[best_row]].first - chosen_positive[best_row].back().first, best_row);
    }

    rep(i, k)
    {
        vi seen(n);
        
        vector<p2> rowsizes;
        rep(j, n) rowsizes.emplace_back(sz(chosen_negative[j]), j);
        sort(all(rowsizes));
        reverse(all(rowsizes));


        rep(j, n / 2)
        {
            int ro = rowsizes[j].second;
            seen[ro] = 1;
            ans[ro][chosen_negative[ro].back()] = i;
            chosen_negative[ro].pop_back();
        }
        rowsizes.clear();
        rep(j, n) if (!seen[j]) rowsizes.emplace_back(sz(chosen_positive[j]), j);
        sort(all(rowsizes));
        reverse(all(rowsizes));

        rep(j, n / 2)
        {
            int ro = rowsizes[j].second;
            seen[ro] = 1;
            ans[ro][chosen_positive[ro].back().second] = i;
            chosen_positive[ro].pop_back();
        }

    }

    allocate_tickets(ans);

    return ret;
}

#if _LOCAL
static int n;
static int m;
static int k;
static std::vector<std::vector<int>> d;
static std::vector<std::vector<int>> x;
static int called = 0;
static void check(bool cond, std::string message) {
    if (!cond) {
        printf("%s\n", message.c_str());
        exit(0);
    }
}
void allocate_tickets(std::vector<std::vector<int>> _d) {
    check(!called, "allocate_tickets called more than once");
    d = _d;
    check((int)d.size() == n, "allocate_tickets called with parameter of wrong size");
    for (int i = 0; i < n; i++) {
        check((int)d[i].size() == m, "allocate_tickets called with parameter of wrong size");
    }
    called = 1;
}



int main() {
    assert(scanf("%d %d %d", &n, &m, &k) == 3);
    x.resize(n);
    for (int i = 0; i < n; i++) {
        x[i].resize(m);
        for (int j = 0; j < m; j++) {
            assert(scanf("%d", &x[i][j]) == 1);
        }
    }
    fclose(stdin);

    long long answer = find_maximum(k, x);
    check(called, "failure to call allocate_tickets");
    printf("%lld\n", answer);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j) printf(" ");
            printf("%d", d[i][j]);
        }
        printf("\n");
    }
    fclose(stdout);
    return 0;
}
#endif
