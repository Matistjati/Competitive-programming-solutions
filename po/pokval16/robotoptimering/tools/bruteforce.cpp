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

// lower inclusive, upper exclusive
inline int randint(int low, int high) { return uniform_int_distribution<int>(low, high-1)(rng); }
inline int randint(int high) { return randint(0,high); }
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
    label,
    noope,
    eof
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

const int maxloop = 100;

int t = -1;


inline bool is_inside(p2 pos)
{
    return pos.second >= 0 && pos.second < maze.size() && pos.first >= 0 && pos.first < maze[0].size();
}

inline bool isempty(p2 pos)
{
    if (!is_inside(pos)) return false;
    return maze[pos.second][pos.first] != '#';
}

#define VIS 0
#define bset 0
#define closestD 1


int score = inf;

#if VIS
#define iterC int(1e8)
#else
#define iterC int(1e5)
#endif

p2 simulate()
{
#if VIS
    Board mazec(maze);
    ofstream cout("C:\\Users\\Matis\\Source\\repos\\Comp prog\\x64\\release\\out.txt");
#endif

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

    p2 closest = p2(0, 0);
    int d = inf;

    int distlimit = t == 3 ? 10 : 20;

    int node = 0;

    vi whichnode(program.size());
    vi parent;
    parent.push_back(-1);
    map<int, int> nodetoloop;

    rep(i, program.size())
    {
        instruction& inst = program[i];
        if (inst.what == loop)
        {
            parent.push_back(node);
            node = parent.size()-1;
            nodetoloop[node] = i;
        }
        if (inst.what == endloop)
        {
            node = parent[node];
        }

        whichnode[i] = node;
    }

    const int progsize = program.size();
    rep(i, iterC)
    {
        if (i == int(3e3) && abs(pos.first-startpos.first)+abs(pos.second- startpos.second)<t) goto end;
        if (i == int(1e4) && abs(pos.first-startpos.first)+abs(pos.second- startpos.second)<t) goto end;
        location++;
        instruction& in = program[location];



#if closestD
        if (abs(goal.first-pos.first)+abs(goal.second-pos.second)<d)
        {
            d = abs(goal.first - pos.first) + abs(goal.second - pos.second);
            closest = pos;
        }
#endif

        if (pos == goal) goto end;

#if VIS
        mazec[pos.second][pos.first] = 'O';
#endif

        //debif(i == 998);
        //debif(i == 5000);

        switch (in.what)
        {
        case gotO:
            node = whichnode[location];
            while (node != whichnode[in.target])
            {
                program[nodetoloop[node]].loopcounter = -inf;
                node = parent[node];
            }
            location = in.target;
            break;
        case gotoblocked:
            if (!isempty(pos + directions[dir]))
            {
                node = whichnode[location];
                while (node != whichnode[in.target])
                {
                    program[nodetoloop[node]].loopcounter = -inf;
                    node = parent[node];
                }
                location = in.target;
            }
            break;
        case call:
            node = whichnode[location];
            while (node != whichnode[in.target])
            {
                program[nodetoloop[node]].loopcounter = -inf;
                node = parent[node];
            }
            callstack.push(location);
            location = in.target;
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
            // Enter
            if (in.loopcounter == -inf)
            {
                in.loopcounter = in.target;
            }
            in.loopcounter--;
            // Exit, endloop takes care of the rest
            if (in.loopcounter <= 0) in.loopcounter = -inf;
            break;
        case ret:
            if (callstack.empty()) return pos;
            location = callstack.top();
            callstack.pop();
            break;
        case endloop:
            if (program[in.target].loopcounter > 0) location = in.target-1;
            break;
        case label:
            break;
        case eof:
            goto end;
        default:
            break;
        }
    }

    end:
#if VIS
    rep(i, mazec.size())
    {
        cout << mazec[i] << "\n";
    }
    cout << "sdfnj";
#endif

#if closestD
    return closest;
#endif


    return pos;
}


inline int calcscore(p2 pos)
{
    return abs(pos.first - goal.first) + abs(pos.second - goal.second);
}

inline int calcscore(int x, int y)
{
    return abs(x - goal.first) + abs(y - goal.second);
}


