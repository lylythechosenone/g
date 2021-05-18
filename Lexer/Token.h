#include <vector>
#include <map>

#include "../Value.h"

#ifndef G_TOKEN_H
#define G_TOKEN_H

enum class TokenType
{
    KEYWORD,
    STRING,
    NUMBER,
    IDENTIFIER,
    BRACKET
};

struct Token
{
    TokenType type;
    std::map<std::string, Value> data;
};

struct TokenizedLine
{
    std::vector<Token> tokens;
    int lineNum;
};

#endif //G_TOKEN_H
