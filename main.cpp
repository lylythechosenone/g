#include <iostream>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "File.h"

int main(int argc, char* argv[])
{
    std::ifstream stream(argv[1]);

    if (!stream.good()) {
        std::cerr << "Failed to open file '" << argv[1] << "'" << std::endl;
        return 1;
    }

    auto lexed = Lexer::lex(&stream);
    std::vector<File> files;
    File mainFile;
    mainFile.name = argv[1];

    while (!lexed.done()) {
        TokenizedLine line = lexed.get();
        mainFile.lines.push_back(line);
        if (line.tokens[0].type == TokenType::KEYWORD &&
            ((KeywordToken *) line.tokens[0].val)->type == KeywordType::INCLUDE) {
            auto temp = Lexer::include(line);
            files.insert(files.end(), temp.begin(), temp.end());
            File file = files[files.size() - 1];
        }
    }
    files.push_back(mainFile);
    for (auto &file : files) {
        std::cout << std::endl << "File `" << file.name << "`:" << std::endl;
        for (int i = 0; i < file.lines.size(); i++) {
            for (int j = 0; j < file.lines[i].tokens.size(); j++) {
                std::cout << "\\\\" << file.lines[i].tokens[j].toString() << "\\\\ ";
            }
            std::cout << std::endl;
        }
    }

    for (int i = 0; i < files.size(); i++) {
        Lexer::cleanUp();
    }
    Parser::cleanUp();
    return 0;
}