inline int calcscore_slow(vector<instruction>& program, int extra = -1, bool random = true)
{
    if (extra != -1) random = false;
    vi loopposses;
    rep(i, program.size()) if (program[i].what == loop) loopposses.push_back(i);
    if (loopposses.size() == 0) return inf;


    while (loopposses.size() > 2) loopposses.pop_back();

    int ret = inf;

    //           0   1   2    3    4    5    6  7
    vi highs = { 150,75, 150, 70,  10,   5, 150, 50 };
    int high = highs[t];

    if (extra != -1) high = extra;

    vi best(2);


    rep(i, high)
    {
        rep(j, high)
        {

            if (random) program[loopposses[0]].target = randint(maxloop);
            else program[loopposses[0]].target = i;

            program[loopposses[0]].loopcounter = -inf;
            if (loopposses.size() == 2)
            {
                if (random) program[loopposses[1]].target = randint(maxloop);
                else program[loopposses[1]].target = j;

                program[loopposses[1]].loopcounter = -inf;
            }
            p2 p = simulate();
            int newscore = calcscore(p);
            if (newscore < ret)
            {
                ret = newscore;
                best[0] = i;
                best[1] = j;
            }
            if (loopposses.size() == 1)
            {
                break;
            }
        }
    }
    program[loopposses[0]].target = best[0];
    if (loopposses.size() == 2)
    {
        program[loopposses[1]].target = best[1];
    }
    return ret;
}

int getprogramlen(vector<instruction>& program)
{
    int ans = 0;

    rep(i, program.size())
    {
        instructionType& t = program[i].what;

        switch (t)
        {
        case forw:
        case le:
        case ri:
        case loop:
        case gotoblocked:
        case call:
        case ret:
            ans++;
        default:
            break;
        }

    }

    return ans;
}


void printprogram()
{
    map<instructionType, string> name = { {call,"call"},{gotO,"goto"},{gotoblocked,"gotoblocked"},{forw,"forward"},{le,"left"},{ri,"right"},{ret,"return"}, {endloop,"}"} };

    int indentation = 0;

    set<int> usedlabels;
    usedlabels.insert(0);
    rep(i, bestprogram.size()) if (bestprogram[i].what == call || bestprogram[i].what == gotO || bestprogram[i].what == gotoblocked) usedlabels.insert(bestprogram[i].target);



    rep(i, bestprogram.size())
    {
        bool hascontent = true;
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
            if (setcontains(usedlabels, i) || inst.name=="main") cout << tabs << inst.name << ":";
            else hascontent = false;
            break;

        default:
            break;
        }
        if (hascontent) cout << "\n";
        if (i == 0) indentation++;
    }
}



void buildprogram(vector<instruction>& program)
{
    vi looplevels(program.size());
    int looplevel = 0;


    int node = 0;

    vi nodes(program.size());
    vector<vector<string>> nodelabels;
    nodelabels.push_back({});
    vi parent;
    parent.push_back(-1);

    rep(i, program.size())
    {
        instruction& inst = program[i];
        looplevels[i] = looplevel;
        if (inst.what == loop)
        {
            parent.push_back(node);
            node=nodelabels.size();
            nodelabels.push_back({});
            looplevel++;
        }
        if (inst.what == endloop)
        {
            node = parent[node];
            looplevel--;
        }

        nodes[i] = node;

        if (inst.what == label) nodelabels[node].emplace_back(inst.name);
    }

    rep(i, program.size())
    {
        instruction& inst = program[i];
        if ((inst.what == gotO || inst.what == gotoblocked || inst.what == call) && inst.name == "ligma")
        {
            vector<string> labels;
            int node = nodes[i];

            while (node!=-1)
            {
                labels.insert(labels.end(), all(nodelabels[node]));
                node = parent[node];
            }

            inst.name = labels[randint(labels.size())];
        }
    }

    /*
    repe(jump, jumps)
    {
        if (inst.what == gotO || inst.what == gotoblocked || inst.what == call) jumps.push_back(i);
        if (program[jump].name=="ligma")
        {
            while (true)
            {
                int k = randint(jump);
                if (program[k].what==label&&looplevels[k]<=looplevels[jump])
                {
                    program[jump].name = program[k].name;
                    break;
                }

            }

        }

    }*/

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

    rep(i, program.size()-1)
    {
        if (program[i].what==loop&&program[i+1].what==endloop)
        {
            program.erase(program.begin()+i);
            program.erase(program.begin()+i);
            i = 0;
        }
    }
    program.push_back(instruction(eof));
}

