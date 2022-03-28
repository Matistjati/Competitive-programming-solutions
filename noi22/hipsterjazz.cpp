

using namespace std;

#include <bits/stdc++.h>

#define vi vector<int>

#define ceildiv(x,y) ((x + y - 1) / y)

int main()
{

    int n, m;
    cin >> n >> m;


    vi colors(n);
    vector<vi> edges(n);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
    }

    for (int i = 0; i < n; i++)
    {
        colors[i] = rand() % 2;
    }

    bool valid = true;
    do
    {
        valid = true;
        for (int i = 0; i < n; i++)
        {
            int different = 0;
            for (auto& edge : edges[i])
            {
                if (colors[edge]!=colors[i])
                {
                    different++;
                }
            }

            int s = (edges[i].size() % 2 == 0 ? edges[i].size() / 2 : (edges[i].size()) / 2+1);
            if (different<s)
            {
                colors[i] = (colors[i]==0?1:0);
                valid = false;
                break;
            }
        }
        /*if (valid)
        {
            __debugbreak();
        }*/
    } while (!valid);


    for (int i = 0; i < n; i++)
    {
        cout << (colors[i] ? 'P' : 'S');
    }
}