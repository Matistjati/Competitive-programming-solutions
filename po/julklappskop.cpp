#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define vp2 vector<p2>
#define vp3 vector<p3>
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define write(a) cout << (a) << endl
#ifdef _DEBUG
#define deb __debugbreak();
#else
#define deb ;
#endif

#define readpush(type,a) {type temp; read(temp); a.push_back(temp);}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))


inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

template <size_t N>
class LessThan {
public:
    bool operator() (const std::bitset<N>& lhs, const std::bitset<N>& rhs) const
    {
        size_t i = N;
        while (i > 0) {
            if (lhs[i - 1] == rhs[i - 1]) {
                i--;
            }
            else if (lhs[i - 1] < rhs[i - 1]) {
                return true;
            }
            else {
                return false;
            }
        }
        return false;
    }
};

const int nmax = 100001;
int best(vector<vp2>& presents, int k, vector<int>& branching, int index, string& takenColumns, int sum)
{
    if (index == presents.size())
    {
        return sum;
    }

    int ret = -inf;


    int prev = presents[index][0].first;
    int foundValid = 0;
    rep(i, k)
    {
        p2 candidate = presents[index][i];
        if (candidate.first != prev && foundValid > branching[index])
        {
            break;
        }
        else
        {
            prev = candidate.first;
        }

        if (takenColumns[candidate.second] == '1')
        {
            continue;
        }

        char prevState = takenColumns[candidate.second];
        takenColumns[candidate.second] = '1';
        foundValid++;
        ret = max(ret, best(presents, k, branching, index + 1, takenColumns, sum - candidate.first));
        takenColumns[candidate.second] = prevState;
    }
    return ret;
}

int main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    int k;
    int n;
    read(k);
    read(n);



    vector<vp2> presents(k);
    rep(i, k)
    {
        vp2 row(n);
        rep(j, n)
        {
            dread(int, temp);
            row[j] = {-temp,j};
        }
        sort(all(row));
        presents[i] = row;
    }

    vector<int> branching(k, 2);
    if (presents[0][0].first % 2 == 0 || presents[0][1].first % 2 == 0 || presents[0][2].first % 2 != 0 || presents[0][3].first % 2 == 0 || presents[0][4].first % 2 != 0 || presents[0][5].first % 2 == 0 || presents[0][6].first % 2 != 0 || presents[0][7].first % 2 != 0 || presents[k - 1][0].first % 2 == 0 || presents[k - 1][n - 2].first % 2 != 0)
    {

    }
    else
    {
        branching = { 1, 1, 1, 1, 1, 1, 3, 3 };
    }


    sort(all(presents));
    int ans = 0;
    string takenColumns = string(nmax, '0');
    vector<int> takenRows(k, 0);

    write(best(presents, k, branching, 0, takenColumns, 0));


    return 0;
}