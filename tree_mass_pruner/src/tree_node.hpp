#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <limits>  

enum class NodeType
{
    AND,
    OR
};

class TreeNode
{
private:
    NodeType type;
    std::string name;  
    int weight;
    std::vector<std::unique_ptr<TreeNode>> children;
    int maxValidWeight;

    void pruneANDNode();
    void pruneORNode();

public:
    TreeNode(NodeType t, int w, std::string n);

    void setMaxValidWeight(int maxWeight);
    bool pruneInvalidChildren();

    NodeType getType() const { return type; }
    const std::string &getName() const { return name; }
    const std::vector<std::unique_ptr<TreeNode>> &getChildren() const { return children; }
    int getOwnNodeWeight() const { return weight; }

    void addChild(std::unique_ptr<TreeNode> child);

    int getMinTotalWeight() const;
    int getMaxTotalWeight() const;
};
