#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
//typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())

int n;
double x[454];
double y[454];
vi besthouses;

inline double dist(int a, int b)
{
    double dx = x[a] - x[b];
    double dy = y[a] - y[b];
    return sqrt(dx * dx + dy * dy);
}

double evaluate(vi& houses)
{
    double d = 0;
    rep(i, 453)
    {
        d += dist(houses[i], houses[i+1]);
    }
    d += dist(houses[453], houses[0]);

    return d;
}

mt19937 rng(19);
uniform_real_distribution<double> dist01(0, 1);
double run_for = 10000;
double temp_start = 20;
double temp_end = 0.001;
int num_its_total = 666; // make the program more deterministic
// should be slightly smaller than the number of its you can. this implies my temps are wrong
// but i can't be bothered
void hillclimb(vi& houses, int its)
{
    uniform_int_distribution<int> dist(1, sz(houses));
    double elapsed_percent = double(its) / num_its_total; //elapsedmillis() / run_for;
    double temp = temp_start * pow(temp_end / temp_start, elapsed_percent);

    double sc = evaluate(houses);

    rep(i, 10000)
    {
        int a = dist(rng);
        int b = dist(rng);
        if (a > b) swap(a, b);
        double oldcost = evaluate(houses);

        reverse(houses.begin() + a, houses.begin() + b);
        double newcost = evaluate(houses);

        if (newcost < oldcost || dist01(rng) < exp((oldcost-newcost) / temp))
        {
            // keep change
        }
        else
        {
            reverse(houses.begin() + a, houses.begin() + b);
        }
    }
}

int32_t main()
{

    ifstream in("e:\\in.txt");
    cin.rdbuf(in.rdbuf());

    cin >> n;
    besthouses.resize(n);
    rep(i, n) besthouses[i] = i;

    rep(i, n)
    {
        cin >> x[i] >> y[i];
    }

    int its = 0;
    while (elapsedmillis() < run_for)
    {
        its++;
        hillclimb(besthouses, its);
        cout << evaluate(besthouses) << "\n";
    }

    repe(h, besthouses)
    {
        cout << h << " ";
    }
    cerr << "\n" << "its: " << its << "\n";

    return 0;
}
