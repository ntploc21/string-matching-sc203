#include <bits/stdc++.h>
#include "./src/boyer_moore.h"
using namespace std;

void parseArgs(int argc, char const* argv[]) {
    // If help
    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-?") == 0)) {
        cout << "Usage: " << argv[0] << " [PATTERN] [TEXT]" << endl;
        cout << "Example: " << argv[0] << " \"abc\" \"abcabc\"" << endl;
        exit(0);
    }

    // If not enough arguments
    if (argc < 3) {
        cerr << "Error: Not enough arguments" << endl;
        cerr << "Usage: " << argv[0] << " [PATTERN] [TEXT]" << endl;
        cerr << "Example: " << argv[0] << " \"abc\" \"abcabc\"" << endl;
        exit(1);
    }
}

int main(int argc, char const* argv[]) {
    parseArgs(argc, argv);

    string pattern = argv[1];
    string text = argv[2];

    Boyer_Moore bm(pattern);
    vector<int> result = bm.search(text);

    cout << "Pattern: " << pattern << endl;
    cout << "Text: " << text << endl;

    if (result.size() == 0)
        cout << "Pattern not found" << endl;
    else {
        cout << "Pattern found at index: ";
        for (int i = 0; i < result.size(); i++)
            cout << result[i] << " ";
        cout << endl;
    }

    return 0;
}