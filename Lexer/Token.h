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

enum class KeywordType {
    INCLUDE,
    IF,
    LOOP_BEGIN,
    LOOP_UTIL,
    SWITCH,
    TYPE,
    PRE_PROCESSOR,
    CLASS,
    ACCESS_MODIFIER,
    MODIFIER,
    MISC
};

enum class SeparatorType {
    COLON,
    COMMA
};

struct TokenBase { std::string string; TokenBase() {} };

struct KeywordToken : public TokenBase { KeywordType type; };

typedef TokenBase StringToken;

struct NumberToken : public TokenBase { Number number;  };

typedef TokenBase IdentifierToken;

struct BracketToken : public TokenBase { bool opening; };

struct SeparatorToken : public TokenBase { SeparatorType type; };


struct Token {
    TokenBase *val;
    TokenType type;
};

struct TokenizedLine
{
    std::vector<Token> tokens;
    int lineNum;
};

#endif //G_TOKEN_H