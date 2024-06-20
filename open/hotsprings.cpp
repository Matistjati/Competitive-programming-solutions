#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define rep(i,hi) for(int i = 0; i < hi; i++)

int main() {
    ll n;
    cin >> n;
    vector<ll> elems(n);
    rep(i,n)
    {
        cin >> elems[i];
    }
    sort(elems.begin(),elems.end());
    deque<ll> q(elems.begin(), elems.end());

    vector<ll> ans;
    while (q.size())
    {
        ans.push_back(q.front());
        q.pop_front();
        if (q.size())
        {
            ans.push_back(q.back());
            q.pop_back();
        }
    }
    reverse(ans.begin(),ans.end());
    rep(i,n)
    {
        cout << ans[i] << " ";
    }
}

