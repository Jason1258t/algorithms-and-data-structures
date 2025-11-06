#pragma once

#include <memory>
#include <string>
#include "tree_node.hpp"

class ITreeParser
{
public:
    virtual ~ITreeParser() = default;
    static std::unique_ptr<TreeNode> parse(std::ifstream &file);
};

class TextTreeParser : public ITreeParser
{
public:
    static std::unique_ptr<TreeNode> parse(std::ifstream &file);
};
