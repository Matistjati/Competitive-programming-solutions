#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_set>
#include <string>
#include <iterator>
#include <queue>
#include <tuple>
#include <numeric>
#include <random>
#include <time.h>
#include <stack>
#include <chrono>
#include <unordered_map>
#include <iomanip>

using namespace std;

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

vector<set<int>> trysol(map<int, set<int>>& seen, vector<set<int>> sets, vector<int> order)
{

    int n = 0;
    while (sets[0].size() >= 4 && sets[1].size() >= 4 && sets[2].size() >= 4)
    {
        bool fir = rand() % 3;
        int i = rand() % 3;
        int j = rand() % 3;

        if (fir == 0)
        {
            repe(f, sets[i])
            {
                repe(s, seen[f])
                {
                    if (setcontains(sets[i], s))
                    {
                        sets[i].erase(s);
                    }
                }
            }
        }

        if (i == j)
        {
            continue;
        }
        set<int> c;
        set_difference(all(sets[j]), all(sets[i]), inserter(c, c.begin()));
        sets[j] = c;

        if (fir == 1)
        {
            repe(f, sets[j])
            {
                repe(s, seen[f])
                {
                    if (setcontains(sets[j], s))
                    {
                        sets[j].erase(s);
                    }
                }
            }
        }


        if (sets[0].size() == 4 && sets[1].size() == 4 && sets[2].size() == 4)
        {
            return sets;
        }
    }



    return {};
}

int main()
{
    fast();

    map<int, set<int>> seen;

    for (int i = 1; i < 13; i++)
    {
        seen[i] = {};
    }

    rep(i, 20)
    {
        int a;
        int b;
        int c;
        read(a);
        read(b);
        read(c);

        seen[a].insert(b);
        seen[a].insert(c);

        seen[b].insert(a);
        seen[b].insert(c);

        seen[c].insert(b);
        seen[c].insert(a);
    }

    set<int> allNums = { 1,2,3,4,5,6,7,8,9,10,11,12 };

    set<int> first;
    set<int> second;
    set<int> third;

    srand(time(NULL));

    for (int i = 1; i < 13; i++)
    {


        set<int> possible;
        set_difference(all(allNums), all(seen[i]), inserter(possible, possible.begin()));



        if (setcontains(first, i))
        {

            set_intersection(all(first), all(possible), inserter(first, first.begin()));

            continue;
        }

        if (setcontains(second, i))
        {

            set_intersection(all(second), all(possible), inserter(second, second.begin()));

            continue;
        }

        if (setcontains(third, i))
        {

            set_intersection(all(third), all(possible), inserter(third, third.begin()));

            continue;
        }


        if (first.size() == 0)
        {
            first = possible;
            continue;
        }
        if (second.size() == 0)
        {
            second = possible;
            continue;
        }
        if (third.size() == 0)
        {
            third = possible;
            continue;
        }
    }


    vector<set<int>> sets = { first, second, third };
    set<set<int>> ans;
    vector<int> indexes = { 0,1,2 };

    do
    {
        vector<set<int>> cand = trysol(seen, sets, indexes);
        if (cand.size())
        {
            set<int> c(allNums);
            set<int> c2;
            set_difference(all(c), all(cand[0]), inserter(c2, c2.begin()));
            c = c2;
            c2 = set<int>();
            set_difference(all(c), all(cand[1]), inserter(c2, c2.begin()));
            c = c2;
            c2 = set<int>();
            set_difference(all(c), all(cand[2]), inserter(c2, c2.begin()));
            c = c2;
            c2 = set<int>();
            if (c.size() == 0)
            {
                rep(i, 3)
                {
                    repe(f, cand[i])
                    {
                        repe(s, seen[f])
                        {
                            if (setcontains(cand[i], s))
                            {
                                goto endofloop;
                            }
                        }
                    }
                }

                repe(sett, cand)
                {
                    ans.insert(sett);
                }
                break;
            }
        }
    endofloop:;
    } while (true);

    repe(sett, ans)
    {
        repe(member, sett)
        {
            cout << member << " ";
        }
        cout << "\n";
    }

    return 0;
}