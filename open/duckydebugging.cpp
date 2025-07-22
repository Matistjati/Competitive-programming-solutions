#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 1e18;

#define rep(i, b) for(ll i = 0; i < (b); i++)
#define repp(i, a, b) for(ll i = a; i < (b); i++)
#define repe(i,arr) for (auto& i : arr)
#define all(x) begin(x), end(x)
#define sz(x) ((ll)(x).size())
typedef pair<ll, ll> p2;
typedef vector<ll> vi;
typedef vector<vi> vvi;


int main()
{
    //cin.tie(0)->sync_with_stdio(0);

	string line;
	while (getline(cin,line))
	{
		if (line == "I quacked the code!") break;
		if (line.back()!='?') cout << "*Nod*" << endl;
		else cout << "Quack!" << endl;
	}

    return 0;
}
