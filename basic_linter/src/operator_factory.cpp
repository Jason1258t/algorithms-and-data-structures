#include "operator_factory.hpp"
#include <iostream>

OperatorFactory::OperatorFactory()
{
    initializeTemplates();
}

void OperatorFactory::initializeTemplates()
{
    registerTemplate(Operator("curly_comment", "{", "}", ContentType::PLAIN_TEXT, true));
    
    registerTemplate(Operator("line_comment", "//", "\n", ContentType::PLAIN_TEXT, false));
    
    registerTemplate(Operator("apostrophe_string", "'", "'", ContentType::PLAIN_TEXT, false));
    
    registerTemplate(Operator("begin_end", "begin", "end", ContentType::NORMAL, true));
    
    registerTemplate(Operator("repeat_until", "repeat", "until", ContentType::NORMAL, true));
    
    registerTemplate(Operator("case_end", "case", "end", ContentType::NORMAL, true));

    registerTemplate(Operator("record_end", "record", "end", ContentType::NORMAL, true));
}

void OperatorFactory::registerTemplate(const Operator& opTemplate)
{
    operatorTemplates[opTemplate.startToken] = opTemplate;
}

Operator OperatorFactory::createFromChar(char startChar, int line, int column) const
{
    return createFromString(std::string(1, startChar), line, column);
}

Operator OperatorFactory::createFromString(const std::string& startToken, int line, int column) const
{
    auto it = operatorTemplates.find(startToken);
    if (it != operatorTemplates.end())
    {
        Operator op = it->second;
        op.line = line;
        op.column = column;
        return op;
    }
    throw std::runtime_error("Unknown operator token: '" + startToken + "'");
}

bool OperatorFactory::hasOperator(const std::string& startToken) const
{
    return operatorTemplates.find(startToken) != operatorTemplates.end();
}

bool OperatorFactory::hasOperator(char startChar) const
{
    return hasOperator(std::string(1, startChar));
}

bool OperatorFactory::isClosingToken(const std::string& token) const
{
    for (const auto& pair : operatorTemplates)
    {
        if (pair.second.closeToken == token)
        {
            return true;
        }
    }
    return false;
}