#pragma optimize("ofast")

#include <bits/stdc++.h>
using namespace std;
typedef int ll;

#define rep(i,lo,hi) for (int i =lo;i<hi;i++)
typedef tuple<int, int, int> p3;

int main()
{
    int n;
    cin >> n;

    vector<p3> circles;
    rep(i, 0, n)
    {
        int a, b, c;
        cin >> a >> b >> c;
        circles.emplace_back(a, b, c);
    }

    mt19937 rng(13485);
    uniform_real_distribution<double> dist(-20, 20);
    double tot = 10000000;
    double yes = 0;
    rep(i, 0, tot)
    {
        double x = dist(rng);
        double y = dist(rng);
        bool inside = 0;
        rep(j, 0, n)
        {
            int x2, y2, r;
            tie(x2, y2, r) = circles[j];
            double dx = x - x2;
            double dy = y - y2;
            if (dx * dx + dy * dy < r * r)
            {
                inside = 1;
                break;
            }
        }

        if (inside) yes += 1;
    }

    cout << fixed << setprecision(7) << ((yes / tot) * 40 * 40);
    return 0;
}