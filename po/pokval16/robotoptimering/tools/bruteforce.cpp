#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
//#include <bits/extc++.h>

using namespace std;

#define enablell 0

#define ll long long
#if enablell
#define int ll
#define inf LLONG_MAX
#define float double
#else
#define inf int(2e9)
#endif
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define p2 pair<int, int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vvvp2 vector<vvp2>
#define p3 tuple<int,int,int>
#define vp3 vector<p3>
#define vvp3 vector<vp3>
#define vvvp3 vector<vvp3>
#define p4 tuple<int,int,int,int>
#define vp4 vector<p4>

#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define read3(a,b,c) cin >> a >> b >> c
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
#define debif(expr) if(expr) deb;
#define debassert(expr) if(!(expr)) deb;
#else
#define noop ;
#define deb ;
#define debif(expr) ;
#define debassert(expr) ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define first(a) (*begin(a))
#define indexpair(p, i) ((i==0)?p.first:p.second)
#define chmax(a,b) ((a)=max((a),b))
#define chmin(a,b) ((a)=min((a),b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
inline p2 operator+(const p2& l, const p2& r) { return mp(l.first + r.first, l.second + r.second); }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s); string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }
inline int readintsigned() { int v = 0; int sign = 1; char c = getchar(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v * sign; }
inline int readint() { int v = 0; char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } return v; }
inline string readstring() { string s; char c; while ((c = getchar()) != EOF && c != '\n') { s.push_back(c); } return s; }
#if 1
random_device rd;
mt19937 rng(rd());
#endif


enum instructionType
{
    gotO,
    gotoblocked,
    forw,
    le,
    ri,
    loop,
    endloop,
    call,
    ret,
    label
};

struct instruction
{
    int target;
    instructionType what;
    string name;
    int loopcounter = -inf;
    
    instruction(instructionType what) : what(what), target(-10), name("ligma") {}
    instruction(instructionType what, string targetlabel) : what(what), name(targetlabel) {}
    instruction(instructionType what, int target) : what(what), target(target) {}
};

typedef vector<string> Board;
Board maze;
p2 goal;
p2 startpos;
int startdir;
vector<instruction> program;
vector<instruction> bestprogram;

inline bool is_inside(p2 pos)
{
    return pos.second >= 0 && pos.second < maze.size() && pos.first >= 0 && pos.first < maze[0].size();
}

inline bool isempty(p2 pos)
{
    if (!is_inside(pos)) return false;
    return maze[pos.second][pos.first] == '.';
}

p2 simulate()
{
    p2 pos = startpos;
    int dir = startdir;
    // Find main
    int location = -1;
    rep(i, program.size())
    {
        auto inst = program[i];
        if (inst.what == label && inst.name == "main")
        {
            location = i;
            break;
        }
    }

    vi loopposses;
    rep(i, program.size()) if (program[i].what == loop) loopposses.push_back(i);

    stack<int> callstack;

    //                 Down  left    up       right
    vp2 directions = { {0,1},{-1, 0},{0,-1}, {1,0} };

    rep(i, int(1e5))
    {
        location++;
        if (location<0)
        {
            location = 0;
            deb;
        }
        if (location >= program.size()) return pos;
        instruction& in = program[location];

        if (pos == goal) return pos;

        //debif(i == 998);
        //debif(i == 5000);

        switch (in.what)
        {
        case gotO:
            repe(pos, loopposses) program[pos].loopcounter = -inf;
            location = in.target;
            break;
        case gotoblocked:
            if (!isempty(pos + directions[dir]))
            {
                repe(pos, loopposses) program[pos].loopcounter = -inf;
                location = in.target;
            }
            break;
        case instructionType::forw:
            if (isempty(pos+directions[dir])) pos += directions[dir];
            break;
        case instructionType::le:
            dir--;
            dir = (4+(dir % 4))%4;
            break;
        case instructionType::ri:
            dir++;
            dir = dir % 4;
            break;
        case loop:
            if (in.loopcounter == -inf) in.loopcounter = in.target;
            in.loopcounter--;
            if (in.loopcounter <= 0) in.loopcounter = -inf;
            break;
        case call:
            repe(pos, loopposses) program[pos].loopcounter = -inf;
            callstack.push(location);
            location = in.target;
            break;
        case ret:
            if (callstack.empty()) return pos;
            location = callstack.top();
            callstack.pop();
            break;
        case endloop:
            if (program[in.target].loopcounter != -inf) location = in.target-1;
            break;
        case label:
            break;
        default:
            break;
        }
    }

    return pos;
}

