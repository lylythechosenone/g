#include <iostream>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

int main( int argc, char* argv[])
{
    std::ifstream stream(argv[1]);

    if (!stream.good()) {
        std::cerr << "Failed to open file." << std::endl;
        return -1;
    }

    auto lexed = Lexer::lex(&stream);

    while (!lexed.done()) {
        TokenizedLine line = lexed.get();
        for (int i = 0; i < line.tokens.size(); i++) {
            std::cout << line.tokens[i].data["string"].getString() << " ";
        }
        std::cout << std::endl;
    }

    auto parsed = Parser::parse(&lexed);

    Lexer::cleanUp();
    Parser::cleanUp();
    return 0;
}