#pragma once

#include <string>
#include <vector>

class turbo_boyer_moore {
private:
    std::string pattern;
    std::vector<int> bad_char;
    std::vector<int> good_suffix;

    void calculateSuffix(std::vector<int>& suffix);
    void precompute_bad_char();
    void precompute_good_suffix();
public:
    turbo_boyer_moore();
    turbo_boyer_moore(const std::string& pattern);
    ~turbo_boyer_moore();

    void setPattern(const std::string& pattern);
    void clear();

    std::vector<int> search(const std::string& text);
};