#include "turbo_bm.h"

void turbo_boyer_moore::calculateSuffix(std::vector<int>& suffix) {
    int patternSize = int(pattern.size());
    suffix.assign(patternSize, 0);
    suffix[patternSize - 1] = patternSize;

    int f = 0, g = patternSize - 1;
    for (int i = patternSize - 2; i >= 0; --i) {
        if (i > g && suffix[i + patternSize - 1 - f] < i - g)
            suffix[i] = suffix[i + patternSize - 1 - f];
        else {
            if (i < g)
                g = i;
            f = i;
            while (g >= 0 && pattern[g] == pattern[g + patternSize - 1 - f])
                --g;
            suffix[i] = f - g;
        }
    }
}

void turbo_boyer_moore::precompute_bad_char() {
    int patternSize = int(pattern.size());
    bad_char.assign(256, patternSize);
    for (int i = 0; i < patternSize - 1; ++i)
        bad_char[int(pattern[i])] = patternSize - i - 1;
}

void turbo_boyer_moore::precompute_good_suffix() {
    int patternSize = int(pattern.size());
    std::vector<int> suffix;
    calculateSuffix(suffix);
    good_suffix.assign(patternSize, patternSize);

    int j = 0;
    for (int i = patternSize - 1; i >= 0; --i) {
        if (suffix[i] == i + 1) {
            for (; j < patternSize - 1 - i; ++j)
                if (good_suffix[j] == patternSize)
                    good_suffix[j] = patternSize - 1 - i;
        }
    }

    for (int i = 0; i <= patternSize - 2; ++i)
        good_suffix[patternSize - 1 - suffix[i]] = patternSize - 1 - i;
}

turbo_boyer_moore::turbo_boyer_moore() {
    pattern = "";
    // precompute_bad_char();
    // precompute_good_suffix();
}

turbo_boyer_moore::turbo_boyer_moore(const std::string& pattern) {
    this->pattern = pattern;
    precompute_bad_char();
    precompute_good_suffix();
}

turbo_boyer_moore::~turbo_boyer_moore() {
    clear();
}

void turbo_boyer_moore::setPattern(const std::string& pattern) {
    this->pattern = pattern;
    precompute_bad_char();
    precompute_good_suffix();
}

void turbo_boyer_moore::clear() {
    this->pattern = "";
    bad_char.clear();
    good_suffix.clear();
}

std::vector<int> turbo_boyer_moore::search(const std::string& text) {
    int i, j, u, v, shift, turboShift;
    int patternSize = int(pattern.size());
    int textSize = int(text.size());

    std::vector<int> result;

    j = u = 0;
    shift = patternSize;
    while (j <= textSize - patternSize) {
        i = patternSize - 1;

        while (i >= 0 && pattern[i] == text[i + j]) {
            --i;
            if (u != 0 && i == patternSize - 1 - shift)
                i -= u;
        }

        if (i < 0) {
            result.push_back(j);
            shift = good_suffix[0];
            u = patternSize - shift;
        }
        else {
            v = patternSize - 1 - i;
            turboShift = u - v;
            int bcShift = bad_char[int(text[i + j])] - patternSize + 1 + i;
            shift = std::max(turboShift, bcShift);
            shift = std::max(shift, good_suffix[i]);

            if (shift == good_suffix[i])
                u = std::min(patternSize - shift, v);
            else {
                if (turboShift < bcShift)
                    shift = std::max(shift, u + 1);
                u = 0;
            }
        }

        j += shift;
    }

    return result;
}