void addi(instructionType what, string n="", int t=-1)
{
    if (what == noope) return;

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

void generaterandomprogram()
{
    program = vector<instruction>();

    int costlen = 8 +randint(0, 5);

    vector<instructionType> instructions = { gotoblocked, forw,le,ri,loop };//  , call, ret



    addi(label, "main");
    //addi(ri);
    //addi(gotoblocked, "main");

    uniform_int_distribution<int> dist(0, instructions.size()-1);

    priority_queue<p2> loopendings;

    int cost = 0;
    int i = 0;
    int maxloopnesting = 2;
    int looplevel = 0;
    uniform_int_distribution<int> usegoto(0, 5);
    while (cost<costlen)
    {
        if (usegoto(rng))
        {
            instructionType inst = instructions[dist(rng)];
            switch (inst)
            {
            case call:
            case gotoblocked:
                addi(inst);
                break;
            case forw:
            case le:
            case ri:
            case ret:
                addi(inst);
                break;
            case loop:
                if (looplevel + 1 > maxloopnesting) continue;
                addi(loop, randint(maxloop));
                looplevel++;
                loopendings.emplace(i+randint(costlen - cost), program.size());
                break;
            default:
                break;
            }


            while (loopendings.size() && cost>loopendings.top().first)
            {
                p2 p = loopendings.top();
                loopendings.pop();
                addi(label, "l" + to_string(i));
                i++;
                looplevel--;
                addi(endloop);
            }
            cost++;

            addi(label, "l" + to_string(i));
            i++;
        }
        else
        {
            addi(gotO);
        }
    }

    while (loopendings.size())
    {
        p2 p = loopendings.top();
        loopendings.pop();
        addi(endloop);
    }
    addi(gotO, "main");

    /*int looplevel = 0;
    vi looplevels(program.size());


    rep(i, program.size())
    {
        instruction& inst = program[i];
        looplevels[i] = looplevel;
        if (inst.what == loop) looplevel++;
        if (inst.what == endloop) looplevel--;
    }

    while (true)
    {
        int loc = randint(program.size());
        if (looplevels[loc]==0)
        {
            program.insert(program.begin() + loc, instruction(label, "main"));
            break;
        }
    }*/

}

void genstupid()
{
    program = vector<instruction>();

    vector<instructionType> instructions = { forw,le,ri, noope};


    addi(label, "main");
    addi(instructions[randint(instructions.size())]);
    addi(instructions[randint(instructions.size())]);
    addi(loop, randint(101));
    addi(label, "s");
    addi(instructions[randint(instructions.size())]);
    addi(instructions[randint(instructions.size())]);
    addi(loop, randint(101));

    rep(i, 6) addi(instructions[randint(instructions.size())]);


    addi(endloop);
    addi(instructions[randint(instructions.size())]);
    addi(endloop);
    addi(instructions[randint(instructions.size())]);
    addi(gotO, "main");
}

vi perm = {0,0,0,1,2};
set<vi> visited;
vvi instrs;
int instrI = 0;
int highperm = 7;

void instrfill(int index, vi& values)
{
    if (index== highperm)
    {
        instrs.push_back(values);
        return;
    }
    rep(i, 4)
    {
        values[index] = i;
        instrfill(index + 1, values);
    }
}

vector<instructionType> instructions = { gotoblocked, forw,le,ri,loop, gotO };

void doalllen5(int costints, vector<string>& labels, vector<instruction>& instructs)
{
    if (costints==0)
    {
        vector<instruction> prog(instructs);
        prog.push_back(instruction(gotO, "main"));
        buildprogram(prog);

        p2 p = simulate();
        int newscore = calcscore(p);

        if (newscore < 700) newscore = calcscore_slow(prog);

        if (newscore < 400) newscore = calcscore_slow(prog, 100);


        if (newscore < score)
        {
            bestprogram = prog;
            score = newscore;


            cout << p.first << " " << p.second << " , dist: " << score << "\n";
            printprogram();
        }
        return;
    }
    rep(i, instructions.size())
    {
        instructionType& t = instructions[i];
        if (t==forw||t==ri||t==le)
        {
            instructs.push_back(instruction(t));
            labels.push_back(to_string(instructs.size()));
            doalllen5(costints - 1, labels, instructs);
            instructs.pop_back();
            labels.pop_back();

        }
        else if (t==loop)
        {
            rep(i, 3)
            {
                instructs.push_back(instruction(t, randint(150)));
                labels.push_back(to_string(instructs.size()));
                doalllen5(costints - 1, labels, instructs);
                instructs.pop_back();
                labels.pop_back();
            }
        }
        else if (t==gotoblocked||t==gotO)
        {
            if (instructs.back().what == gotO) continue;
            rep(i, min(3, int(labels.size())))
            {
                instructs.push_back(instruction(t, labels[i]));
                doalllen5(costints - (t==gotoblocked), labels, instructs);
                instructs.pop_back();
            }
        }
    }
}

void precomp()
{
    vi values(highperm);
    instrfill(0, values);
    return;
    vector<instruction> instructs;
    instructs.push_back(instruction(label, "main"));
    vector<string> labels;
    labels.push_back("main");
    doalllen5(5, labels, instructs);
    cout << "done";
}

void addic(instructionType t)
{
    if (t==call)
    {
        addi(t, "segs");
    }
    else
    {
        addi(t);
    }
}

void genstupidperm()
{

    program = vector<instruction>();

    vector<instructionType> instructions = { noope,forw,le,ri };

    addi(label, "main");

    instrI++;
    if (instrI == instrs.size())
    {
        cout << instrI;
        instrs = vvi();
        vi values(highperm);
        instrfill(0, values);
        instrI = 0;
    }
    int c = 0;
    repe(i, instrs[instrI]) c += (i != 0);
    if (c > 2) return;


    addi(instructions[instrs[instrI][0]]);
    addi(instructions[instrs[instrI][1]]);
    addi(loop, 1);
    addi(instructions[instrs[instrI][2]]);
    addi(label, "two");
    addi(instructions[instrs[instrI][3]]);
    addi(forw);
    addi(gotoblocked, "six");
    addi(gotO, "two");
    addi(label, "six");
    addi(ri);
    addi(gotoblocked, "six");
    addi(forw);
    addi(le);
    addi(instructions[instrs[instrI][4]]);
    addi(endloop);
    addi(instructions[instrs[instrI][5]]);
    addi(instructions[instrs[instrI][6]]);
    addi(gotO, "main");

    return;

    instrI++;
    int counts = 0;
    repe(i, instrs[instrI]) counts += (i != 0);

    addi(label, "segs");
    if (counts != 5) return;
    addi(instructions[instrs[instrI][0] % 4]);
    addi(instructions[instrs[instrI][1] % 4]);
    addi(instructions[instrs[instrI][2] % 4]);
    addi(ret);

    addi(label, "main");
    addi(instructions[instrs[instrI][3]]);
    addi(loop, randint(1000));
    addi(instructions[instrs[instrI][4]]);
    addi(loop, randint(1000));
    addi(instructions[instrs[instrI][4]]);
    addi(instructions[instrs[instrI][5]]);
    addi(endloop);
    addi(instructions[instrs[instrI][6]]);
    addi(endloop);
    addi(instructions[instrs[instrI][7]]);
    addi(gotO, "main");

    if (instrI % 100000 == 0) cout << instrI;

    if (instrI==instrs.size())
    {
        cout << instrI;
        instrs = vvi();
        vi values(highperm);
        instrfill(0, values);
        instrI = 0;
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
//        forward
//        right
//        forward
//        gotoblocked l11
//        l4:
//        for 32 {
//                forward
//                right
//                forward
//                left
//                forward
//        }
//        forward
//        l11:
//        left
//        gotoblocked l4
//        goto main
//)V0G0N";

//const char* p = R"V0G0N(
//main:
//    right
//    gotoblocked main
//
//    l1:
//    right
//    gotoblocked l1
//
//
//    forward
//    right
//    right
//    goto main
//)V0G0N";



const char* p = R"V0G0N(
main:
    for 12 {
            right
            for 40 {
                    forward
                    goto nine
                    five:
                    left
                    gotoblocked ten
                    forward
                    right
                    nine:
                    gotoblocked five
                    ten:
            }
    }
    right
    goto main
)V0G0N";

//const char* p = R"V0G0N(
//main:
//        left
//        for 12 {
//                forward
//                forward
//                for 17 {
//                        left
//                        forward
//                        left
//                        forward
//                        left
//                        left
//                }
//                forward
//        }
//        goto main
//)V0G0N";

//const char* p = R"V0G0N(
//main:
//    sadjgs:
//    for 10 {
//        segs:
//        for 20 {
//            amogussex:
//            amongsus:
//        }
//        binladen:
//        for 10 {
//            bogsax:
//        }
//        asjfdi:
//    }
//    socks:
//    feet:
//    goto main
//)V0G0N";

//const char* p = R"V0G0N(
//main:
//        gotoblocked l10
//        for 28 {
//                right
//                for 33 {
//                        left
//                        forward
//                        left
//                        right
//                        forward
//                        right
//                        forward
//                }
//        }
//        l10:
//        right
//        forward
//        goto main
//
//)V0G0N";

    string s(p);

    program = vector<instruction>();



    vector<string> tokens = split(s, '\n');

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
    //ifstream cin("C:\\Users\\Matis\\downloads\\robot\\robot_path_freedom2.in");
    ifstream cin("C:\\Users\\Matis\\documents\\robot\\maps\\robot_rand_80.in");
    //ifstream cin("C:\\Users\\Matis\\documents\\robot\\maps\\robot_rand_80.in");
    //ifstream cin("C:\\Users\\Matis\\documents\\robot\\maps\\robot_cross.in");
    //ifstream cin("C:\\Users\\Matis\\documents\\robot\\maps\\test2.in");
#endif



    srand(time(NULL));
    dread(string, _);
    if (_ == "robot_path_freedom2") t = 0;
    if (_ == "robot_ew_manuell") t = 1;
    if (_ == "robot_concentric") t = 2;
    if (_ == "robot_rand_60") t = 3;
    if (_ == "robot_rand_80") t = 4;
    if (_ == "test1") t = 5;
    if (_ == "test2") t = 6;
    if (_ == "robot_path_freedom2") t = 7;
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

        if (maze[i][j] != '#' && maze[i][j]!='M') maze[i][j] = '.';
    }


    precomp();

    parseprogram();


    p2 ending = simulate();
    int newscore = calcscore(ending);
#if VIS
    cout << newscore << " " << getprogramlen(program);
    return 0;
#endif
    if (ending.first>23983598)
    {
        printprogram();
    }

#if 0

#define J 0
    vi loopposses;
    rep(i, program.size()) if (program[i].what == loop) loopposses.push_back(i);

    int score = calcscore(0,0)+inf;
    rep(i, 100)
#if J
        rep(j, 100)
#endif
    {
        /*if (i == 98 && j == 154)
        {
            cout << "logma";
        }*/


        parseprogram();
#if J
        program[loopposses[1]].target = j;
        program[loopposses[1]].loopcounter = -inf;
#endif


        program[loopposses[0]].target = i;
        program[loopposses[0]].loopcounter = -inf;

        repe(p, loopposses) program[p].loopcounter = -inf;

        p2 p = simulate();
        int newscore = calcscore(p);
        if (newscore < score)
        {
            bestprogram = program;
            score = newscore;
            //cout << score;
            cout << "score: " << score << ", i: " << i;
#if J
            cout << ", j: " << j;
#endif
            cout << "\n";
            /*if (score==318)
            {
                printprogram();
            }*/
        }
    }
    cout << "done";
#endif

#if 1

    //               0    1   2    3    4    5   6   7
    vi scorereqs = { 175, 90, 100, 685, 800, 69, 100, 40};
    int scorereq = scorereqs[t];

    ll n_checked = 0;

    while (true)
    {
        generaterandomprogram();
        //else genstupid();
        //genstupidperm();

        buildprogram(program);

        p2 p = simulate();
        int newscore = calcscore(p);

        if (newscore < scorereq) newscore = calcscore_slow(program);
        //newscore = calcscore_slow(program, 100);
        if (newscore < 500) newscore = calcscore_slow(program, 100);


        if (newscore < score)
        {
            bestprogram = program;
            score = newscore;


            cout << p.first << " " << p.second << " , dist: " << score << ", len: " << getprogramlen(program) << "\n";
            printprogram();

            if (score==0)
            {
                cout << "checked: " << n_checked << "\n";
                score = 1;
            }
        }
        // Make sure n checked can be viewed during debugging
        if (score>inf) cout << n_checked;
        n_checked++;
    }
    cout << n_checked;
#endif

#if !VIS
    cout << "ligmab";
#endif

    quit;
}
