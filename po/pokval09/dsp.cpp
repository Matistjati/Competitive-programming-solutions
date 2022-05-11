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


using namespace std;

#define p2 pair<int, int>
#define ll long long
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

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

    vector<int> registers(256);

    int n;
    read(n);
    vector<pair<string, pair<int, int>>> commands;
    rep(i, n)
    {
        string command;
        read(command);
        if (command == "INPUT" || command == "OUTPUT")
        {
            int nRegister;
            read(nRegister);
            commands.push_back({ command,{nRegister,-inf} });
        }
        else if (command == "HALT")
        {
            commands.push_back({ command,{-inf,-inf} });
        }
        else
        {
            int a;
            int b;
            read(a);
            read(b);
            commands.push_back({ command,{a,b} });
        }
    }

    rep(i, commands.size())
    {
        auto command = commands[i];

        if (command.first == "INPUT")
        {
            read(registers[command.second.first]);
        }
        else if (command.first == "OUTPUT")
        {
            write(registers[command.second.first]);
        }
        else if (command.first == "HALT")
        {
            break;
        }
        else if (command.first == "JNZ")
        {
            if (registers[command.second.first])
            {
                i = command.second.second - 1;
            }
        }
        else if (command.first == "ADD")
        {
            registers[command.second.second] += registers[command.second.first];
        }
        else if (command.first == "SUB")
        {
            registers[command.second.second] -= registers[command.second.first];
        }
        else if (command.first == "CONST")
        {
            registers[command.second.second] = command.second.first;
        }
    }

    return 0;
}