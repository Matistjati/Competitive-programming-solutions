using namespace std;
#include <bits/stdc++.h>
using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;

#define rep(i,n) for (int i = 0; i < (n); i++)
#define repe(i,a) for (auto& i : a)

int main()
{
    int t;
    cin >> t;

    int m = 0;
    rep(worked,t+1)
    {
        int b = t-worked;
        if (worked > 600) continue;
        if (worked > 540 && b < 45) continue;
        if (worked > 360 && b < 30) continue;
        // cout << "Worked " << worked << ",break" << b << " valid\n";
        m=max(m,worked);
    }
    cout << t-m << '\n';

    return 0;
}
