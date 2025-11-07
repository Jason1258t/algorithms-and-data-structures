#include "tree_node.hpp"
#include "tree_parser.hpp"
#include "tree_visualizer.hpp"
#include <iostream>
#include <fstream>

// Домогацкий Иван ПС-22

// Среда выполнения:
// Apple clang version 16.0.0 (clang-1600.0.26.3)
// Target: arm64-apple-darwin24.6.0
// Thread model: posix

// 24. В   листьях   И-ИЛИ   дерева,  соответствующего некоторому
// множеству  конструкций,  заданы   значения   массы.   Известно
// максимально допустимое значение массы изделия. Требуется усечь
// дерево   так,   чтобы   дерево    включало    все    элементы,
// соответствующие  допустимым  значениям массы,  но не содержало
// "лишних" вершин.  Конечное дерево выдать на экран в  наглядном
// виде (12).

std::ifstream openFile(int argc, char *argv[])
{
    std::string filename;

    if (argc > 1)
    {
        filename = argv[1];
    }
    else
    {
        std::cout << "Enter filename: ";
        std::getline(std::cin, filename);
    }

    if (filename.empty())
    {
        throw std::runtime_error("Error: Filename cannot be empty!");
    }

    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Error: Cannot open file '" + filename + "'!");
    }

    std::cout << "File '" << filename << "' opened successfully!" << std::endl;
    return file;
}

int main(int argc, char *argv[])
{
    std::ifstream file = openFile(argc, argv);
    auto tree = TextTreeParser::parse(file);
    std::cout << "=== Original Tree ===" << std::endl;
    TreeVisualizer::printTree(tree.get());

    std::cout << "Enter max weight: ";
    int weight;
    std::cin >> weight;
    std::cout << '\n';

    tree->setMaxValidWeight(weight);
    tree->pruneInvalidChildren();
    
    std::cout << '\n';
    TreeVisualizer::printTree(tree.get());
}