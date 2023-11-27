#include "aho_corasick.hpp"

// i don't know is this code is ok or not, but it works
// gonna improve it later
namespace aho_corasick {

    AhoCorasick::Vertex::Vertex(int p, char ch, int depth) : p(p), pch(ch), depth(depth) {
        std::fill(std::begin(next), std::end(next), -1);
        std::fill(std::begin(go), std::end(go), -1);
    }

    void AhoCorasick::add_string(std::string const& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (tree[v].next[c] == -1) {
                tree[v].next[c] = tree.size();
                tree.emplace_back(v, ch, tree[v].depth + 1);
            }
            v = tree[v].next[c];
        }
        tree[v].output = true;
    }

    int AhoCorasick::go(int v, char ch) {
        int c = ch - 'a';
        if (tree[v].go[c] == -1) {
            if (tree[v].next[c] != -1)
                tree[v].go[c] = tree[v].next[c];
            else
                tree[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
        }
        return tree[v].go[c];
    }

    int AhoCorasick::get_link(int v) {
        if (tree[v].link == -1) {
            if (v == 0 || tree[v].p == 0)
                tree[v].link = 0;
            else
                tree[v].link = go(get_link(tree[v].p), tree[v].pch);
        }
        return tree[v].link;
    }
}; // namespace aho_corasick