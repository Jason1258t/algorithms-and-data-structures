#pragma once

#include <string>

enum class ContentType
{
    NORMAL,
    PLAIN_TEXT
};

struct Operator
{
    std::string name;
    std::string startToken;
    std::string closeToken;
    ContentType contentType;
    bool allowsMultiline;
    int line;
    int column;

    Operator() 
        : name(""), startToken(""), closeToken(""), 
          contentType(ContentType::NORMAL), allowsMultiline(false),
          line(0), column(0) {}

    Operator(const std::string &n, const std::string &st, const std::string &ct,
             ContentType ct_type, bool multiline, int ln = 0, int col = 0)
        : name(n), startToken(st), closeToken(ct), contentType(ct_type),
          allowsMultiline(multiline), line(ln), column(col) {}
};