void buildprogram(vector<instruction>& program)
{
    int looplevel = 0;
    
    rep(i, program.size())
    {
        bool fixed = false;
        instruction& inst = program[i];
        if (inst.what == gotO || inst.what == gotoblocked || inst.what == call)
        {
            //debif(inst.what == call);
            rep(i, program.size())
            {
                instruction& in = program[i];
                if (in.what == label && in.name == inst.name)
                {
                    fixed = true;
                    inst.target = i;
                    break;
                }
            }
            debif(inst.target < 0);
        }
        else if (inst.what==endloop)
        {
            int level = 0;

            
            per(j, i)
            {
                if (program[j].what == endloop) level++;
                if (program[j].what == loop)
                {
                    if (level)
                    {
                        level--;
                    }
                    else
                    {
                        fixed = true;
                        inst.target = j;
                        break;
                    }
                }
            }
        }
        else
        {
            fixed = true;
        }
        if (!fixed)
        {
            cout << "";
        }
        debassert(fixed);
    }
}

void addi(instructionType what, string n="", int t=-1)
{
    if (n!="")
    {
        program.push_back(instruction(what, n));
    }
    else if (t!=-1)
    {
        program.push_back(instruction(what, t));
    }
    else
    {
        program.push_back(instruction(what));
    }
}

void addi(instructionType what, int t) { addi(what, string(), t); }

//gotO,
//label

//gotoblocked,
//forw,
//le,
//ri,
//loop,
//endloop,
//call,
//ret,

void generaterandomprogram()
{
    program = vector<instruction>();

    int costlen = 7;

    vector<instructionType> instructions = { gotoblocked, forw,le,ri,loop };// , call, ret


    vector<string> labels;
    labels.push_back("main");
    addi(label, "main");

    uniform_int_distribution<int> dist(0, instructions.size()-1);

    priority_queue<p2> loopendings;

    int cost = 0;
    int i = 0;
    while (cost<costlen)
    {
        if (dist(rng))
        {
            instructionType inst = instructions[dist(rng)];
            switch (inst)
            {
            case call:
            case gotoblocked:
                addi(inst, labels[rand() % labels.size()]);
                break;
            case forw:
            case le:
            case ri:
            case ret:
                addi(inst);
                break;
            case loop:
                addi(loop, rand() % 200);
                loopendings.emplace(i+(rand()%(costlen-cost)), program.size());
                break;
            default:
                break;
            }


            while (loopendings.size() && cost>loopendings.top().first)
            {
                p2 p = loopendings.top();
                loopendings.pop();
                addi(endloop);
            }
            cost++;
            if (loopendings.empty())
            {
                addi(label, "l" + to_string(i));
                labels.push_back("l" + to_string(i));
            }
            
        }
        else
        {
            addi(gotO, labels[rand() % labels.size()]);
        }
        i++;
    }

    while (loopendings.size())
    {
        p2 p = loopendings.top();
        loopendings.pop();
        addi(endloop);
    }

}

inline int calcscore(p2 pos)
{
    return abs(pos.first - goal.first) + abs(pos.second - goal.second);
}

inline int calcscore(int x, int y)
{
    return abs(x - goal.first) + abs(y - goal.second);
}

//gotO,
//gotoblocked,
//call,
//forw,
//le,
//ri,
//ret,

//label
//loop,
//endloop,

void printprogram()
{
    map<instructionType, string> name = { {call,"call"},{gotO,"goto"},{gotoblocked,"gotoblocked"},{forw,"forward"},{le,"left"},{ri,"right"},{ret,"return"}, {endloop,"}"} };
    
    int indentation = 0;

    rep(i, bestprogram.size())
    {
        instruction& inst = bestprogram[i];
        string n = setcontains(name, inst.what) ? name[inst.what] : "";
        string tabs = string(indentation, '\t');
        switch (bestprogram[i].what)
        {
        case call:
        case gotoblocked:
        case gotO:
            cout << tabs << n << " " << inst.name;
            break;
        case forw:
        case le:
        case ri:
        case ret:
            cout << tabs << n;
            break;
        case endloop:
            indentation--;
            tabs = string(indentation, '\t');
            cout << tabs << n;
            break;
        case loop:
            cout << tabs << "for " << to_string(inst.target) << " {";
            indentation++;
            break;
        case label:
            cout << tabs << inst.name << ":";
            break;
            
        default:
            break;
        }
        cout << "\n";
        if (i == 0) indentation++;
    }
}

// trim from start (in place)
static inline void ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
        }));
}

// trim from end (in place)
static inline void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
        }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}

