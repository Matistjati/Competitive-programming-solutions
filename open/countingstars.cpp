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
#define deb __debugbreak();

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)


inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

int main()
{
    fast();

    int i = 0;
    string caseN;
    vector<p2> direct = { {1,0},{-1,0},{0,1},{0,-1} };
    while (getline(cin, caseN))
    {
        if (caseN == "")
        {
            getline(cin, caseN);
            if (caseN == "")
            {
                return 0;
            }
        }
        i++;
        int n_stars = 0;
        
        int space = caseN.find(' ');
        int r = stoi(caseN.substr(0, space));
        int c = stoi(caseN.substr(space + 1, caseN.size() - space - 1));

        vector<string> board;
        rep(i, r)
        {
            readpush(string, board);
        }


        rep(i, r)
        {
            rep(j, c)
            {
                if (board[i][j] == '-')
                {
                    n_stars++;
                    set<p2> visited;
                    queue<p2> toVisit;
                    toVisit.push({ i,j });

                    while (toVisit.size())
                    {
                        p2 curr = toVisit.front();
                        toVisit.pop();

                        if (board[curr.first][curr.second] == '-')
                        {
                            board[curr.first][curr.second] = 'O';
                        }

                        repe(dir, direct)
                        {
                            p2 n = curr;
                            n.first += dir.first;
                            n.second += dir.second;

                            if (n.first < 0 || n.first >= r || n.second < 0 || n.second >= c || board[n.first][n.second]=='#')
                            {
                                continue;
                            }

                            if (setcontains(visited,n))
                            {
                                continue;
                            }

                            visited.insert(n);
                            toVisit.push(n);

                        }
                    }

                }
            }
        }


        cout << "Case " << i << ": " << (n_stars) << "\n";
        
    }



    return 0;
}
