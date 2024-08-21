#include "doll.h"

#include <bits/stdc++.h>
using namespace std;

const int inf = int(1e9);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int n;
int ind = 1;
vi state;
vi x, y;
int k=0;
vi exitcnt;
int numexits = 0;
int build_tree(int d, vi& x, vi& y)
{
	int u = ind++;
	if (d==0)
	{
		exitcnt[u] = 2;
		numexits += 2;
		x[u] = inf;
		y[u] = inf;
		return u;
	}
	y[u] = build_tree(d - 1, x, y);
	x[u] = build_tree(d - 1, x, y);
	exitcnt[u] = exitcnt[x[u]] + exitcnt[y[u]];
	return u;
}

void killc(int u, vi& x, vi& y)
{
	if (u == inf) return;
	if (x[u]!=inf)
	{
		exitcnt[x[u]] = 0;
		killc(x[u], x, y);
		x[u] = inf;
	}
	if (y[u]!=inf)
	{
		exitcnt[y[u]] = 0;
		killc(y[u], x, y);
		y[u] = inf;
	}
}

bool kill(int u, vi& x, vi& y)
{
	if (u == inf) return false;
	if (numexits-exitcnt[u]>=n+1)
	{
		numexits -= exitcnt[u];
		killc(u, x, y);
		return true;
	}
	
	if (kill(x[u], x, y))
	{
		exitcnt[u] -= exitcnt[x[u]];
		x[u] = 1;
	}
	if (kill(y[u], x, y))
	{
		exitcnt[u] -= exitcnt[y[u]];
		y[u] = 1;
	}
	exitcnt[u] = 0;
	if (x[u] != inf) exitcnt[u] += exitcnt[x[u]];
	if (y[u] != inf) exitcnt[u] += exitcnt[y[u]];
	return false;
}

int* lastv = 0;
int statesum = 0;
void traverse(int u, int t)
{
	int& v = state[u]?y[u]:x[u];
	if (v == -1) return;
	statesum += state[u] == 0 ? 1 : -1;
	state[u] ^= 1;
	if (v==inf)
	{
		lastv = &v;
		v = -t;
		return;
	}
	traverse(v, t);
}

void create_circuit(int m, std::vector<int> a)
{
	n = sz(a);
	vi c(m + 1, -1);
	c[0] = a[0];
	n--;
	a.erase(a.begin());
	while ((1<<(k+1))<=n)
	{
		k++;
	}

	state.resize(1 << (k+1));
	x.resize(1 << (k+1), inf);
	y.resize(1 << (k+1), inf);
	exitcnt.resize(1 << (k+1), 0);
	build_tree(k, x, y);
	kill(1, x, y);
	rep(i, n)
	{
		traverse(1, a[i]);
	}
	repp(i, n, (1<<(k+1)))
	{
		traverse(1, -1);
		if (statesum == 0)
		{
			*lastv = 0;
			break;
		}
	}

	while (x.back()==inf&&y.back()==inf)
	{
		x.pop_back();
		y.pop_back();
	}
	rep(i, sz(x)) x[i] *= -1, y[i] *= -1;
	rep(i, sz(x))
	{
		if (x[i] == -inf) x[i] = -1;
		if (y[i] == -inf) y[i] = -1;
	}
	x.erase(x.begin());
	y.erase(y.begin());
	
	answer(c, x, y);
}
