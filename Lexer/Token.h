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
    BRACKET,
    OPERATOR
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

enum class OperatorType {
    ASSIGNMENT,
    MATH,
    BITWISE,
    COMPARISON,
    LOGIC,
    INCREMENT_DECREMENT,
    TERNARY
};

struct TokenBase { std::string string; int column; };

struct KeywordToken : public TokenBase { KeywordType type; };

typedef TokenBase StringToken;

struct NumberToken : public TokenBase { Number number;  };

typedef TokenBase IdentifierToken;

struct BracketToken : public TokenBase { bool opening; };

struct SeparatorToken : public TokenBase { SeparatorType type; };

struct OperatorToken : public TokenBase { OperatorType type; };


struct Token {
    TokenBase *val;
    TokenType type;

    std::string toString() {
        switch (type) {
            case TokenType::STRING:
                return "\"" + val->string + "\"";
            default:
                return val->string;
        }
    }
};

struct TokenizedLine
{
    std::vector<Token> tokens;
    int lineNum;
};

#endif //G_TOKEN_H