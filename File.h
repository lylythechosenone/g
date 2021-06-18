#include <string>
#include <vector>

#include "Lexer/Token.h"

#ifndef G_FILE_H
#define G_FILE_H


class File {
public:
    std::string name;
    std::vector<TokenizedLine> lines;
};


#endif // G_FILE_H
