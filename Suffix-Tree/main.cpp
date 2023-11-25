// On–line construction of suffix trees
// https://www.cs.helsinki.fi/u/ukkonen/SuffixT1withFigs.pdf

#include <bits/stdc++.h>

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

void suffix_tree::ukkonen() {
    for (int i = 0; i <= s.size(); i++) {
        add_letter(i);
    }
}

void suffix_tree::add_letter(int pos) {
    node* parent;
    bool end_point;
    node* last_new_node = root;
    do {
        end_point = test_and_split(pos, parent);
        if (last_new_node != root) {
            last_new_node->slink = parent;
        }
        if (!end_point) {
            node* new_leaf = new node(pos, LAST_POS, this);
            parent->childAt(getChar(pos)) = new_leaf;

            last_new_node = parent;

            active_point.moveToSuffix();
        }
    } while (!end_point && parent != root);
    if (end_point) {
        active_point.moveForward();
    }
    cur_len++;
}

bool suffix_tree::test_and_split(int pos, node*& new_node) {
    char new_char = getChar(pos);
    active_point.canonize();
    node* parent = active_point.v;
    if (active_point.edge_len == 0) {
        new_node = parent;
        return parent->childAt(new_char) != NULL;
    }
    node* child = parent->childAt(active_point.ch);
    int split_pos = child->start + active_point.edge_len;
    if (getChar(split_pos) == new_char) {
        return true;
    } else {
        new_node = new node(child->start, split_pos, this);
        new_node->childAt(getChar(split_pos)) = child;
        parent->childAt(active_point.ch) = new_node;
        child->start = split_pos;
        return false;
    }
}

void suffix_tree::dfs() { dfs(root, ""); }

bool suffix_tree::contains(string s) {
    node* cur = root;
    int i = 0;
    while (i < s.size()) {
        char ch = s[i];
        node* child = cur->childAt(ch);
        if (child == NULL) return false;
        int j = 0;
        while (i < s.size() && j < child->getEdgeLen()) {
            if (s[i] != getChar(child->start + j)) return false;
            i++;
            j++;
        }
        if (i == s.size()) return true;
        cur = child;
    }
    return false;
}

vector<int> suffix_tree::getAllOccurences(string s) {
    node* cur = root;
    int i = 0;
    while (i < s.size()) {
        char ch = s[i];
        node* child = cur->childAt(ch);
        if (child == NULL) return {};
        int j = 0;
        while (i < s.size() && j < child->getEdgeLen()) {
            if (s[i] != getChar(child->start + j)) return {};
            i++;
            j++;
        }
        if (i == s.size()) return bfs(child, s.size());
        cur = child;
    }
    return {};
}

void suffix_tree::dfs(node* root, string path_to_parent) {
    if (root == NULL) return;
    string path = path_to_parent + s.substr(root->start, root->getEdgeLen());
    for (node* child : root->children) {
        dfs(child, path);
    }
    if (root->end == LAST_POS) {
        cout << path << endl;
    }
}

void suffix_tree::dfs(node* root, string path_to_parent, vector<int>& res) {
    if (root == NULL) return;
    string path = path_to_parent + s.substr(root->start, root->getEdgeLen());
    for (node* child : root->children) {
        dfs(child, path, res);
    }
    if (root->end == LAST_POS) {
        res.push_back(cur_len - path.size());
    }
}

vector<int> suffix_tree::bfs(node* root, int len) {
    vector<int> res;
    queue<pair<node*, int>> q;
    q.push({root, len});

    unordered_map<node*, bool> mark;

    mark[root] = mark[0] = true;

    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        if (p.first == nullptr) continue;
        if (p.first->end == LAST_POS) {
            // cout << cur_len << ' ' << p.second << endl;
            res.push_back(cur_len - p.second);
            continue;
        }
        for (node* child : p.first->children)
            if (!mark[child]) {
                mark[child] = true;
                q.push({child, p.second + child->getEdgeLen()});
            }
    }

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    freopen(".inp", "r", stdin);
    freopen(".out", "w", stdout);
    string s, t;
    getline(cin, s, '\n');
    getline(cin, t, '\n');
    // cout << s.size() << " " << t.size() << endl;
    suffix_tree stree(s);
    vector<int> res = stree.getAllOccurences(t);
    cout << res.size() << endl;
    sort(res.begin(), res.end());
    for (int i : res) cout << i + 1 << " ";
    // cout << "done" << endl;
    return 0;
}
