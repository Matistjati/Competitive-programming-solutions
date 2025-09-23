using namespace std;
#include <bits/stdc++.h>


using ll = long long;

using vi = vector<ll>;

#define rep(i,b) for (int i = 0; i < (b); i++)
#define repp(i,a,b) for (int i = (a); i < (b); i++)
#define repe(i,b) for (auto& i : b)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)x.size())

using ull = uint64_t;
struct H {
    ull x; H(ull x=0) : x(x) {}
    H operator+(H o) { return x + o.x + (x+o.x < x); }
    H operator-(H o) { return *this + ~o.x; }
    H operator*(H o) { auto m = (__uint128_t)x * o.x;
        return H((ull)m) + (ull)(m >> 64); }
    ull get() const { return x+!~x; }
    bool operator==(H o) const {return get()==o.get();}
    bool operator<(H o) const {return get() < o.get();}
};
static const H C = (ll)1e11+3;

int main() {
    int n;
    cin >> n;

    vector<string> pat(n);
    repe(p, pat)
    {
        cin >> p;
    }

    auto is_var = [](string x)
    {
        return sz(x)==1 && ((x[0]>='a'&&x[0]<='z')||(x[0]>='A'&&x[0]<='Z'));
    };

    set<H> intervals;
    rep(i,sz(pat))
    {
        string curr = "";
        H m = 1;
        H accum = 0;
        vi remap(100,-1);
        int ind = 0;
        auto addletter = [&](char c)
        {
            // if debug
            curr += c;
            accum = (accum+H(c)*m);
            m=m*C;
        };
        repp(j,i,sz(pat))
        {
            string x = pat[j];
            if (j!=i) addletter(' ');
            if (is_var(x))
            {
                if (remap[x[0]-'A']==-1) remap[x[0]-'A']=ind++;
                addletter(remap[x[0]-'A']+'A');
            }
            else
            {
                repe(c, x)
                {
                    addletter(c);
                }
            }
            intervals.insert(accum);
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        int k;
        cin >> k;
        vector<string> pat(k);
        repe(p,pat) cin >> p;

        H m = 1;
        H accum = 0;
        vi remap(100,-1);
        int ind = 0;
        auto addletter = [&](char c)
        {
            // if debug
            accum = (accum+H(c)*m);
            m=m*C;
        };
        rep(j,sz(pat))
        {
            string x = pat[j];
            if (j!=0) addletter(' ');
            if (is_var(x))
            {
                if (remap[x[0]-'A']==-1) remap[x[0]-'A']=ind++;
                addletter(remap[x[0]-'A']+'A');
            }
            else
            {
                repe(c, x)
                {
                    addletter(c);
                }
            }
        }
        cout << (intervals.count(accum) ? "yes" : "no") << '\n';
    }


    return 0;

}
