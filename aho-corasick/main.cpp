#include "aho_corasick.hpp"
#include <iostream>

using namespace aho_corasick;

// sample usage, see https://cp-algorithms.com/string/aho_corasick.html
int main() {
    AhoCorasick aho_corasick;
    aho_corasick.add_string("he");
    aho_corasick.add_string("she");
    aho_corasick.add_string("his");
    aho_corasick.add_string("hers");
    
    std::string text = "ahishers";
    int v = 0;
    for (int i = 0; i < text.size(); ++i) {
        v = aho_corasick.go(v, text[i]);
        if (aho_corasick.get_node(v).output) {
            std::cout << "Word ending at " << i << " is " << text.substr(i - aho_corasick.get_node(v).depth + 1, aho_corasick.get_node(v).depth) << std::endl;
        }
    }
}