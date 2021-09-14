
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

#define read(a) cin >> a; 
#define ll long long

#define rep(i, high) for (ll i = 0; i < high; i++)
#define write(a) cout << a << endl

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
				charToNum[char(i + 87)] = i;
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
	int a;
	read(a);

	std::vector<string> operators = { "+","-","/","*" };

	vector<line> expressions;

	rep(i, a)
	{
		line l;

		read(l.left);
		read(l.op);
		read(l.right);
		string ignore;
		read(ignore);
		read(l.answer);

		expressions.push_back(l);
	}

	map<int, char> numtochar = {};
	for (int i = 0; i < 26; i++)
	{
		numtochar[i+10] = i+97;
	}
	numtochar[36] = '0';
	for (size_t i = 1; i < 10; i++)
	{
		numtochar[i] = i + 48;
	}

	rep(i, expressions.size())
	{
		string bases = "";
		for (int base = 1; base <= 36; base++)
		{
			if (check_base(expressions[i], base))
			{
				bases += numtochar[base];
			}
		}

		if (bases.size() == 0)
		{
			write("invalid");
		}
		else
		{
			write(bases);
		}
	}

	return 0;
}