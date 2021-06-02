#include <fstream>

#include "Token.h"
#include "../DataStream.h"
#include "../Util.h"
#include "../g.h"

#include <filesystem>

#define fs std::filesystem

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

    void endToken(TokenizedLine &line, std::string &tokenStr, int column)
    {
        if (tokenStr == "") return;
        if (Util::isNumber(tokenStr))
        {
            NumberToken *token = new NumberToken();
            token->string = tokenStr;
            token->column = column;
            token->number = tokenStr;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::NUMBER;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::includeKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::INCLUDE;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::ifKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::IF;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::loopBeginKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::LOOP_BEGIN;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::loopUtilKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::LOOP_UTIL;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::switchKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::SWITCH;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::typeKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::TYPE;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::preProcessorKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::PRE_PROCESSOR;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::classKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::CLASS;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::accessModifierKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::ACCESS_MODIFIER;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::modifierKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::MODIFIER;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else if (Util::includes(G::miscKeywords, tokenStr))
        {
            KeywordToken *token = new KeywordToken();
            token->type = KeywordType::MISC;
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::KEYWORD;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        } else
        {
            IdentifierToken *token = new IdentifierToken();
            token->string = tokenStr;
            token->column = column;
            Token toReturn;
            toReturn.val = token;
            toReturn.type = TokenType::IDENTIFIER;
            line.tokens.push_back(toReturn);
            tokens.push_back(toReturn);
        }
        tokenStr = "";
    }

    TokenizedLine get() override
    {
        TokenizedLine toReturn;

        lineNum++;
        toReturn.lineNum = lineNum;

        std::string tokenStr;

        int column = 0;
        bool inString = false;
        while (toReturn.tokens.size() == 0) {
            while (true)
            {
                const char chr = stream->get();
                column++;
                if (chr == '\n' && tokenStr[tokenStr.length() - 1] == '\\') {
                    tokenStr = tokenStr.substr(0, tokenStr.length() - 1);
                    continue;
                }
                if (chr == '\n' || chr == -1) break;
                if (inString)
                {
                    if (chr == '"')
                    {
                        if (tokenStr[tokenStr.length() - 1] == '\\') {
                            tokenStr[tokenStr.length() - 1] = '\"';
                        } else {
                            inString = false;
                            StringToken *token = new StringToken();
                            token->string = tokenStr;
                            token->column = column;
                            Token tokenWrapper;
                            tokenWrapper.val = token;
                            tokenWrapper.type = TokenType::STRING;
                            tokens.push_back(tokenWrapper);
                            toReturn.tokens.push_back(tokenWrapper);
                            tokenStr = "";
                        }
                        continue;
                    }
                    if (tokenStr[tokenStr.length() - 1] == '\\') {
                        if (chr == 'n') {
                            tokenStr[tokenStr.length() - 1] = '\n';
                        } else if (chr == 't') {
                            tokenStr[tokenStr.length() - 1] = '\t';
                        } else if (chr == '0') {
                            tokenStr[tokenStr.length() - 1] = 0;
                        } else if (chr != '\\') {
                            std::cerr << "Unknown escape sequence '" << "\\" << chr << "'" << std::endl;
                            std::exit(1);
                        }
                    } else {
                        tokenStr += chr;
                    }
                    continue;
                }

                if (chr == ' ')
                {
                    endToken(toReturn, tokenStr, column);
                    continue;
                } if (chr == '(' || chr == ')' || chr == '[' || chr == ']' || chr == '{' || chr == '}')
                {
                    endToken(toReturn, tokenStr, column);
                    BracketToken *token = new BracketToken();
                    token->string = chr;
                    token->column = column;
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
                    tokens.push_back(tokenWrapper);
                    toReturn.tokens.push_back(tokenWrapper);
                    continue;
                } if (chr == '"' && tokenStr != "\\")
                {
                    endToken(toReturn, tokenStr, column);
                    inString = true;
                    continue;
                }
                tokenStr += chr;
            }
            endToken(toReturn, tokenStr, column);
        }

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

    std::vector<Token> tokens;
};

class Lexer
{
public:
    inline static std::vector<DataStreamBase<TokenizedLine> *> streamStack = {nullptr};

    static void cleanUp()
    {
        delete streamStack[streamStack.size() - 1];
        if (streamStack.size() != 1) {
            streamStack.pop_back();
        }
    }

    static DataStream<TokenizedLine> lex(std::ifstream *strm)
    {
        streamStack.push_back(new LexDataStream(strm));
        return DataStream(streamStack[streamStack.size() - 1]);
    }

    static std::vector<std::vector<TokenizedLine>> include(TokenizedLine line) {
        std::vector<std::vector<TokenizedLine>> toReturn;
        if (line.tokens[0].val->string == "using") {
            if (line.tokens[1].type != TokenType::IDENTIFIER) {
                std::cerr << "Error (" << line.lineNum << ":" << line.tokens[1].val->column << "): `" << line.tokens[1].toString() <<
                    "` is not an identifier." << std::endl;
                std::exit(1);
            }
            if (line.tokens.size() > 2) {
                std::cerr << "Error (" << line.lineNum << ":" << line.tokens[1].val->column << "): Too many arguments for `using` directive" << std::endl;
                std::exit(1);
            }

            std::ifstream *strm = nullptr;
            for (int i = 0; i < G::libraryPaths.size(); i++) {
                fs::path path = G::libraryPaths[i];
                path.append(Util::replace(line.tokens[1].val->string, ".", "/"));
                path.append("main.g");
                if (exists(path)) {
                    strm = new std::ifstream(path);
                }
            }
            if (strm == nullptr) {
                std::cerr << "Error (" << line.lineNum << ":" << line.tokens[1].val->column << "): Could not find include file `" <<
                    line.tokens[1].toString() << "`" << std::endl;
                std::exit(1);
            }

            auto lexed = Lexer::lex(strm);
            toReturn.push_back(std::vector<TokenizedLine>());
            while (!lexed.done()) {
                TokenizedLine tempLine = lexed.get();
                toReturn[toReturn.size() - 1].push_back(tempLine);
                if (tempLine.tokens[0].type == TokenType::KEYWORD &&
                    ((KeywordToken *) tempLine.tokens[0].val)->type == KeywordType::INCLUDE) {
                    auto vec = Lexer::include(tempLine);
                    toReturn.insert(toReturn.end(), vec.begin(), vec.end());
                }
            }
            delete strm;
            strm = nullptr;
        } else {
            if (line.tokens[1].type != TokenType::STRING) {
                std::cerr << "Error (" << line.lineNum << ":" << line.tokens[1].val->column << "): `" << line.tokens[1].toString() <<
                          "` is not a string." << std::endl;
                std::exit(1);
            }
            if (line.tokens.size() > 2) {
                std::cerr << "Error (" << line.lineNum << ":" << line.tokens[1].val->column << "): Too many arguments for `include` directive" << std::endl;
                std::exit(1);
            }

            std::ifstream *strm = nullptr;

            fs::path path = line.tokens[1].val->string;
            if (exists(path)) {
                strm = new std::ifstream(path);
            }
            if (strm == nullptr) {
                std::cerr << "Error (" << line.lineNum << ":" << line.tokens[1].val->column << "): Could not find include file `" <<
                          line.tokens[1].toString() << "`" << std::endl;
                std::exit(1);
            }

            auto lexed = Lexer::lex(strm);
            toReturn.push_back(std::vector<TokenizedLine>());
            while (!lexed.done()) {
                TokenizedLine tempLine = lexed.get();
                toReturn[toReturn.size() - 1].push_back(tempLine);
                if (line.tokens[0].type == TokenType::KEYWORD &&
                    ((KeywordToken *) line.tokens[0].val)->type == KeywordType::INCLUDE) {
                    auto temp = Lexer::include(line);
                    toReturn.insert(toReturn.end(), temp.begin(), temp.end());
                }
            }
            delete strm;
            strm = nullptr;
        }
        return toReturn;
    }
};

#endif // G_LEXER
