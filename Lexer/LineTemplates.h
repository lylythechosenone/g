#include "../Lexer/Token.h"

#ifndef G_LINETEMPLATES_H
#define G_LINETEMPLATES_H

class LineTemplate
{
public:
    virtual ~LineTemplate() = default;
    virtual bool matches(TokenizedLine line) = 0;
};

class ForTemplate : public LineTemplate
{
    bool matches(TokenizedLine line) override
    {
        if (line.tokens[0].type == TokenType::KEYWORD && line.tokens[0].data["string"].getString() == "for")
        {

        }
    }
};

#endif //G_LINETEMPLATES_H
