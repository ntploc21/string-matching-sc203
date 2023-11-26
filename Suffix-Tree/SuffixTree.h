#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include <string>
#include <vector>
using namespace std;

struct suffix_tree {
    struct node {
        int start;
        int end;
        vector<node*> children;
        node* slink;
        suffix_tree* stree;
        node(int start, int end, suffix_tree* stree)
            : start(start),
              end(end),
              children(vector<node*>(27)),
              stree(stree) {}
        int getEdgeLen() {
            return (end == stree->LAST_POS ? stree->cur_len : end) - start;
        }
        node*& childAt(char ch) { return children[ch - 'a' + 1]; }
    };

    struct implicit_node {
        node* v;
        char ch;
        int edge_len;

        void canonize() {
            if (edge_len == 0) return;
            node* child = v->childAt(ch);
            int actual_edge_len = child->getEdgeLen();
            while (actual_edge_len <= edge_len) {
                v = child;
                edge_len -= actual_edge_len;
                if (edge_len != 0) {
                    ch = v->stree->getChar(v->stree->cur_len - edge_len);
                    child = v->childAt(ch);
                    actual_edge_len = child->getEdgeLen();
                }
            }
        }

        void moveToSuffix() {
            if (v != v->stree->root) {
                v = v->slink;
            } else if (edge_len > 0) {
                edge_len--;
                ch = v->stree->getChar(v->stree->cur_len - edge_len);
            }
        }

        void moveForward() {
            edge_len++;
            if (edge_len == 1) {
                ch = v->stree->getChar(v->stree->cur_len);
            }
        }
    };

    string s;
    node* root;
    implicit_node active_point;

    suffix_tree(string s)
        : s(s), root(new node(0, 0, this)), active_point{root, '\0', 0} {
        ukkonen();
    }

    void dfs();

    bool contains(string s);

    vector<int> getAllOccurences(string s);

   private:
    void ukkonen();
    void add_letter(int pos);
    bool test_and_split(int ch, node*& new_node);
    char getChar(int pos) { return pos < s.size() ? s[pos] : 'a' - 1; }
    void dfs(node* root, string path_to_parent);
    void dfs(node* root, string path_to_parent, vector<int>& res);
    vector<int> bfs(node* root, int len);
    const int LAST_POS = -1;

    int cur_len = 0;
};

#endif  // SUFFIX_TREE_H
