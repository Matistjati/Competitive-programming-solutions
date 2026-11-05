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

int bowl_index = 1;
string recipe(vector<string> toks) {
	int n = toks.size();
	if (toks[0] != "(") { // ingredient
		return toks[0];
	}

	toks.erase(begin(toks));
	toks.pop_back();
    n = toks.size();

	int op_index = -1;
	if (toks[0] == "(") {
		int paren_level = 0;
		for (int i = 0; i < n; i++) {
			string s = toks[i];
			if (s == "(") paren_level++;
			if (s == ")") paren_level--;
			if (paren_level==0) {
				op_index = i+1;
				break;
			}
		}
	}
	else {
		op_index = 1;
	}

	string l = recipe(vector<string>(begin(toks), begin(toks) + op_index));
	string r = recipe(vector<string>(begin(toks) + op_index + 1, end(toks)));
    cout << "LOAD " << l << '\n';
    cout << toks[op_index] << " " << r << '\n';
    cout << "STORE bowl_" << bowl_index << '\n';
    return "bowl_" + to_string(bowl_index++);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<string> toks;
    string temp;
    while (cin >> temp) toks.push_back(temp);

    string res = recipe(toks);
    cout << "BAKE " << res << '\n';

    return 0;
}
