#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <stack>
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

string answer(string number)
{

    char firstDigit = number[number.size() - 1];
    if (firstDigit == '9')
    {
        int n_9 = 0;
        bool done = false;
        per(i, number.size() - 1)
        {
            if (number[i] == '9')
            {
                n_9++;
            }
            else
            {
                if (n_9 > 0)
                {
                    number[i + 1] = '8';
                    if (i >= 0)
                    {
                        number[i]++;
                    }
                    else
                    {
                        number.insert(number.begin(), '1');
                    }
                    done = true;
                    break;
                }
            }
        }

        if (n_9 > 0 && !done)
        {
            number[0]--;
            number.insert(number.begin(), '1');
        }
    }
    else if (firstDigit == '0')
    {
        int firstNoneZero = -1;

        per(i, number.size()-1)
        {
            if (number[i] != '0')
            {
                firstNoneZero = i;
                break;
            }
        }
        int firstNonNine = -1;


        bool hasNine = number.find('9') != string::npos;
        if (hasNine)
        {
            for (int i = number.rfind('9') - 1; i >= 0; i--)
            {
                if (number[i] != '9')
                {
                    firstNonNine = i;
                    break;
                }
            }



            int firstNonNine = -1;
            per(i, firstNoneZero-1)
            {
                if (number[i] != '9')
                {
                    firstNonNine = i;
                    break;
                }
            }

            if (firstNonNine != -1)
            {
                number[firstNonNine]++;
                number[firstNoneZero]--;
                sort(next(number.begin(), firstNonNine+1), number.end());
            }
            else
            {
                number[firstNoneZero]--;
                number.insert(number.begin(), '1');
                sort(next(number.begin(), 1), number.end());
            }

        }
        else
        {
            if (firstNoneZero-1<0)
            {
                if (number[0] == '1')
                {
                    number.push_back('0');
                }
                else
                {
                    number[number.size() - 1] = number[0] - 1;
                    number[0] = '0';
                    number.insert(number.begin(), '1');
                }

            }
            else
            {
                number[number.size() - 1] = number[firstNoneZero] - 1;
                number[firstNoneZero] = '0';
                number[firstNoneZero-1]++;
            }

        }
    }
    else
    {
        if (int(number.size())-2 < 0)
        {
            number[number.size() - 1]--;
            number.insert(number.begin(), '1');
        }
        else
        {
            if (number[number.size() - 2] == '9')
            {
                int firstNonNine = -1;

                per(i, number.size()-2)
                {
                    if (number[i] != '9')
                    {
                        firstNonNine = i;
                        break;
                    }
                }

                if (firstNonNine == -1)
                {
                    number.insert(number.begin(), '1');
                    number[1] = number[number.size() - 1]-1;
                    number[number.size() - 1] = '9';
                }
                else
                {
                    number[firstNonNine]++;
                    number[number.size() - 2] = number[number.size() - 1] - 1;
                    number[number.size() - 1] = '9';
                    sort(next(number.begin(), firstNonNine+1),number.end());
                }

            }
            else
            {
                number[number.size() - 1]--;
                number[number.size() - 2]++;
            }
        }

    }

    return number;
}

int main()
{
    fast();

    string number;
    read(number);

    write(answer(number));
    return 0;
}