#include "kmp.hpp"

#include <iostream>

int main(int argc, char const *argv[])
{

    std::string pattern;
    std::string text;

    if (argc > 1)
    {
        pattern = argv[1];
        text = argv[2];
    }
    else
    {
        pattern = "ababaca";
        text = "bacbabababacaca";
    }

    KMP kmp(pattern);
    std::vector<int> ans = kmp.search(text, pattern);

    for (int i = 0; i < (int)ans.size(); i++)
    {
        std::cout << ans[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}