#pragma once

#include <memory>
#include <string>
#include "tree_node.hpp"

class ITreeParser
{
public:
    virtual ~ITreeParser() = default;
    virtual std::unique_ptr<TreeNode> parse(const std::string &input) = 0;
};

class TextTreeParser : public ITreeParser
{
public:
    std::unique_ptr<TreeNode> parse(const std::string &filename) override;
};
