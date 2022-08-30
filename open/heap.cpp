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

class Heap
{
public:
    int size = 0;
    vector<int> vec;
    int depth = 1;
    int deepest = 0;
    int capacity = pow(depth, 2) - 1;



    void insert(int element)
    {
        size++;

        if (size >= capacity)
        {
            depth++;
            capacity = pow(depth, 2) - 1;
            vec.resize(capacity, -inf);
        }

        int index = size-1;
        vec[index] = element;
        while (index >= 0)
        {
            if (vec[index] > vec[(index-1)/2])
            {
                swap(vec[index], vec[(index - 1) / 2]);
                index = (index - 1) / 2;
            }
            else
            {
                break;
            }
        }

    }

    void heapify(int index)
    {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int largest = index;

        if (left <= size && vec[left] > vec[largest])
        {
            largest = left;
        }

        if (right <= size && vec[right] > vec[largest])
        {
            largest = right;
        }

        if (largest != index)
        {
            deepest = max(largest, deepest);
            swap(vec[index], vec[largest]);
            heapify(largest);
        }
    }


    void removemax()
    {
        vec[0] = vec[size-1];
        vec[size-1] = -inf;
        size--;
        heapify(0);
    }

};

Heap h;

// Sätt in ett element i heapen
void insert(int element)
{
    h.insert(element);
}

// Returnera det största elementet i heapen
int getMax() {
    return h.vec[0];
}

// Ta bort det största värdet i heapen
void removeMax()
{
    h.removemax();
}

// Returnera antalet element i heapen
int getSize()
{
    return h.size;
}
