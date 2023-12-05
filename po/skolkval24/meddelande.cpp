#include <iostream>
#include <string>
int main()
{
    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < s.size(); j++) if (s[j] != '.') std::cout << s[j];
    }
}
