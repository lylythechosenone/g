#include <fstream>

#include "Token.h"
#include "../DataStream.h"
#include "../Util.h"
#include "../g.h"

#ifndef G_LEXER
#define G_LEXER

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
        if (Util::isNumber(tokenStr))
        {
            NumberToken *token = new NumberToken();
            token->string = tokenStr;
            token->number = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::NUMBER;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::includeKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::INCLUDE;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::ifKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::IF;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::loopBeginKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::LOOP_BEGIN;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::loopUtilKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::LOOP_UTIL;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::switchKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::SWITCH;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::typeKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::TYPE;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::preProcessorKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::PRE_PROCESSOR;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::classKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::CLASS;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::accessModifierKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::ACCESS_MODIFIER;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::modifierKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::MODIFIER;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else if (Util::includes(G::miscKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::MISC;
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
        } else
        {
            IdentifierToken *token = new IdentifierToken();
            token->string = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::IDENTIFIER;
            line.tokens.push_back(toReturn);

        }
        tokenStr = "";
    }

    TokenizedLine get() override
    {
        TokenizedLine toReturn;

        lineNum++;
        toReturn.lineNum = lineNum;

        std::string tokenStr;

        bool inString = false;
        while (true)
        {
            const char chr = stream->get();
            if (chr == '\n' || chr == -1) break;
            if (inString)
            {
                if (chr == '"')
                {
                    inString = false;
                    StringToken *token = new StringToken();
                    token->string = tokenStr;
                    Token tokenWrapper;
                    tokenWrapper.val = token;
                    tokenWrapper.type = TokenType::STRING;
                    toReturn.tokens.push_back(tokenWrapper);
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
                BracketToken *token = new BracketToken();
                token->string = tokenStr;
                if (chr == '(' || chr == '[' || chr == '{')
                {
                    token->opening = true;
                } else
                {
                    token->opening = false;
                }
                Token tokenWrapper;
                tokenWrapper.val = token;
                tokenWrapper.type = TokenType::BRACKET;
                toReturn.tokens.push_back(tokenWrapper);
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

        return toReturn;
    }

    bool done() override
    {
        return (size_t)stream->tellg() >= fileLength;
    }

    bool doneNow() override {
        return (size_t)stream->tellg() - 1 >= fileLength;
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

#endif // G_LEXER
