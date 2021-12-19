#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define enablell 1

#define ll long long
#if enablell
#define int ll
#endif
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vp3 vector<p3>
#if enablell
#define inf 1e18
#else
#define inf int(1e9)
#endif

#define read(a) cin >> a
#define write(a) cout << (a) << "\n"
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define noop cout << "";
#define deb __debugbreak();
#else
#define noop ;
#define deb ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high; i >= 0; i--)
#define perr(i, low, high) for (int i = high; i >= low; i--)

#define readpush(type,vect) type temp; read(temp); vect.(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define insideinterval(v, interval) (v >= interval.first && v <= interval.second)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

template <typename T, typename U>
void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r)
{
    l = { l.first + r.first,l.second + r.second };
}

template <typename Out>
void split(const std::string& s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

inline int sToi(string& time)
{
    vector<string> sp = split(time, ':');

    int t = 0;

    t += stoi(sp[0]) * 3600;
    t += stoi(sp[1]) * 60;
    t += stoi(sp[2]);

    return t;
}

inline string iTos(int time)
{
    string ret = "";
    int h = time / 3600;

    time -= h * 3600;

    if (h < 10)
    {
        ret += "0" + to_string(h) + ":";
    }
    else
    {
        ret += to_string(h) + ":";
    }

    int m = time / 60;
    time -= m * 60;
    if (m < 10)
    {
        ret += "0" + to_string(m) + ":";
    }
    else
    {
        ret += to_string(m) + ":";
    }

    if (time < 10)
    {
        ret += "0" + to_string(time);
    }
    else
    {
        ret += to_string(time);
    }

    return ret;
}

int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    dread2(int, n, m);

    readvector(int, arrivals, n);
    vi timeTable(m);

    rep(i, m)
    {
        dread(string, time);
        timeTable[i] = sToi(time);
    }

    const int oneDay = 24 * 3600;

    vi firstRound;
    firstRound.reserve(oneDay);
    bool first = true;
    int j = 0;
    rep(i, n)
    {
        if (arrivals[i] < oneDay)
        {
            firstRound.emplace_back(arrivals[i]);
        }
        else
        {
            if (firstRound.empty())
            {
                cout << "fel";
                quit;
            }
            if (arrivals[i] % oneDay == firstRound[j])
            {
                j++;
                j = j % firstRound.size();
            }
            else
            {
                cout << "fel";
                quit;
            }
        }
    }


    vi ans;
    ans.reserve(m);




    rep(i, m)
    {
        int startT = timeTable[i] - arrivals[0];
        if (startT < 0)
        {
            startT = oneDay + startT;

            if (i == 0 && startT <= timeTable[m - 1])
            {
                continue;
            }
        }
        if (i > 0 && startT <= timeTable[i-1])
        {
            continue;
        }
        bool works = true;
        int k = i;

        repp(j, 0, firstRound.size())
        {
            if ((startT + firstRound[j]) % oneDay == timeTable[k])
            {
                k++;
                k = k % timeTable.size();
            }
            else
            {
                works = false;
                break;
            }
        }


        if (works)
        {
            ans.emplace_back(startT);
        }
    }


    sort(all(ans));
    if (ans.size())
    {
        repe(t, ans)
        {
            cout << iTos(t) << " ";
        }
    }
    else
    {
        cout << "fel";
    }


    quit;
}
