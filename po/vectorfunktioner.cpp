#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <string>
#include <iterator>
#include <queue>
#include <tuple>
#include <numeric>

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << a << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define notsetcontains(set, x) set.find(x) == set.end()

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto const& i : container)
#define inf 1e9

// Vänd på en vektor.
// Notera att den skickas som referens,
// så du ska vända samma vektor som skickas in.
void reverse(vector<int> & vec) {
    reverse(vec.begin(), vec.end());
}

// Välj ut vartannat element ur en vektor (första, tredje, osv)
// och returnera en ny vektor med svaret.
// Du får inte modifiera vektorn, trots att den skickas som referens.
// Därför används "const" framför parametern.
vector<int> vartannat(const vector<int> & vec) {
    vector<int> odds;
    for (int i = 0; i < vec.size(); i += 2)
    {
        odds.push_back(vec[i]);
    }

    return odds;
}

// Returnera det minsta värdet i en vektor.
int minsta(const vector<int> & vec) {
    return *std::min_element(vec.begin(), vec.end());
}

// Returnera summan av elementen i en vektor.
int summa(const vector<int> & sum) {
    return std::accumulate(sum.begin(), sum.end(), 0);
}

// Räkna antalet udda heltal, som dessutom befinner
// sig på udda index (räknat noll-indexerat!)
int veryOdd(const vector<int> & suchVector) {
    int n_odd = 0;
    for (int i = 1; i < suchVector.size(); i += 2)
    {
        if (suchVector[i]%2==1)
        {
            n_odd++;
        }
    }
    return n_odd;
}
