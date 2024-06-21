#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif



struct Participant {
    string name;
    int laps;
    int finishTime;
};

int timeToSeconds(const string& time) {
    int hh, mm, ss;
    string period;
    hh = stoi(time.substr(0, 2));
    mm = stoi(time.substr(3, 2));
    ss = stoi(time.substr(6, 2));
    period = time.substr(9, 2);
    if (period == "PM" && hh != 12) hh += 12;
    if (period == "AM" && hh == 12) hh = 0;
    return hh * 3600 + mm * 60 + ss;
}

string secondsToTime(int seconds) {
    int hh = (seconds / 3600) % 24;
    int mm = (seconds % 3600) / 60;
    int ss = seconds % 60;
    string period = (hh >= 12) ? "PM" : "AM";
    if (hh > 12) hh -= 12;
    if (hh == 0) hh = 12;
    stringstream ssTime;
    ssTime << setw(2) << setfill('0') << hh << ":"
        << setw(2) << setfill('0') << mm << ":"
        << setw(2) << setfill('0') << ss << " " << period;
    return ssTime.str();
}

int timedist(int a, int b)
{
    if (b > a)
    {
        return b - a;
    }
    return 86400 - a + b;
}

signed main()
{
    fast();
    string startTime;
    getline(cin, startTime);
    int startTimeSec = timeToSeconds(startTime);

    int n;
    cin >> n;
    cin.ignore();

    map<string, vector<string>> participantLaps;

    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        size_t pos = 11;
        string timestamp = line.substr(0, pos);
        string name = line.substr(pos + 1);
        participantLaps[name].push_back(timestamp);
    }

    vector<Participant> results;

    for (const auto& entry : participantLaps) {
        const string& name = entry.first;
        const vector<string>& laps = entry.second;

        int lapsCount = 0;
        int finishTime = -1;
        bool finished = false;
        for (const string& lap : laps) {
            int lapTimeSec = timeToSeconds(lap);
            if (timedist(startTimeSec, lapTimeSec) < 3 * 3600) {
                lapsCount++;
            }
            else {
                finishTime = lapTimeSec;
                lapsCount++;
                break;
            }
        }
        if (finishTime != -1 && lapsCount > 0) {
            results.push_back({ name, lapsCount, finishTime });
        }
    }

    sort(results.begin(), results.end(), [](const Participant& a, const Participant& b) {
        if (a.laps != b.laps) return a.laps > b.laps;
    return a.finishTime < b.finishTime;
        });

    for (const auto& participant : results) {
        cout << participant.laps << " " << participant.name << endl;
    }


    return 0;
}
