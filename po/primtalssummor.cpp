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
#define p2 pair<ll, ll>
#define p3 tuple<ll, ll, ll>
#define vi vector<ll>
#define inf 1e9

#define read(a) cin >> a
#define write(a) cout << (a) << endl

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

    vector<int> primes = {
    101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
    211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
    307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397,
    401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499,
    503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599,
    601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691,
    701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797,
    809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
    907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997 };

    vector<int> masks;
    vector<int> goodPrimes;
    rep(i, primes.size())
    {
        int v = primes[i];
        int mask = 0;
        set<int> digits;
        digits.insert(v % 10);
        mask |= (1 << (v % 10));
        v /= 10;
        digits.insert(v % 10);
        mask |= (1 << (v % 10));
        v /= 10;
        digits.insert(v % 10);
        mask |= (1 << (v % 10));
        if (setcontains(digits, 0))
        {
            continue;
        }
        if (digits.size() == 3)
        {
            masks.push_back(mask);
            goodPrimes.push_back(primes[i]);
        }
    }

    int complete = 0;
    for (int i = 1; i <= 9; i++)
    {
        complete |= (1 << i);
    }

    int n = 0;
    int mi = inf;
    int ma = -inf;
    set<set<string>> seen;
    rep(i, goodPrimes.size())
    {
        rep(j, goodPrimes.size())
        {
            rep(k, goodPrimes.size())
            {
                set<char> letters;
                string a = to_string(goodPrimes[i]);
                string b = to_string(goodPrimes[j]);
                string c = to_string(goodPrimes[k]);
                rep(l, 3)
                {
                    letters.insert(a[l]);
                    letters.insert(b[l]);
                    letters.insert(c[l]);
                }

                if (letters.size() != 9)
                {
                    continue;
                }

                set<string> combination = { a,b,c };
                if (setcontains(seen, combination))
                {
                    continue;
                }
                int s = goodPrimes[i] + goodPrimes[j] + goodPrimes[k];

                //cout << goodPrimes[i] << " " << goodPrimes[j] << " " << goodPrimes[k] << "\n";
                seen.insert(combination);
                n++;
                mi = min(mi, s);
                ma = max(ma, s);
            }
        }
    }

    cout << n << " " << mi << " " << ma;

    return 0;
}