#include <fstream>
#include <iostream>

#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

int main(int argc, char* argv[])
{
    std::ifstream stream(argv[1]);

    auto lexed = Lexer::lex(&stream);
    auto parsed = Parser::parse(&lexed);

    Lexer::cleanUp();
    Parser::cleanUp();
    return 0;
}