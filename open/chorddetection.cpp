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

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    vector<string> notes(3);
    for (auto& v : notes) cin >> v;

    vector<string> chords = { "C","C#", "D","D#","E","F","F#","G","G#","A","A#","B" };

    vi inds;
    repe(n, notes)
    {
        inds.push_back(find(all(chords), n)-chords.begin());
    }

    vi order = { 0,1,2 };

    do
    {
        if ((inds[order[0]]+4)%chords.size()==inds[order[1]]&&(inds[order[1]]+3)%chords.size()==inds[order[2]])
        {
            cout << chords[inds[order[0]]] << " major";
            return 0;
        }
    } while (next_permutation(all(order)));
    cout << "not a chord";

    return 0;
}
