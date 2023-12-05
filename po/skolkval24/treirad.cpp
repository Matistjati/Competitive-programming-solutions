#include <iostream>
int main()
{
    int n;
    std::cin >> n;
    int l = 1;
    while (l * (l + 1) * (l + 2) < n) l++;
    std::cout << l - 1;
}
