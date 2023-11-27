#include "../../kmp/kmp.hpp"
#include "../../aho-corasick/aho_corasick.hpp"
#include "../../boyer-moore/src/boyer_moore.h"
#include "../../rabin-karp/rabin_karp.hpp"
#include "../../Suffix-Tree/SuffixTree.h"

#include <iostream>
#include <chrono>
#include <string>

const std::vector<std::string> paths = {
    "./1",
    "./2",
    "./3",
    "./4",
    "./5"};

int main()
{
    std::ofstream fout("result.txt");
    for (int i = 0; i < paths.size(); i++)
    {
        int numTest = 1;
        std::string path = paths[i];
        int averageTime[5] = {0};
        while (true)
        {
            std::vector<std::string> patterns;
            std::string text;
            std::string filePath = path + "/" + std::to_string(numTest) + ".inp";
            std::ifstream file(filePath);
            if (!file.is_open())
            {
                break;
            }
            int numPattern;
            file >> numPattern;
            for (int i = 0; i < numPattern; i++)
            {
                std::string pattern;
                file >> pattern;
                patterns.push_back(pattern);
            }
            getline(file, text);
            file.close();
            // KMP
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < numPattern; i++)
            {
                KMP kmp(patterns[i]);
                kmp.search(text, patterns[i]);
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[0] += duration.count();
            // Aho-Corasick
            start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < numPattern; i++)
            {
                aho_corasick::AhoCorasick ahoCorasick;
                ahoCorasick.add_string(patterns[i]);
                int v = 0;
                for (int i = 0; i < text.size(); ++i)
                {
                    v = ahoCorasick.go(v, text[i]);
                }
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[1] += duration.count();
            // Boyer-Moore
            start = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < numPattern; i++)
            {
                Boyer_Moore boyerMoore(patterns[i]);
                boyerMoore.search(text);
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[2] += duration.count();
            // Rabin-Karp
            start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < numPattern; i++)
            {
                rabin_karp::rabin_karp(patterns[i], text);
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[3] += duration.count();
            // Suffix-Tree
            start = std::chrono::high_resolution_clock::now();
            suffix_tree suffixTree(text);
            for (int i = 0; i < numPattern; i++)
            {
                suffixTree.contains(patterns[i]);
            }
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