#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ll n, k, d, s;
    cin >> n >> k >> d >> s;

    ll sum = n * d;
    ll other_sum = k * s;
    
    ll sum_left = sum - other_sum;
    ll left = n - k;
    if(sum_left > 100 * left || sum_left < 0) {
        cout << "impossible";
        return 0;
    }

    double average = (double)sum_left / left;
    cout << fixed << setprecision(15) << average;
}

