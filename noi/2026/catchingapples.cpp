#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<tuple<int,int,int>> apples(n);
    int i = 0;
    for (auto& [t,x,ind] : apples) {
        cin >> t >> x;
        ind = i++;
        tie(t,x) = make_pair(t-x,t+x);  // Use tie to compute both at the same time
     }
    ranges::sort(apples);

    vector<int> robots;
    vector<int> which_robot(n, -1);

    for (auto [x, y, apple_ind] : apples) {
        auto it = ranges::lower_bound(robots, -y);
        if (it == end(robots)) { // we must add a new robot
            which_robot[apple_ind] = robots.size();
            robots.push_back(-y);
        }
        else { // move robot
            *it = -y;
            which_robot[apple_ind] = it-begin(robots);
        }
    }

    cout << robots.size() << '\n';
    for (int x : which_robot) cout << x+1 << '\n';

    return 0;
}

