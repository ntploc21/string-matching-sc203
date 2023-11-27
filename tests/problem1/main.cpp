#include "../../kmp/kmp.hpp"
#include "../../aho-corasick/aho_corasick.hpp"
#include "../../boyer-moore/src/boyer_moore.h"
#include "../../rabin-karp/rabin_karp.hpp"
#include "../../Suffix-Tree/SuffixTree.h"

#include <iostream>
#include <chrono>
#include <string>

const std::vector<std::string> paths = {
    "./lim100",
    "./lim1000",
    "./lim5000",
    "./lim10000",
    "./lim100000",
    "./lim500000"
};

int main()
{
    std::ofstream fout("result.txt");
    for (int i = 0; i < paths.size(); i++) {
        int numTest = 1;
        std::string path = paths[i];
        int averageTime[5] = {0};
        while (true) {
            std::string pattern;
            std::string text;
            std::string filePath = path + "/" + std::to_string(numTest) + ".inp";
            std::ifstream file(filePath);
            if (!file.is_open()) {
                break;
            }
            getline(file, pattern);
            getline(file, text);
            file.close();
            // KMP
            auto start = std::chrono::high_resolution_clock::now();
            KMP kmp(pattern);
            kmp.search(text, pattern);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[0] += duration.count();
            // Aho-Corasick
            start = std::chrono::high_resolution_clock::now();
            aho_corasick::AhoCorasick ahoCorasick;
            ahoCorasick.add_string(pattern);
            int v = 0;
            for (int i = 0; i < text.size(); ++i)
            {
                v = ahoCorasick.go(v, text[i]);
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[1] += duration.count();
            // Boyer-Moore
            start = std::chrono::high_resolution_clock::now();
            Boyer_Moore boyerMoore(pattern);
            boyerMoore.search(text);
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[2] += duration.count();
            // Rabin-Karp
            start = std::chrono::high_resolution_clock::now();
            rabin_karp::rabin_karp(pattern, text);
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[3] += duration.count();
            // Suffix-Tree
            start = std::chrono::high_resolution_clock::now();
            suffix_tree suffixTree(text);
            suffixTree.contains(pattern);
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[4] += duration.count();
            numTest++;
        }
        fout << path << std::endl;
        fout << "KMP: " << (float)averageTime[0] / numTest << std::endl;
        fout << "Aho-Corasick: " << (float)averageTime[1] / numTest << std::endl;
        fout << "Boyer-Moore: " << (float)averageTime[2] / numTest << std::endl;
        fout << "Rabin-Karp: " << (float)averageTime[3] / numTest << std::endl;
        fout << "Suffix-Tree: " << (float)averageTime[4] / numTest << std::endl;
    }
    fout.close();
}