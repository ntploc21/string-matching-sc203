#include <bits/stdc++.h>
#include "./src/boyer_moore.h"
using namespace std;

int main() {
    Boyer_Moore bm("ababaca");
    vector<int> result = bm.search("abababacaba");
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    cout << endl;
    return 0;
}