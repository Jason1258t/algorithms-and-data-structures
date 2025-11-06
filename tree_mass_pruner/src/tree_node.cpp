#include "tree_node.hpp"
#include <iostream>

TreeNode::TreeNode(NodeType t, int w, std::string n) 
    : type(t), name(n), weight(w), maxValidWeight(std::numeric_limits<int>::max()) {} 

void TreeNode::pruneANDNode()
{
    std::cout << "pruning AND node "<< name << " with max valid weight " << maxValidWeight << '\n';
    int minLayerWeight = getMinTotalWeight() - weight;
    std::cout << "min layer weight " << minLayerWeight << '\n';
    for (auto &child : children)
    {
        int maxChildWeight = maxValidWeight - weight - (minLayerWeight - child->getMinTotalWeight());
        if (child->getMinTotalWeight() <= maxChildWeight)
        {
            child->setMaxValidWeight(maxChildWeight);
            child->pruneInvalidChildren();
        } else {
            throw std::runtime_error("Cannot prune node: " + name);
        }
    }
}

void TreeNode::pruneORNode()
{
    std::vector<std::unique_ptr<TreeNode>> newChildren;
    std::cout << "pruning OR node "<< name << " with max valid weight " << maxValidWeight << '\n';
    for (auto &child : children)
    {
        if (child->getMinTotalWeight() <= maxValidWeight)
        {
            child->setMaxValidWeight(maxValidWeight - weight);
            child->pruneInvalidChildren();
            newChildren.push_back(std::move(child));
        } else {
            std::cout << "removed node " << name << '\n';
        }
    }

    children = std::move(newChildren);
}

void TreeNode::setMaxValidWeight(int maxWeight)
{
    maxValidWeight = maxWeight;
}

bool TreeNode::pruneInvalidChildren()
{
    if (getMinTotalWeight() > maxValidWeight)
        return false;

    if (type == NodeType::AND)
    {
        pruneANDNode();
        return true;
    }

    pruneORNode();
    return true;
}

void TreeNode::addChild(std::unique_ptr<TreeNode> child)
{
    children.push_back(std::move(child));
}

int TreeNode::getMinTotalWeight() const
{
    if (type == NodeType::AND)
    {
        int childrenSum = 0;
        for (const auto &child : children)
        {
            childrenSum += child->getMinTotalWeight();
        }
        return childrenSum + weight;
    }
    else
    {
        if (children.empty())
            return weight;

        auto min_child = std::min_element(children.begin(), children.end(),
                                          [](const std::unique_ptr<TreeNode> &a,
                                             const std::unique_ptr<TreeNode> &b)
                                          {
                                              return a->getMinTotalWeight() < b->getMinTotalWeight();
                                          });

        return (*min_child)->getMinTotalWeight() + weight;
    }
}

int TreeNode::getMaxTotalWeight() const
{
    if (type == NodeType::AND)
    {
        int childrenSum = 0;
        for (const auto &child : children)
        {
            childrenSum += child->getMaxTotalWeight();
        }
        return childrenSum + weight;
    }
    else
    {
        if (children.empty())
            return weight;

        auto max_child = std::max_element(children.begin(), children.end(),
                                          [](const std::unique_ptr<TreeNode> &a,
                                             const std::unique_ptr<TreeNode> &b)
                                          {
                                              return a->getMaxTotalWeight() < b->getMaxTotalWeight();
                                          });

        return (*max_child)->getMaxTotalWeight() + weight;
    }
}