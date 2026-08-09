#include <iostream>
#include "binarySearchTree.h"   

int main() {
    BinarySearchTree<std::string> words;

    words.insert("apple");
    words.insert(std::string("banana"));
    words.insert("cherry");

    if (auto result = words.find("banana")) {
        std::cout << "Found: " << *result << '\n';
    } else {
        std::cout << "Not found\n";
    }

    words.remove("apple");

    std::cout << "Inorder: ";
    for (const auto& w : words.inorder())
        std::cout << w << ' ';
    std::cout << '\n';

    return 0;
}