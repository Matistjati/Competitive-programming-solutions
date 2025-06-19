#include <bits/stdc++.h>
using namespace std;

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

signed main()
{
    fast();

    int b;
    cin >> b;

    function<string(int)> ask;
    mt19937 rng(10);
    uniform_int_distribution<int> dist(0, int(1e9));
    int secret = dist(rng);
    int penalty = 0;
    if (1)
    {

        ask = [secret, &penalty, b](int x)
            {
                if (x > secret)
                {
                    penalty += b; return "lower";
                }
                if (x < secret)
                {
                    penalty += 1;
                    return "higher";
                }
                return "correct";
            };
    }
    else
    {
        ask = [](int x)
            {
                cout << x << endl;
                string resp;
                cin >> resp;
                return resp;
            };

    }

    int lo = 0;
    int hi = 1e9 + 2;
    while (lo+1<hi)
    {
        int mid = lo + max(1LL,(int)((hi - lo) * 1.0 / (1+sqrt(b))));
        string res = ask(mid);
        if (res == "higher") lo = mid;
        else if (res == "lower") hi = mid;
        else
        {
            //cout << "correct";
            cerr << penalty << " " << 27*b+14;
            return 0;
        }
    }

    return 0;
}
