#include <bits/stdc++.h>
using namespace std;

#define rep(i,hi) for (int i = 0; i < hi; i++)
#define repp(i,lo,hi) for (int i = lo; i < hi; i++)

int mguess(string s)
{
    cout << s << endl;
    string a,b,c,d;
    cin >> a >> b;
    if (b=="GRANTED")
    {
        exit(0);
    }
    cin >> c >> d;
    c.erase(c.begin());
    return stoi(c);
}

int main()
{
    string guess = "";

    int l = 0;
    repp(i, 1, 22)
    {
        string s = string(i, 'a');
        if (mguess(s)>5) 
        {
            l = i;
            break;
        }
    }


    vector<char> among;
    repp(c,'a','z'+1) among.push_back(c);
    repp(c,'A','Z'+1) among.push_back(c);
    repp(c,'0','9'+1) among.push_back(c);
    guess = string(l,'a');
    rep(i,25)
    {
        vector<pair<int,char>> guesses;
        int mi = 10000;
        for (auto c : among)
        {

            guess[i] = c;

            guesses.emplace_back(mguess(guess), c);
            mi = min(mi, guesses.back().first);
        }

        //cerr << "BEGIN CHOICE\n";
        for (auto p : guesses)
        {
            //cerr << p.first << " " << p.second << "\n";
            if (p.first!=mi)
            {
                guess[i] = p.second;
                break;
            }
        }
                //cerr << "END CHOICE\n";

        //exit(0);
    }
    

    return 0;
}

