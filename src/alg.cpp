// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include <cctype>
#include <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не могу открыть файл " << filename << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            word.push_back(tolower(ch));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {

    std::ofstream outFile("result/freq.txt");

    tree.printByFrequency(std::cout);
    tree.printByFrequency(outFile);

    outFile.close();
}
