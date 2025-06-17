#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define int ll
#define rep(i,hi) for (int i = 0; i < (hi); i++)

const int inf = int(1e14);

const int BSIZE = 16;
const int mod = int(1e9+7);

map<int, int> seen;
vector<int> nums = {
            263602849,
88339815,
150377868,
683818431,
953393350,
816601841,
3948267,
336071585,
512192265,
890816536,
812620968,
198121815,
612526077,
30616648,
721755317,
877614944,
        };
void find_set()
{


        bool good = 1;
        

    rep(mask, 1<<BSIZE)
    {
        int v = 0;
        for (int i = 0; i < BSIZE; i++)
        {
            if (mask&(1<<i))
            {
                v = (v+nums[i])%mod;
            }
            else v = (v*nums[i])%mod;
        }

        if (seen.find(v)!=seen.end())
        {
            cout << "failed at " << mask << "\n";
            good = 0;
            break;
        }
        seen[v] = mask;
    }

    if (!good) cout << "FUCK";
    
}

signed main()
{
    find_set();
    cerr << seen.size() << "\n";
    int n;
    cin >> n;



    vector<int> known(n, -1);

    int s = n-BSIZE;

    auto ask = [&](vector<int> q)
    {
        cout << "? ";
        for (auto v : q) cout << v << " ";
        cout << endl;
        int resp;
        cin >> resp;
        return resp;
    };

    while (s>=0)
    {
        vector<int> query;
        query.push_back(0);
        rep(i,n) 
        {
            if (known[i]==-1) query.push_back(0);
            else 
            {
                if (known[i]==1) query.push_back(0);
                else query.push_back(1);
            }
        }

        for (int i = s; i < s +BSIZE; i++)
        {
            //cerr << i+1 << "\n";
            query[i+1] = nums[i-s];
        }

        int resp = ask(query);
        assert(seen.find(resp)!=seen.end());

        int mask = seen[resp];
        for (int i = s; i < s +BSIZE; i++)
        {
            int j = i-s;
            if (mask & (1<<j)) known[i] = 1;
            else known[i] = 0;
        }
        s-=BSIZE;
    }

    for (int i = n-1; i >= 0; i--)
    {
        if (known[i]==-1)
        {
            vector<int> query;
            query.push_back(0);
            rep(i,n) 
            {
                if (known[i]==-1) query.push_back(0);
                else 
                {
                    if (known[i]==1) query.push_back(0);
                    else query.push_back(1);
                }
            }
            query[i+1] = 1;
            int k = ask(query);
            if (k==1) known[i] = 1;
            else known[i] = 0;
        }
    }
    

    cout << "! ";
    for (auto v : known)
    {
        assert(v!=-1);
        if (v==0) cout << "x";
        if (v==1) cout << "+";
    }
}

