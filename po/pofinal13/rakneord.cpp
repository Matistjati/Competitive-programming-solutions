#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

map<int, string> basecases;
map<int, string> tens;
void init()
{
	basecases[1] = "ett";
	basecases[2] = "tva";
	basecases[3] = "tre";
	basecases[4] = "fyra";
	basecases[5] = "fem";
	basecases[6] = "sex";
	basecases[7] = "sju";
	basecases[8] = "atta";
	basecases[9] = "nio";
	basecases[10] = "tio";
	basecases[11] = "elva";
	basecases[12] = "tolv";
	basecases[13] = "tretton";
	basecases[14] = "fjorton";
	basecases[15] = "femton";
	basecases[16] = "sexton";
	basecases[17] = "sjutton";
	basecases[18] = "arton";
	basecases[19] = "nitton";

	tens[20] = "tjugo";
	tens[30] = "trettio";
	tens[40] = "fyrtio";
	tens[50] = "femtio";
	tens[60] = "sextio";
	tens[70] = "sjuttio";
	tens[80] = "attio";
	tens[90] = "nittio";
}
string get_part(int rem, string magnitude)
{
	if (rem == 0) return "";
	string ret = "";
	int ten_r = rem % 100;
	if (ten_r)
	{
		if (rem == 1)
		{
			if (magnitude == "") ret = "ett";
			if (magnitude == "tusen") ret = "ettusen";
			if (magnitude == "miljoner") ret = "enmiljon";
			if (magnitude == "miljarder") ret = "enmiljard";
		}
		else
		{
			if (ten_r < 20)
			{
				ret += basecases[ten_r];
			}
			else
			{
				ret += tens[ten_r - ten_r % 10] + basecases[ten_r % 10];
			}
			if (sz(ret) >= 3 && sz(magnitude))
			{
				if (ret.substr(sz(ret) - 3) == "ett")
				{
					rep(i, 3)ret.pop_back();
					ret += "en";
				}
			}
			ret += magnitude;
		}
	}
	else ret += magnitude;
	int hundred = rem - rem % 100;
	if (hundred)
	{
		ret = basecases[hundred / 100] + "hundra" + ret;
	}

	return ret;
}

string get_word(int i)
{
	vi remainders;
	while (i)
	{
		remainders.push_back(i % 1000);
		i /= 1000;
	}
	string ret = "";

	if (sz(remainders))
	{
		ret += get_part(remainders[0], "");
	}
	if (sz(remainders) > 1)
	{
		string s = get_part(remainders[1], "tusen");
		ret = s + ret;
	}
	if (sz(remainders) > 2)
	{
		string s = get_part(remainders[2], "miljoner");
		ret = s + ret;
	}
	if (sz(remainders) > 3)
	{
		string s = get_part(remainders[3], "miljarder");
		ret = s + ret;
	}
	return ret;
}

vector<vector<pair<string, int>>> parts(4);

void precomp()
{
	rep(i, 1000)
	{
		parts[3].emplace_back(get_part(i, ""), i);
		parts[2].emplace_back(get_part(i, "tusen"), i);
		parts[1].emplace_back(get_part(i, "miljoner"), i);
		parts[0].emplace_back(get_part(i, "miljarder"), i);
	}
	rep(i, 4) sort(all(parts[i]));
}

p2 dp[2][4][100];
p2 count(int part, bool unlimited, int stringind, string& maxs, vi& maxparts)
{
	if (part == sz(parts))
	{
		return p2(0,1);
	}

	p2& v = dp[unlimited][part][stringind+1];
	if (v.first != -1) return v;

	bool string_unlimited = stringind == -1;

	p2 ret = p2(0,0);
	repe(p, parts[part])
	{
		
		bool new_unlimited;
		if (unlimited) new_unlimited = 1;
		else
		{
			if (p.second > maxparts[part]) continue;
			if (p.second == maxparts[part]) new_unlimited = unlimited;
			else new_unlimited = 1;
		}
		int new_stringind = -2;
		if (stringind != -1)
		{
			for (int i = 0; ; i++)
			{
				if (i + stringind >= sz(maxs))
				{
					// equal, maxs shorter
					new_stringind = -2;
					break;
				}
				if (i >= sz(p.first))
				{
					new_stringind = stringind + sz(p.first); // equal, other is shorter
					break;
				}
				if (maxs[i + stringind] < p.first[i])
				{
					// maxs is lexicographically smaller
					new_stringind = -2;
					break;
				}
				if (maxs[i + stringind] > p.first[i])
				{
					// p.first is lexicographically smaller, from now on unlimited
					new_stringind = -1;
					break;
				}
			}
		}
		else new_stringind = -1;
		
		if (new_stringind == -2) continue;

		p2 r = count(part + 1, new_unlimited, new_stringind, maxs, maxparts);
		ret.first += r.first + r.second * sz(p.first);
		ret.second += r.second;
	}
	return v = ret;
}

