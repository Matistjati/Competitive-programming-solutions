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

struct line
{
    string left;
    string right;
    char op;
    string answer;
};

double applyOperator(double left, double right, char op)
{
    switch (op)
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '/':
        return left / right;
    case '*':
        return left * right;
    default:
        write("fuck you");
        return -INFINITY;
        break;
    }
}

bool check_base(line expression, double base)
{
    map<char, double> charToNum = { };
    if (base == 1)
    {
        charToNum['1'] = 1;
    }
    else
    {
        for (int i = 0; i < base; i++)
        {
            if (i < 10)
            {
                charToNum[char(i + 48)] = i;
            }
            else
            {
                charToNum[char(i + 55)] = i;
            }

        }
    }


    double leftval = 0;
    double rightval = 0;
    double answer = 0;

    for (size_t i = 0; i < expression.left.size(); i++)
    {
        if (!charToNum.count(expression.left[i]))
        {
            return false;
        }
        leftval += pow(base, double(expression.left.size() - 1 - i)) * charToNum[expression.left[i]];
    }

    for (size_t i = 0; i < expression.right.size(); i++)
    {
        if (!charToNum.count(expression.right[i]))
        {
            return false;
        }
        rightval += pow(base, double(expression.right.size() - 1 - i)) * charToNum[expression.right[i]];
    }

    for (size_t i = 0; i < expression.answer.size(); i++)
    {
        if (!charToNum.count(expression.answer[i]))
        {
            return false;
        }
        answer += pow(base, double(expression.answer.size() - 1 - i)) * charToNum[expression.answer[i]];
    }

    if (applyOperator(leftval, rightval, expression.op) == answer)
    {
        return true;
    }

    return false;
}

int main()
{
    fast();



    std::vector<string> operators = { "+","-","/","*" };

    vector<line> expressions;


    line l;

    read(l.left);
    l.op = '+';
    read(l.right);
    read(l.answer);

    expressions.push_back(l);

    map<int, char> numtochar = {};
    for (int i = 0; i < 26; i++)
    {
        numtochar[i + 10] = i + 97;
    }
    numtochar[36] = '0';
    for (size_t i = 1; i < 10; i++)
    {
        numtochar[i] = i + 48;
    }

    rep(i, expressions.size())
    {
        vector<int> bases;
        for (int base = 2; base <= 16; base++)
        {
            if (check_base(expressions[i], base))
            {
                bases.push_back(base);
            }
        }


        rep(i, bases.size())
        {
            cout << bases[i] << " ";
        }
    }

    return 0;
}