#ifndef KMP_KMP_HPP
#define KMP_KMP_HPP

#include <vector>
#include <string>

class KMP
{
public:
    KMP(const std::string &pattern);
    std::vector<int> search(const std::string &text, const std::string &pattern);
private:
    std::vector<int> buildTable(const std::string &pattern);
    std::vector<int> pi;
};


#endif // KMP_KMP_HPP
