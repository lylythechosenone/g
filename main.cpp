#include <iostream>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

int main( int argc, char* argv[])
{
    std::ifstream stream(argv[1]);

    if (!stream.good()) {
        std::cerr << "Failed to open file '" << argv[1] << "'" << std::endl;
        return 1;
    }

    auto lexed = Lexer::lex(&stream);
    std::vector<std::vector<TokenizedLine>> files;
    std::vector<TokenizedLine> mainFile;

    while (!lexed.done()) {
        TokenizedLine line = lexed.get();
        mainFile.push_back(line);
        if (line.tokens[0].type == TokenType::KEYWORD &&
            ((KeywordToken *) line.tokens[0].val)->type == KeywordType::INCLUDE) {
            auto temp = Lexer::include(line);
            files.insert(files.end(), temp.begin(), temp.end());
            std::vector<TokenizedLine> file = files[files.size() - 1];
            for (int i = 0; i < file.size(); i++) {
                for (int j = 0; j < file[i].tokens.size(); j++) {
                    std::cout << file[i].tokens[j].toString() << " ";
                }
                std::cout << std::endl;
            }
        }
    }
    files.push_back(mainFile);

    for (int i = 0; i < files.size(); i++) {
        Lexer::cleanUp();
    }
    Parser::cleanUp();
    return 0;
}