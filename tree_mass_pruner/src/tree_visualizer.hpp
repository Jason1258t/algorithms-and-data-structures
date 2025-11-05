#include <iostream>
#include "tree_node.hpp"

class TreeVisualizer
{
public:
    static void printTree(const TreeNode *node, int depth = 0)
    {
        std::string indent(depth * 2, ' ');
        std::cout << indent
                  << (node->getType() == NodeType::AND ? "AND" : "OR")
                  << " \"" << node->getName() << "\" (" << node->getOwnNodeWeight() << ")";

        if (!node->getChildren().empty())
        {
            std::cout << " [min:" << node->getMinTotalWeight()
                      << ", max:" << node->getMaxTotalWeight() << "]";
        }
        std::cout << std::endl;

        for (const auto &child : node->getChildren())
        {
            printTree(child.get(), depth + 1);
        }
    }
};