void parseprogram()
{
//const char* p = R"V0G0N(
//main:
//    for 98 {
//        right
//        for 154 {
//            gotoblocked main
//            forward
//            left
//        }
//    }
//)V0G0N";

const char* p = R"V0G0N(
main:
    for 100 {
            right
            for 125 {
                    gotoblocked main
                    forward
                    left
            }
    }
    forward
)V0G0N";
    string s(p);

    program = vector<instruction>();
    


    vector<string> tokens = split(s, '\n');

    //forw,
    //label
    //ri,
    //le,
    //ret,
    //endloop,

    //gotO,
    //gotoblocked,
    //call,

    //loop,
    map<string, instructionType> simpleinst;
    simpleinst["forward"] = forw;
    simpleinst["right"] = ri;
    simpleinst["left"] = le;
    simpleinst["ret"] = ret;
    simpleinst["}"] = endloop;


    repe(token, tokens)
    {
        trim(token);
        if (token == "") continue;

        // label
        if (token.find(':') != string::npos)
        {
            string labelname = token.substr(0, token.find(':'));
            addi(label, labelname);
        }
        else if (token.find("gotoblocked") != string::npos)
        {
            string name = token.substr(string("gotoblocked ").size());
            addi(gotoblocked, name);
        }
        else if (token.find("goto") != string::npos)
        {
            string name = token.substr(string("goto ").size());
            addi(gotO, name);
        }
        else if (token.find("call") != string::npos)
        {
            string name = token.substr(string("call ").size());
            addi(call, name);
        }
        else if (token.find("for ") != string::npos)
        {
            string name = token.substr(string("for ").size());
            while (name.back() < '0' || name.back() > '9') name.pop_back();
            addi(loop, stoi(name));
        }
        else
        {
            bool found = false;
            repe(inst, simpleinst)
            {
                if (token.find(inst.first) != string::npos)
                {
                    found = true;
                    addi(inst.second);
                    break;
                }
            }
            debassert(found);
        }
    }

    buildprogram(program);


}

int32_t main()
{
    fast();

#if 1
    //ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
    ifstream cin("C:\\Users\\Matis\\downloads\\robot\\robot_ew_manuell.in");
#endif

    dread(string, _);
    dread2(int, rows, cols);

    maze = Board(rows);
    rep(i, rows) read(maze[i]);

    map<char, int> dirtoindex;
    dirtoindex['v'] = 0;
    dirtoindex['<'] = 1;
    dirtoindex['^'] = 2;
    dirtoindex['>'] = 3;

    rep(i, rows) rep(j, cols)
    {
        if (setcontains(dirtoindex, maze[i][j]))
        {
            startdir = dirtoindex[maze[i][j]];
            startpos = { j,i };
        }

        if (maze[i][j] == 'M') goal = { j,i };

        if (maze[i][j] != '#') maze[i][j] = '.';
    }

    
    /*addi(label, "main");
    addi(loop, 2000);
    addi(forw);
    addi(endloop);
    addi(le);
    addi(gotO, "main");*/

    /*addi(label, "t");
    addi(ri);
    addi(gotoblocked, "t");
    addi(gotO, "midtwo");
    addi(label, "main");
    addi(le);
    addi(gotoblocked, "t");
    addi(label, "midtwo");
    addi(forw);
    addi(gotO, "main");

    buildprogram(program);

    rep(i, 2000)
    {
        simulate(startpos, startdir, program);
    }
    
    
    
    
    */
    
    parseprogram();
    
    p2 ending = simulate();
    int newscore = calcscore(ending);
    
    
    //vi loopposses;
    //rep(i, program.size()) if (program[i].what == loop) loopposses.push_back(i);



    //int score = calcscore(0,0)+inf;
    //rep(i, 1000)
    //{
    //    rep(j, 1000)
    //    {
    //        if (i == 98 && j == 154)
    //        {
    //            cout << "logma";
    //        }
    //        program[loopposses[0]].target = i;
    //        program[loopposses[1]].target = j;
    //        /*program[loopposses[1]].loopcounter = -inf;
    //        program[loopposses[1]].target = -inf;*/

    //        p2 p = simulate();
    //        int newscore = calcscore(p);
    //        if (newscore < score)
    //        {
    //            bestprogram = program;
    //            score = newscore;
    //            write(score);
    //            /*if (score==318)
    //            {
    //                printprogram();
    //            }*/
    //        }
    //    }
    //}

    int score = inf;
    while (true)
    {
        generaterandomprogram();
        buildprogram(program);
        p2 p = simulate();
        int newscore = calcscore(p);
        
        if (newscore<score)
        {
            bestprogram = program;
            score = newscore;
            cout << p.first << " " << p.second << "\n";
            if (p.first>47)
            {
                printprogram();
            }
        }

    }



    cout << "ligmab";

    quit;
}
