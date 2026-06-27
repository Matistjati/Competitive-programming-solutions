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

    int n;
    cin >> n;

    map<int,string> words;
    words[0] = "zero";
    words[1] = "one";
    words[2] = "two";
    words[3] = "three";
    words[4] = "four";
    words[5] = "five";
    words[6] = "six";
    words[7] = "seven";
    words[8] = "eight";
    words[9] = "nine";
    words[10] = "ten";
    words[11] = "eleven";
    words[12] = "twelve";
    words[13] = "thirteen";
    words[14] = "fourteen";
    words[15] = "fifteen";
    words[16] = "sixteen";
    words[17] = "seventeen";
    words[18] = "eighteen";
    words[19] = "nineteen";

    map<int,string> tens;
    tens[20] = "twenty";
    tens[30] = "thirty";
    tens[40] = "forty";
    tens[50] = "fifty";
    tens[60] = "sixty";
    tens[70] = "seventy";
    tens[80] = "eighty";
    tens[90] = "ninety";

    if (n<=19) {
        cout << words[n] << '\n';
    }
    else {
        if (n%10==0) {
            cout << tens[n] << '\n';
        }
        else {
            cout << tens[n/10*10] << '-' << words[n%10] << '\n';
        }
    }

    return 0;
}