int wlen(int max, string maxs)
{
	assert(max);
	string m = to_string(max);
	while (sz(m) < 12) m.insert(m.begin(), '0');
	vi maxparts;
	rep(i, 4)
	{
		maxparts.push_back(stoi(m.substr(sz(m) - 3)));
		rep(j, 3) m.pop_back();
	}
	reverse(all(maxparts));
	int start = 0;
	while (maxparts[start] == 0) start++;
	rep(a, 2) rep(b, 4) rep(c, 100)
	{
		dp[a][b][c] = p2(-1, -1);
	}

	return count(start, 0, 0, maxs, maxparts).first;
}


signed main()
{
	fast();

	init();
	precomp();
	assert(get_word(1) == "ett");
	assert(get_word(2) == "tva");
	assert(get_word(3) == "tre");
	assert(get_word(4) == "fyra");
	assert(get_word(5) == "fem");
	assert(get_word(6) == "sex");
	assert(get_word(7) == "sju");
	assert(get_word(8) == "atta");
	assert(get_word(9) == "nio");
	assert(get_word(10) == "tio");
	assert(get_word(11) == "elva");
	assert(get_word(12) == "tolv");
	assert(get_word(13) == "tretton");
	assert(get_word(14) == "fjorton");
	assert(get_word(15) == "femton");
	assert(get_word(16) == "sexton");
	assert(get_word(17) == "sjutton");
	assert(get_word(18) == "arton");
	assert(get_word(19) == "nitton");
	assert(get_word(20) == "tjugo");
	assert(get_word(30) == "trettio");
	assert(get_word(40) == "fyrtio");
	assert(get_word(50) == "femtio");
	assert(get_word(60) == "sextio");
	assert(get_word(70) == "sjuttio");
	assert(get_word(80) == "attio");
	assert(get_word(90) == "nittio");
	assert(get_word(91) == "nittioett");
	assert(get_word(100) == "etthundra");
	assert(get_word(198) == "etthundranittioatta");
	assert(get_word(201) == "tvahundraett");
	assert(get_word(1121) == "ettusenetthundratjugoett");
	assert(get_word(581743) == "femhundraattioentusensjuhundrafyrtiotre");
	assert(get_word(51101001) == "femtioenmiljoneretthundraentusenett");
	assert(get_word(162500020) == "etthundrasextiotvamiljonerfemhundratusentjugo");
	assert(get_word(1002001004) == "enmiljardtvamiljonerettusenfyra");
	assert(get_word(91011091000) == "nittioenmiljarderelvamiljonernittioentusen");

	assert(wlen(999, "z") == 16260);
	assert(wlen(9999, "z") == 235600);
	assert(wlen(99999, "z") == 2908000);
	assert(wlen(999999, "z") == 37425000);
	assert(wlen(9999999, "z") == 472250000);
	assert(wlen(99999999, "z") == 5319500000);

	int n, k;
	cin >> n >> k;
	k--;

	auto get_char = [&](int k)
	{
		string s = string(100, 'z');
		string last;
		rep(i, 100)
		{
			for (int c = 'z'; c>='a';c--)
			{
				s[i] = c;
				int l = wlen(n, s);
				if (l<=k)
				{
					s[i] = c + 1;
					last = s;
					break;
				}
			}
		}
		while (wlen(n,s)>k)
		{
			s.pop_back();
		}
		k -= wlen(n, s);
		cout << s[k];
	};
	get_char(k);
	get_char(k + 1);
	get_char(k + 2);

	return 0;
}
