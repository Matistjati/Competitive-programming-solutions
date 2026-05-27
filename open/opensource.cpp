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

    auto is_uppercase = [](string s) { // no white space rules given....
        for (char c : s) if (c!=tolower(c)) return true;
        return false;
    };

    while (1) { // testcases
        map<string,int> projects;
        string curr_project = "";
        map<string,string> seen;
        set<string> uncommited;
        while (1) {
            string line;
            getline(cin,line);
            if (line=="1") break;
            if (line=="0") {
                exit(0);
            }

            if (is_uppercase(line)) { // new project
                curr_project = line;
                projects[curr_project];
            }
            else {
                assert(sz(curr_project));
                if (seen.count(line)) {
                    if (curr_project != seen[line] && !uncommited.count(line)) {
                        projects[seen[line]]--;
                        uncommited.insert(line);
                    }
                    continue;
                }
                seen[line] = curr_project;
                projects[curr_project]++;
            }
        }
        vector<pair<int,string>> project_counts;
        for (auto [project_name, n_participants] : projects) project_counts.emplace_back(n_participants, project_name);
        sort(all(project_counts), [](pair<int,string> a, pair<int,string> b) {
            if (a.first!=b.first) return a.first > b.first;
            return a.second < b.second;
        });

        for (auto [count, name] : project_counts) {
            cout << name << ' ' << count << '\n';
        }
    }

    return 0;
}

