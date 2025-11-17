#pragma once

#include "operator_factory.hpp"
#include "logger.hpp"
#include "parse_error.hpp"
#include "stack.hpp"
#include <string>

class Tokenizer
{
private:
    OperatorFactory &factory;
    SimpleStack<Operator> stack;
    Logger &logger;

    bool isWordDelimiter(char c)
    {
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_')
        {
            return false;
        }
        return true;
    }

    void addOperator(const Operator &op)
    {
        if (!stack.empty())
        {
            auto lastOp = stack.top();
            if (op.nestingType == NestingType::FORBIDDEN || (op.nestingType == NestingType::ONLY_THIS && lastOp.name != op.name))
            {
                throw ParserError("Ошибка вложенности операторов: " + op.name + " вложен в " + lastOp.name);
            }
        }
        stack.push(op);
    }

    void processWordToken(std::string &token, int lineNumber, int pos)
    {
        if (token.empty())
            return;

        logger.log("TOKEN(word): " + token + "  (line " + std::to_string(lineNumber) + ")");

        if (factory.hasOperator(token))
        {
            Operator op = factory.createFromString(token, lineNumber, pos);
            logger.log("  -> Open operator '" + op.name +
                       "' (start='" + op.startToken + "') at line " + std::to_string(lineNumber));
            addOperator(op);
        }
        else if (factory.isClosingToken(token))
        {
            if (stack.empty())
            {
                throw ParserError("Unexpected closing '" + token + "' at line " + std::to_string(lineNumber));
            }
            if (stack.top().closeToken != token)
            {
                throw ParserError("Mismatched closing '" + token + "' expected '" +
                                  stack.top().closeToken + "' opened at line " +
                                  std::to_string(stack.top().line));
            }
            stack.pop();
        }
        token.clear();
    }

    void processCharToken(char c, const std::string &line, int lineNumber, size_t &i)
    {
        if (factory.hasOperator(c))
        {
            Operator op = factory.createFromChar(c, lineNumber, static_cast<int>(i));
            logger.log("TOKEN(single): '" + std::string(1, c) + "'  -> ");

            if (op.contentType == ContentType::PLAIN_TEXT || op.allowsMultiline)
            {
                logger.log("open operator '" + op.name + "' at line " + std::to_string(lineNumber));
                addOperator(op);
            }
            else
            {
                logger.log("operator '" + op.name + "' (treat as close?)");
                std::string strCh = std::string(1, c);
                if (factory.isClosingToken(strCh))
                {
                    if (stack.empty())
                    {
                        throw ParserError("Unexpected closing '" + strCh + "' at line " + std::to_string(lineNumber));
                    }
                    if (stack.top().closeToken != strCh)
                    {
                        throw ParserError("Mismatched closing '" + strCh + "' expected '" +
                                          stack.top().closeToken + "' opened at line " +
                                          std::to_string(stack.top().line));
                    }
                    stack.pop();
                }
            }
            return;
        }

        // двухсимвольные операторы
        if (i + 1 < line.size())
        {
            char c2 = std::tolower(line[i + 1]);
            std::string two(1, c);
            two += c2;
            if (factory.hasOperator(two))
            {
                Operator op = factory.createFromString(two, lineNumber, static_cast<int>(i));
                logger.log("TOKEN(multi): '" + two + "' -> open '" + op.name + "' at line " + std::to_string(lineNumber));
                addOperator(op);
                ++i; // пропускаем следующий символ
                return;
            }
        }
    }

    void processEndOfLine(std::string &token, int lineNumber)
    {
        if (!stack.empty() && stack.top().closeToken == "\n")
        {
            logger.log("Closing line-operator opened at line " + std::to_string(stack.top().line) +
                       " at end of line " + std::to_string(lineNumber));
            stack.pop();
        }

        if (!stack.empty() && !stack.top().allowsMultiline)
        {
            throw ParserError("Expected " + stack.top().closeToken + " but found end of line");
        }

        if (!token.empty())
        {
            logger.log("TOKEN(end-line word): " + token + "  (line " + std::to_string(lineNumber) + ")");

            if (factory.hasOperator(token))
            {
                Operator op = factory.createFromString(token, lineNumber, static_cast<int>(token.size() - 1));
                logger.log("  -> Open operator '" + op.name + "' (start='" + op.startToken + "') at line " + std::to_string(lineNumber));
                addOperator(op);
            }
            else if (factory.isClosingToken(token))
            {
                if (stack.empty())
                {
                    throw ParserError("Unexpected closing '" + token + "' at line " + std::to_string(lineNumber));
                }
                if (stack.top().closeToken != token)
                {
                    throw ParserError("Mismatched closing '" + token + "' expected '" +
                                      stack.top().closeToken + "' opened at line " +
                                      std::to_string(stack.top().line));
                }
                stack.pop();
            }
            token.clear();
        }
    }

public:
    Tokenizer(OperatorFactory &factory, Logger &logger)
        : factory{factory}, logger{logger} {}

    void processLine(const std::string &line, int lineNumber)
    {
        std::string token;

        for (size_t i = 0; i < line.size(); ++i)
        {
            char c = std::tolower(line[i]);

            if (!stack.empty() && stack.top().contentType == ContentType::PLAIN_TEXT)
            {
                const std::string &closeTok = stack.top().closeToken;
                if (closeTok == "\n")
                {
                    break;
                }

                if (line.compare(i, closeTok.size(), closeTok) == 0)
                {
                    i += closeTok.size() - 1;
                    stack.pop();
                }
                continue;
            }

            if (!isWordDelimiter(c))
            {
                token += std::tolower(c);
                continue;
            }

            processWordToken(token, lineNumber, i);
            processCharToken(c, line, lineNumber, i);
        }

        processEndOfLine(token, lineNumber);
    }

    bool hasUnclosedOperators() const
    {
        return !stack.empty();
    }

    Operator getTopUnclosedOperator() const
    {
        return stack.top();
    }
};