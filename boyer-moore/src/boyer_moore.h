#pragma once

#include <string>
#include <vector>
#include <algorithm>

class Boyer_Moore {
private:
    std::string pattern;
    std::vector<int> badChar;
    std::vector<int> goodSuffix;

    void preBadChar(std::string pattern);
    void preGoodSuffix(std::string pattern);
    int moveByGoodSuffix(int index, int patternLength);
public:
    Boyer_Moore();
    Boyer_Moore(const std::string& pattern);
    ~Boyer_Moore();

    void setPattern(const std::string& pattern);
    std::vector<int> search(const std::string& text);
};
