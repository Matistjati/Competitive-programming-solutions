#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

int main() {
    cin.tie(0)->sync_with_stdio(0);

    vector<int> registers(256);

    int n;
    cin >> n;
    vector<pair<string, pair<int, int>>> commands;
    rep(i, n) {
        string command;
        cin >> command;
        if (command == "INPUT" || command == "OUTPUT") {
            int nRegister;
            cin >> nRegister;
            commands.push_back({ command,{nRegister,-1} });
        }
        else if (command == "HALT") {
            commands.push_back({ command,{-1,-1} });
        }
        else {
            int a, b;
            cin >> a >> b;
            commands.push_back({ command,{a,b} });
        }
    }

    rep(i, sz(commands))
    {
        auto command = commands[i];

        if (command.first == "INPUT")
        {
            cin >> registers[command.second.first];
        }
        else if (command.first == "OUTPUT")
        {
            cout << registers[command.second.first] << '\n';
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
