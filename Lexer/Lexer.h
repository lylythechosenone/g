#include <fstream>

#include "Token.h"
#include "../DataStream.h"
#include "../Util.h"
#include "../g.h"

#ifndef G_LEXER_H
#define G_LEXER_H

class LexDataStream: public DataStreamBase<TokenizedLine>
{
public:
    explicit LexDataStream(std::ifstream *stream)
    {
        this->stream = stream;
        stream->seekg(0, std::ios::end);
        fileLength = stream->tellg();
        stream->seekg(0, std::ios::beg);
    }

    static void endToken(TokenizedLine &line, std::string &tokenStr)
    {
        if (tokenStr == "") return;
        Token token;
        if (Util::isNumber(tokenStr))
        {
            token.type = TokenType::NUMBER;
            token.data["number"] = Number(tokenStr);
        } else if (Util::includes(G::keywords, tokenStr))
        {
            token.type = TokenType::KEYWORD;
        } else
        {
            token.type = TokenType::IDENTIFIER;
        }
        token.data["string"] = tokenStr;
        line.tokens.push_back(token);
        tokenStr = "";
    }

    TokenizedLine get() override
    {
        TokenizedLine toReturn;

        while (toReturn.tokens.size() == 0)
        {
            lineNum++;
            toReturn.lineNum = lineNum;

            std::string tokenStr;

            bool inString = false;
            while (true)
            {
                const char chr = stream->get();
                if (chr == '\n') break;
                if (inString)
                {
                    if (chr == '"')
                    {
                        inString = false;
                        Token token;
                        token.type = TokenType::STRING;
                        token.data["string"] = tokenStr;
                        toReturn.tokens.push_back(token);
                        tokenStr = "";
                        continue;
                    }
                    tokenStr += chr;
                    continue;
                }

                if (chr == ' ')
                {
                    endToken(toReturn, tokenStr);
                    continue;
                } if (chr == '(' || chr == ')' || chr == '[' || chr == ']' || chr == '{' || chr == '}')
                {
                    endToken(toReturn, tokenStr);
                    Token token;
                    token.type = TokenType::BRACKET;
                    token.data["string"] = chr;
                    if (chr == '(' || chr == '[' || chr == '{')
                    {
                        token.data["opening"] = true;
                    } else
                    {
                        token.data["opening"] = false;
                    }
                    toReturn.tokens.push_back(token);
                    continue;
                } if (chr == '"')
                {
                    endToken(toReturn, tokenStr);
                    inString = true;
                    continue;
                }
                tokenStr += chr;
            }
            endToken(toReturn, tokenStr);
        }
        return toReturn;
    }

    bool done() override
    {
        return (size_t)stream->tellg() + 1 == fileLength;
    }

private:
    std::ifstream *stream;
    int lineNum = 0;

    size_t fileLength;
};

class Lexer
{
public:
    inline static DataStreamBase<TokenizedLine> *stream = nullptr;

    static void cleanUp()
    {
        delete stream;
    }

    static DataStream<TokenizedLine> lex(std::ifstream *strm)
    {
        stream = new LexDataStream(strm);
        return DataStream(Lexer::stream);
    }
};

#endif //G_LEXER_H
