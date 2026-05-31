// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не могу открыть файл " << filename << std::endl;
        return;
    }

    std::vector<std::string> words;
    std::string word;
    char ch;

    while (file.get(ch)) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            word.push_back(tolower(ch));
        } else {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }

    file.close();

    std::shuffle(words.begin(), words.end(), std::mt19937(std::random_device()()));

    for (const auto& w : words) {
        tree.insert(w);
    }
}

void printFreq(BST<std::string>& tree) {
    std::ofstream outFile("result/freq.txt");

    tree.printByFrequency(std::cout);
    tree.printByFrequency(outFile);

    outFile.close();
}
