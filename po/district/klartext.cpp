#include <bits/stdc++.h>

using namespace std;

#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#define enablell 0

#define ll long long
#if enablell
#define int ll
#endif
#define vi vector<int>
#define vb vector<bool>
#define vvb vector<vb>
#define vvvb vector<vvb>
#define vvi vector<vi>
#define vvvi vector<vvi>
#define p2 pair<int, int>
#define p3 tuple<int,int,int>
#define p4 tuple<int,int,int,int>
#define vp2 vector<p2>
#define vvp2 vector<vp2>
#define vp3 vector<p3>
#define vp4 vector<p4>
#if enablell
#define inf 1e18
#else
#define inf int(1e9)
#endif

#define read(a) cin >> a
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
#else
#define noop ;
#define deb ;
#endif

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high; i >= 0; i--)
#define perr(i, low, high) for (int i = high; i >= low; i--)

#define readpush(type,vect) type temp; read(temp); vect.(temp);
#define readvector(type, name, size) vector<type> name(size); rep(i,size) {dread(type,temp); name[i]=temp;}
#define readinsert(type,a) {type temp; read(temp); a.insert(temp);}
#define all(a) begin(a),end(a)
#define setcontains(set, x) (set.find(x) != set.end())
#define stringcontains(str, x) (str.find(x) != string::npos)
#define within(a, b, c, d) (a >= 0 && a < b && c >= 0 && c < d)
#define insideinterval(v, interval) (v >= interval.first && v <= interval.second)
#define sz(container) ((int)container.size())
#define mp(a,b) (make_pair(a,b))

#define ceildiv(x,y) ((x + y - 1) / y)
#define fract(a) (a-floor(a))
#define sign(a) ((a>0) ? 1 : -1)

auto Start = chrono::high_resolution_clock::now();

inline void fast()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

template <typename T, typename U>
void operator+=(std::pair<T, U>& l, const std::pair<T, U>& r)
{
    l = { l.first + r.first,l.second + r.second };
}

string reverse2(string in, int depth)
{
    if (in.size()==1)
    {
        return in;
    }
    string ret(in.size(),'-');

    std::string left = in.substr(0, ceildiv(in.length(), 2));
    std::string right = in.substr(ceildiv(in.length(), 2));

    if (depth%2==0)
    {
        rep(i, left.size())
        {
            ret[i * 2] = in[i];
        }
    }
    else
    {
        rep(i, left.size())
        {
            ret[(ret.size() - 1) - i * 2] = left[i];
        }
    }


    string second = reverse2(right, depth+1);

    int offset = ret[0] != '-';
    rep(i, second.size())
    {
        ret[i * 2 + offset] = second[i];
    }


    return ret;

}


string solve4(string in)
{
    if (in.size()==1)
    {
        return in;
    }
    string ret = "";
    if (in.size()%2==0)
    {
        int low = in.size() / 2;
        int high = in.size() / 2;
        string left = in.substr(0, low);
        string right = in.substr(high);
        ret = solve4(right) + solve4(left);
    }
    else
    {
        int low = in.size() / 2;
        int high = ceildiv(in.size(), 2);
        string left = in.substr(0, low);
        string right = in.substr(high);

        ret = solve4(left) + in[in.size() / 2] + solve4(right);
    }

    return ret;
}


int32_t main()
{
    fast();

#if 0
    ifstream cin("C:\\Users\\Matis\\source\\repos\\Comp prog\\x64\\Debug\\in.txt");
#endif

    int type;
    read(type);

    int testing = 2;
    bool isTesting = false;

    if (type == 1 && (!isTesting || type==testing))
    {
        string cipher;
        read(cipher);

        int hyphen = cipher.find("-");
        int offset = stoi(cipher.substr(0, hyphen));
        cipher = cipher.substr(hyphen + 1, cipher.size() - hyphen);


        repe(letter, cipher)
        {
            int newLetter = (letter + offset);
            if (newLetter > 'z')
            {
                newLetter = char((newLetter)-'z' + 'a' - 1);
            }
            cout << char(newLetter);
        }

    }
    else if (type==2 && (!isTesting || type == testing))
    {
        dread(string, cipher);
        string ans(cipher.size(),'-');

        cout << reverse2(cipher,0);
    }
    else if (type==3)
    {
        //           0   1   2   3   4  5  6  7  8  9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24
        vi perm = { 24, 21, 23, 20, 22, 9, 6, 8, 5, 7, 19, 16, 18, 15, 17, 4,  1,  3,  0,  2,  14, 11, 13, 10, 12, };

        dread(string, cipher);
        string out(cipher.size(),'-');


        rep(i, cipher.size())
        {
            out[perm[i]] = cipher[i];
        }
        cout << out;
        //123456789ABCDEFGHIJKLMNOP
        //abcbbbcbbcdbacccdbbdcbbdc 0
        //bbabadcbacadbcbacbbbcdddd 4
        //dcdadddacbcaaddbadccccbca 2
        //cbdabbacaabbabdddabbdcdbc 1
        //ccaabcbcbdaddcddddbaaabcd 3
        //cbbcbbadaddacddbbdcbbacad 5


        //123456789ABCDEFGHIJKLMNOP
        //cbdcbccbbbddbcbbbbaccbcda 0
        //ccbddaaabcbdbdabbacddbbba 1
        //acccbbdcdacacbddcadddadca 2
        //dacabdbbccadbddbcacaddcad 3
        //dddcdccadbbcbababbbabdcab 4
        //daabcdaabdbbcbdbbccbdaddc 5
    }
    else if (type == 4 && (!isTesting || type == testing))
    {
        string cipher;
        read(cipher);
        cout << solve4(cipher);
    }
    else if (type==5)
    {
        string cipher;
        read(cipher);

        map<string, char> keys = {
            {"1110000", 'a'},
            {"1110001", 'b'},
            {"001010", 'c'},
            {"001011", 'd'},
            {"011100", 'e'},
            {"011101", 'f'},
            {"101010", 'g'},
            {"101011", 'h'},
            {"111001", 'i'},
            {"00100", 'j'},
            {"01010", 'k'},
            {"01011", 'l'},
            {"01111", 'm'},
            {"10100", 'n'},
            {"11000", 'o'},
            {"11001", 'p'},
            {"11101", 'q'},
            {"0011", 'r'},
            {"0100", 's'},
            {"0110", 't'},
            {"1000", 'u'},
            {"1001", 'v'},
            {"1011", 'w'},
            {"1101", 'x'},
            {"1111", 'y'},
            {"000", 'z'}
        };

        string out = "";

        while (cipher.size())
        {
            repe(key, keys)
            {
                if (cipher.size()>=key.first.size())
                {
                    if (cipher.substr(0,key.first.size()) == key.first)
                    {
                        cipher = cipher.substr(key.first.size());
                        out += key.second;
                        break;
                    }
                }
            }
        }
        cout << out;
    }


    quit;
}
