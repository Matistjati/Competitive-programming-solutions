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

using namespace std;

#define ll long long
#define read(a) cin >> a
#define write(a) cout << a << endl
#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto const& i : container)
#define inf 1e9

vector<string> correctBoard = { "11111",
							    "01111",
							    "00 11",
							    "00001",
							    "00000" };
vector<pair<int, int>> offsets = { {-2,-1}, {-2,1}, {2,-1}, {2,1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} };

int main()
{
	int n;
	read(n);

	map<vector<string>, int> states;

	queue<vector<string>> toDo;

	toDo.push(correctBoard);
	states[correctBoard] = 0;

	while (toDo.size())
	{
		auto curr = toDo.front();
		toDo.pop();

		int n_moves = states[curr];
		if (n_moves >= 10)
		{
			break;
		}

		int whiteX;
		int whiteY;
		rep(i, 5)
		{
			rep(j, 5)
			{
				if (curr[i][j] == ' ')
				{
					whiteX = i;
					whiteY = j;
					goto found;
				}
			}
		}

		found:


		vector<string> copy(curr);
		repe(offset, offsets)
		{
			int newX = whiteX + offset.first;
			int newY = whiteY + offset.second;

			if (newX < 0 || newX > 4 || newY < 0 || newY > 4)
			{
				continue;
			}


			swap(copy[whiteX][whiteY], copy[newX][newY]);
			if (!setcontains(states, copy))
			{
				states[copy] = n_moves + 1;
				toDo.push(copy);
			}
			swap(copy[whiteX][whiteY], copy[newX][newY]);


		}

	}


	rep(i, n)
	{
		vector<string> board(5, "XXXXX");
		rep(j, 5)
		{
			getline(cin, board[j]);
			if (board[j] == "")
			{
				getline(cin, board[j]);
			}
		}

		if (setcontains(states, board))
		{
			cout << "Solvable in " << states[board] << " move(s)." << endl;
		}
		else
		{
			write("Unsolvable in less than 11 move(s).");
		}
	}
}