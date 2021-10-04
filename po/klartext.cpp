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

#define ll long long
#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define repp(i, high) for (ll i = high; i >= 0; i--)
#define inf 1e9

void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}


int main()
{
    fast();

    int type;
    read(type);
    if (type == 1)
    {
        string cipher;
        read(cipher);

        int hyphen = cipher.find("-");
        int offset = stoi(cipher.substr(0, hyphen));
        cipher = cipher.substr(hyphen+1, cipher.size() - hyphen);


        repe(letter, cipher)
        {
            int newLetter = (letter + offset);
            if (newLetter > 'z')
            {
                newLetter = char((newLetter)-'z' + 'a' - 1);
            }
            cout << char(newLetter);
        }

    }
    else if (type == 4)
    {
        string cipher;
        read(cipher);
        reverse(cipher.begin(), cipher.end());
        write(cipher);
    }

    return 0;
}