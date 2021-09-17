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
#define setcontains(set, x) set.find(x) != set.end()
#define notsetcontains(set, x) set.find(x) == set.end()

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto const& i : container)


bool valid(vector<string>& board, const string& word, vector<vector<bool>>& visited, int x, int y, int wordIndex)
{
	if (wordIndex == word.size())
	{
		return true;
	}

	if (x < 0 || x > 3 || y < 0 || y > 3)
	{
		return false;
	}

	if (visited[x][y])
	{
		return false;
	}

	if (word[wordIndex] != board[x][y])
	{
		return false;
	}


	vector<int> mutations = { -5, -4, -3, -1, 1, 3, 4, 5};

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			visited[x][y] = true;
			if (valid(board, word, visited, x+i, y+j, wordIndex + 1))
			{
				return true;
			}
			visited[x][y] = false;
		}

	}


	return false;
}

void solve(set<string> words, vector<string> board, map<char, set<string>> firstLetters)
{
	vector<int> lengthToScore = {0,0,0,1,1,2,3,5,11};

	set<char> contained;
	repe(row, board)
	{
		repe(c, row)
		{
			contained.insert(c);
		}
	}



	map<char, set<pair<int, int>>> occurences;
	rep(i, 4)
	{
		rep(j, 4)
		{
			char c = board[i][j];
			if (notsetcontains(occurences, c))
			{
				occurences[c] = set<pair<int,int>>();
			}
			occurences[c].insert({i,j});
		}
	}

	set<string> temp;
	std::copy_if(words.begin(), words.end(), std::inserter(temp, temp.end()), [occurences](const string& value) { return occurences.find(value[0]) != occurences.end(); });
	words = temp;

	int uniqueSolutions = 0;
	string longestWord;
	int score = 0;
	repe(word, words)
	{
		repe(startIndex, occurences[word[0]])
		{
			vector<vector<bool>> visited;
			visited.resize(4, vector<bool>(4, false));
			if (valid(board, word, visited, startIndex.first, startIndex.second, 0))
			{
				if (word.size() > longestWord.size())
				{
					longestWord = word;
				}
				if (word.size() == longestWord.size() && word < longestWord)
				{
					longestWord = word;
				}

				score += lengthToScore[word.size()];
				uniqueSolutions++;
				break;
			}
		}
	}

	std::cout << score << " " << longestWord << " " << uniqueSolutions << endl;
}

int main()
{
	int w;

	read(w);


	map<char, set<string>> firstLetters;
	set<string> words;
	rep(i, w)
	{
		readinsert(string, words);
	}

	repe(word, words)
	{
		char firstLetter = word[0];
		if (firstLetters.find(firstLetter) == firstLetters.end())
		{
			firstLetters[firstLetter] = set<string>();
		}

		firstLetters[firstLetter].insert(word);
	}

	int b;
	read(b);

	vector<vector<string>> boards;

	rep(i, b)
	{
		vector<string> board;
		rep(j, 4)
		{
			readpush(string, board);
		}
		boards.push_back(board);
	}

	rep(i, b)
	{
		solve(words, boards[i], firstLetters);
	}

}