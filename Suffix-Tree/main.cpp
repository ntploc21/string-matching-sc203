// On–line construction of suffix trees
// https://www.cs.helsinki.fi/u/ukkonen/SuffixT1withFigs.pdf

#include <bits/stdc++.h>

#include "SuffixTree.h"

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
