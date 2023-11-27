#include "../../kmp/kmp.hpp"
#include "../../aho-corasick/aho_corasick.hpp"
#include "../../boyer-moore/src/boyer_moore.h"
#include "../../rabin-karp/rabin_karp.hpp"
#include "../../Suffix-Tree/SuffixTree.h"

#include <iostream>
#include <chrono>
#include <string>

const std::vector<std::string> paths = {
    "./keywords-1000-one-input-1000",
    "./keywords-1000-one-input-100000",
    "./keywords-1000-multiple-input-1000",
    "./keywords-1000-multiple-input-100000"
    };

int main()
{
    std::ofstream fout("results.txt");
    for (int i = 0; i < paths.size(); i++)
    {
        int numTest = 1;
        std::string path = paths[i];
        int averageTime[5] = {0};
        while (true)
        {
            std::vector<std::string> patterns;
            std::vector<std::string> texts;
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
            int numText;
            file >> numText;
            for (int i = 0; i < numText; i++)
            {
                std::string text;
                file >> text;
                texts.push_back(text);
            }
            file.close();
            // KMP
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < numPattern; i++)
            {
                KMP kmp(patterns[i]);
                for (int j = 0; j < numText; j++)
                {
                    kmp.search(texts[j], patterns[i]);
                }
                auto timeout = std::chrono::high_resolution_clock::now();
                if (timeout - start > std::chrono::seconds(5))
                {   
                    break;
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[0] += duration.count();
            // Aho-Corasick
            start = std::chrono::high_resolution_clock::now();
            aho_corasick::AhoCorasick ahoCorasick;
            for (int i = 0; i < numPattern; i++)
            {
                ahoCorasick.add_string(patterns[i]);
            }
            int v = 0;
            for (int i = 0; i < numText; i++)
            {
                for (int j = 0; j < texts[i].size(); ++j)
                {
                    v = ahoCorasick.go(v, texts[i][j]);
                }
                auto timeout = std::chrono::high_resolution_clock::now();
                if (timeout - start > std::chrono::seconds(5))
                {
                    break;
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
                for (int j = 0; j < numText; j++)
                {
                    boyerMoore.search(texts[j]);
                }
                auto timeout = std::chrono::high_resolution_clock::now();
                if (timeout - start > std::chrono::seconds(5))
                {
                    break;
                }
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[2] += duration.count();
            // Rabin-Karp
            start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < numPattern; i++)
            {
                for (int j = 0; j < numText; j++)
                {
                    rabin_karp::rabin_karp(patterns[i], texts[j]);
                }
                auto timeout = std::chrono::high_resolution_clock::now();
                if (timeout - start > std::chrono::seconds(5))
                {
                    break;
                }
            }
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            averageTime[3] += duration.count();
            // Suffix-Tree
            start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < numText; i++)
            {
                suffix_tree suffixTree(texts[i]);
                for (int j = 0; j < numPattern; j++)
                {   
                    suffixTree.contains(patterns[j]);
                }
                auto timeout = std::chrono::high_resolution_clock::now();
                if (timeout - start > std::chrono::seconds(5))
                {
                    break;
                }
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