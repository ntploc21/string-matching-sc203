#include "kmp.hpp"

KMP::KMP(const std::string &pattern)
{
    pi = buildTable(pattern);
}

std::vector<int> KMP::buildTable(const std::string &pattern)
{
    int n = (int)pattern.length();
    std::vector<int> pi(n);
    int j = 0;
    for (int i = 1; i < n; i++)
    {
        while (j > 0 && pattern[i] != pattern[j])
            j = pi[j - 1];
        if (pattern[i] == pattern[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

std::vector<int> KMP::search(const std::string &text, const std::string &pattern)
{
    std::vector<int> ans;
    std::vector<int> pi = buildTable(pattern);
    int n = (int)text.length();
    int m = (int)pattern.length();
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        while (j > 0 && text[i] != pattern[j])
            j = pi[j - 1];
        if (text[i] == pattern[j])
            j++;
        if (j == m)
        {
            ans.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return ans;
}

