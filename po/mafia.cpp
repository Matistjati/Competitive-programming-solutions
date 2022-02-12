#undef _GLIBCXX_DEBUG                // disable run-time bound checking, etc
#pragma GCC optimize("Ofast,inline") // Ofast = O3,fast-math,allow-store-data-races,no-protect-parens
#pragma GCC optimize ("unroll-loops")

#pragma GCC target("bmi,bmi2,lzcnt,popcnt")                      // bit manipulation
#pragma GCC target("movbe")                                      // byte swap
#pragma GCC target("aes,pclmul,rdrnd")                           // encryption
#pragma GCC target("avx,avx2,f16c,fma,sse3,ssse3,sse4.1,sse4.2") // SIMD

#include <bits/stdc++.h>
//#include <bits/extc++.h>

using namespace std;

#define enablell 0

#define ll long long
#if enablell
#define int ll
#define inf 2e18
#define float double
#else
#define inf int(2e9)
#endif
#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define vvvvi vector<vvvi>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define p2 pair<int, int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vvvp2 vector<vvp2>
#define p3 tuple<int,int,int>
#define vp3 vector<p3>
#define vvp3 vector<vp3>
#define vvvp3 vector<vvp3>
#define p4 tuple<int,int,int,int>
#define vp4 vector<p4>

#define read(a) cin >> a
#define read2(a,b) cin >> a >> b
#define read3(a,b,c) cin >> a >> b >> c
#define write(a) cout << (a) << "\n"
#define quit cout << endl; _Exit(0);
#define dread(type, a) type a; cin >> a
#define dread2(type, a, b) dread(type, a); dread(type, b)
#define dread3(type, a, b, c) dread2(type, a, b); dread(type, c)
#define dread4(type, a, b, c, d) dread3(type, a, b, c); dread(type, d)
#define dread5(type, a, b, c, d, e) dread4(type, a, b, c, d); dread(type, e)
#ifdef _DEBUG
#define noop cout << "";
#define deb __debugbreak();
#define debassert(expr) if (!(expr)) deb;
#define debif(expr) if(expr) deb;
#else
#define noop ;
#define deb ;
#define debassert(expr) ;
#define debif(expr) ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, low, high) for (int i = high-1; i >= low; i--)

#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))
#define first(a) (*begin(a))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))

auto Start = chrono::high_resolution_clock::now();
#define elapsedmillis() (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count())
#define rununtil(time) if (elapsedmillis() >= time) break;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
template <typename T, typename U> inline void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r) { l = { l.first + r.first,l.second + r.second }; }
template <typename T> inline int sgn(T val) { return (T(0) < val) - (val < T(0)); }
template <typename Out> inline void split(const string& s, char delim, Out result) { istringstream iss(s);  string item; while (getline(iss, item, delim)) { *result++ = item; } }
inline vector<string> split(const string& s, char delim) { vector<string> elems; split(s, delim, back_inserter(elems)); return elems; }

#define UNVISITED 0
#define GOOD 1
#define BAD 2

int opposite(int col)
{
	if (col == 0) deb;

	if (col == GOOD) return BAD;
	if (col == BAD) return GOOD;
	deb;
}

p2 findsubset(vvp3& edges, vb& seen, vi& color, int curr)
{
	if (seen[curr]) return { 0,0 };
	seen[curr] = true;

	p2 ret = { color[curr] == BAD,color[curr] == GOOD};

	repe(edge, edges[curr])
	{
		int node, type, fromMe;
		tie(node, type, fromMe) = edge;
		if (color[curr]==GOOD)
		{
			if (fromMe)
			{
				assert(color[node] == UNVISITED || color[node] == type);
				color[node] = type;
			}
			else
			{
				if (color[node] == UNVISITED)
				{
					color[node] = (type == GOOD) ? GOOD : BAD;
				}
				else
				{
					if (color[node]==GOOD)
					{
						assert(type == color[curr]);
					}
					else
					{
						assert(type == opposite(color[curr]));
					}
				}
			}
		}
		else if (color[curr]==BAD)
		{
			if (fromMe)
			{
				assert(color[node] == UNVISITED || color[node] == opposite(type));
				color[node] = opposite(type);
			}
			else
			{
				if (color[node] == UNVISITED)
				{
					color[node] = (type == BAD) ? GOOD : BAD;
				}
				else
				{
					if (color[node] == GOOD)
					{
						assert(type == color[curr]);
					}
					else
					{
						assert(type == opposite(color[curr]));
					}
				}
			}
		}
		else
		{
			deb;
		}
		ret += findsubset(edges, seen, color, node);
	}

	return ret;
}

vector<ll> ans;

void cops(int n, int m, int a[], int b[], int t[])
{
	ans = vector<ll>(n+1, 0);
	ans[0] = 1;
	vb seen(n);
	vvp3 edges(n);

	rep(i, m)
	{
		edges[a[i]].emplace_back(b[i], t[i], true);
		edges[b[i]].emplace_back(a[i], t[i], false);
	}


	vi color(n);

	rep(i, n)
	{
		if (seen[i]) continue;
		color[i] = BAD;
		p2 s = findsubset(edges, seen, color, i);

		vector<ll> newrow(n+1, 0);
		rep(j, n+1)
		{
			if (j + s.first <= n) newrow[j + s.first] += ans[j];
			if (j + s.second <= n) newrow[j + s.second] += ans[j];

		}
		ans = move(newrow);
	}

}

long long guess(int C)
{
	return ans[C];
}

//
//int32_t main() {
//	dread2(int, N, M);
//	vi A(M), B(M), T(M);
//	for (int i = 0; i < M; i++) read(A[i]);
//	for (int i = 0; i < M; i++) read(B[i]);
//	for (int i = 0; i < M; i++) read(T[i]);
//	dread(int, G);
//
//	vi C(G);
//	for (int i = 0; i < G; i++) read(C[i]);
//	cops(N, M, &A[0], &B[0], &T[0]);
//	int k = 0;
//	for (int i = 0; i < G; ++i) {
//		int g = guess(C[i]);
//		cout << g << " ";
//		k += g==1;
//	}
//	cout << ("\n");
//	//write(k);
//}



//
//int32_t main()
//{
//    fast();
//
//#if 0
//    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
//#endif
//
//
//
//
//
//
//    quit;
//}