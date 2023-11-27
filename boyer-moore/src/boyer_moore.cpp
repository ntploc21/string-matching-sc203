#include "boyer_moore.h"

Boyer_Moore::Boyer_Moore() {
    this->pattern = "";
}

/// @brief Intialize Boyer_Moore with pattern string
/// @param pattern 
Boyer_Moore::Boyer_Moore(const std::string& pattern) {
    this->pattern = pattern;
    preBadChar(pattern);
    preGoodSuffix(pattern);
}

Boyer_Moore::~Boyer_Moore() {
    this->pattern = "";
    this->badChar.clear();
    this->goodSuffix.clear();
}

/// @brief Set pattern string
/// @param pattern 
void Boyer_Moore::setPattern(const std::string& pattern) {
    this->pattern = pattern;
    preBadChar(pattern);
    preGoodSuffix(pattern);
}

/// @brief Precalculate bad character table
/// @param pattern 
/// The bad character heuristic is used to skip unnecessary comparisons when a mismatch is detected.
/// It stores the maximum shift for each character, if the character is not present in the pattern, then value is -1.
void Boyer_Moore::preBadChar(std::string pattern) {
    int patternLength = pattern.length();
    this->badChar.assign(256, -1);

    for (int i = 0; i < patternLength - 1; i++)
        this->badChar[int(pattern[i])] = i;
}

/// @brief Precalculate good suffix table
/// @param pattern 
/// The good suffix heuristic is used to determine the maximum shift when a mismatch occurs based on the suffix of the pattern.
/// goodSuffix stores maximum shift for each possible shift value.
void Boyer_Moore::preGoodSuffix(std::string pattern) {
    // Initialize goodSuffix with 0
    int patternLength = pattern.length();
    this->goodSuffix.assign(patternLength, -1);
    this->isPrefix.assign(patternLength, false);

    for (int i = 0, j, k; i < patternLength - 1; i++) {
        j = i;
        k = 0;
        while (j >= 0 && pattern[j] == pattern[patternLength - k - 1])
            this->goodSuffix[++k] = (--j) + 1;

        if (j < 0)
            this->isPrefix[k] = true;
    }
}

/// @brief Move by good suffix
/// @param index - index of mismatched character
/// @param patternLength - length of pattern string
/// @return int - shift value
/// It takes the current position of the mismatch (index) and the length of the pattern (patternLength).
/// If there is a good suffix match, it returns the appropriate shift; otherwise, it returns 1.
int Boyer_Moore::moveByGoodSuffix(int index, int patternLength) {
    int suffixLength = patternLength - index - 1;

    // If there is a good suffix match
    if (this->goodSuffix[suffixLength] != -1)
        return index - this->goodSuffix[suffixLength] + 1;

    // If there is a prefix match
    for (int i = index + 2; i < patternLength; i++) {
        if (this->isPrefix[patternLength = i])
            return i;
    }

    return patternLength;
}

std::vector<int> Boyer_Moore::search(const std::string& text) {
    // If pattern is empty, return empty vector
    if (this->pattern.length() == 0)
        return std::vector<int>();

    // Initialize variables
    int textLength = text.length();
    int patternLength = this->pattern.length();
    std::vector<int> result;
    int i = 0; // index of text

    // This loop iterates through the text until the end of the text minus the length
    // of the pattern. It performs the main steps of the Boyer-Moore algorithm
    while (i <= textLength - patternLength) {
        // Start from the end of the pattern
        int j = patternLength - 1;

        // Find the index of first mismatched character
        while (j >= 0 && this->pattern[j] == text[i + j])
            j--;

        // If there is no mismatch, then we have found a match
        if (j < 0) {
            result.push_back(i);
            i += moveByGoodSuffix(0, patternLength);
        }
        else {
            // Otherwise, we shift the pattern to the right by the maximum of the bad character
            // j - this->badChar[int(text[i + j])] is the shift value for the bad character heuristic
            // The max function is used to ensure that we shift at least one position
            i += std::max(1,
                j - this->badChar[int(text[i + j])]
            );
        }
    }

    return result;
}