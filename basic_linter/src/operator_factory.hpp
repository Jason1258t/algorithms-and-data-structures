#pragma once

#include "operator.hpp"
#include <string>
#include <unordered_map>
#include <stdexcept>

class OperatorFactory
{
private:
    std::unordered_map<std::string, Operator> operatorTemplates;
    void initializeTemplates();

public:
    OperatorFactory();
    
    void registerTemplate(const Operator& opTemplate);
    
    Operator createFromChar(char startChar, int line = 0, int column = 0) const;
    Operator createFromString(const std::string& startToken, int line = 0, int column = 0) const;
    
    bool hasOperator(const std::string& startToken) const;
    bool hasOperator(char startChar) const;
    
    bool isClosingToken(const std::string& token) const;
};