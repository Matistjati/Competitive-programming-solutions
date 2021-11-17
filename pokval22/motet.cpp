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
    cin.tie(NULL); cout.tie(NULL);
}


int main()
{
    fast();

    int n;
    read(n);

    vector<p3> intervals;

    rep(i, n)
    {
        dread(int, m);

        vp2 person;

        rep(i, m)
        {
            p2 start;
            cin >> start.first;
            cin >> start.second;
            person.push_back(start);
        }
        
        vp3 realPerson;

        sort(all(person));

        p2 curr = person[0];
        
        for (int j = 1; j < person.size(); j++)
        {
            p2 nextp = person[j];
            if (nextp.first - curr.second < 2)
            {
                curr.second = max(curr.second, nextp.second);
            }
            else
            {
                intervals.push_back({ curr.first,curr.second,i });
                curr = person[j];
            }
        }
        p3 last = { curr.first,curr.second,i };
        if (intervals.empty() || intervals[intervals.size()-1] != last)
        {
            intervals.push_back(last);
        }
    }

    sort(all(intervals));

    

    ll most = -linf;

    priority_queue<p2> activeIntervals;

    map<int, pair<bool, set<int>>> okPeople;

    ll active = 0;

    for (int i = 0; i < intervals.size(); i++)
    {
        p3 curr = intervals[i];

        while (activeIntervals.size() && curr[0] > -activeIntervals.top().first)
        {
            p2 inter = activeIntervals.top();
            activeIntervals.pop();

            okPeople[inter.second].second.erase(-inter.first);
            if (okPeople[inter.second].second.empty() && okPeople[inter.second].first)
            {
                active--;
                okPeople[inter.second].first = false;
            }
        }

        activeIntervals.push({ -curr[1],curr[2] });
        if (!setcontains(okPeople,curr[2]))
        {
            okPeople[curr[2]] = { false, {} };
        }
        okPeople[curr[2]].second.insert(curr[1]);
        if (!okPeople[curr[2]].first)
        {
            active++;
            okPeople[curr[2]].first = true;
        }
        

        most = max(most, active);
    }


    write(most);

    return 0;
}