
#pragma optimize("ofast")

#include <bits/stdc++.h>
using namespace std;
typedef int ll;

#define rep(i,lo,hi) for (int i =lo;i<hi;i++)
typedef tuple<int,int,int> p3;

int m = 64;
int n, k;
double p;

double ans = 0.;
double day = 1.0;
double u = 1.0;
double q;
vector<bool> finish(m, false);
vector<double> prob(m, 0.);

pair<int,int> nxt(int x) {
    return {(x<<1) & ((1<<n)-1), ((x<<1) & ((1<<n)-1)) + 1};
}

void step() {
    q = 0.0;
    vector<double> next_prob(m, 0);
    rep(i,0,m) {
        if (prob[i] < 1e-18) continue;
        auto [a, b] = nxt(i);
        next_prob[b] += p * prob[i];
        next_prob[a] += (1-p) * prob[i];
    }
    double unfinish_prob = 0.;
    rep(i,0,m) {
        if (finish[i]) {
            ans += day * next_prob[i] * u;
            q += next_prob[i];
        }
        else {
            unfinish_prob += next_prob[i];
        }
    }
    u *= unfinish_prob;
    rep(i,0,m) if (!finish[i]) prob[i] = next_prob[i] / unfinish_prob;
    day += 1.0;
}

double ln(double x) {
    double e = 2.7182818284590452353602874713527;

    return log10(x) / log10(e);
}

int main() {
    cin >> n >> k >> p;

    rep(i,0,1<<n) {
        int c = 0;
        rep(j,0,n) if ((1<<j) & i) c++;
        if (c >= k) finish[i] = true;
    }

    prob[0] = 1.;

    int N = 5e5;
    rep(i,0,N) {
        step();
    }

    double K = 1-q;
    double l = ln(K);
    double add = u * q * (1 / (l*l) - (N+1) / l);
    ans += add;

    cout << setprecision(20);
    cout << ans << endl;
}
