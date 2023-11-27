#ifndef __AHO_CORASICK_HPP__
#define __AHO_CORASICK_HPP__

#include <vector>
#include <string>

// code from cp-algorithms: https://cp-algorithms.com/string/aho_corasick.html
namespace aho_corasick {
    class AhoCorasick {
        public:
        static const int ALPHABET_SIZE = 26;

        struct Vertex {
            int next[ALPHABET_SIZE]{};
            bool output{false};
            int p{-1};
            char pch{};
            int link{-1};
            int go[ALPHABET_SIZE]{};
            int depth{};

            Vertex(int p = -1, char ch = '$', int depth = 0);
        };

        

        void add_string(std::string const& s);

        int go(int v, char ch);

        int get_link(int v);

        Vertex get_node(int v) {
            return tree[v];
        }

        private:
        std::vector<AhoCorasick::Vertex> tree{1};
    };

}; // namespace aho_corasick

#endif // __AHO_CORASICK_HPP__
