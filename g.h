#ifndef G_G_H
#define G_G_H

namespace G
{
    inline std::vector<std::string> includeKeywords = {"using", "include"};
    inline std::vector<std::string> ifKeywords = {"if", "else"};
    inline std::vector<std::string> loopBeginKeywords = {"while", "for"};
    inline std::vector<std::string> loopUtilKeywords = {"continue", "break"};
    inline std::vector<std::string> switchKeywords = {"switch", "case"};
    inline std::vector<std::string> typeKeywords = {"string", "number", "nothing", "none", "bool", "char",
                                                    "byte", "word", "dword", "qword"};
    inline std::vector<std::string> preProcessorKeywords = {"pre"};
    inline std::vector<std::string> classKeywords = {"container", "class", "base"};
    inline std::vector<std::string> accessModifierKeywords = {"public", "private"};
    inline std::vector<std::string> modifierKeywords = {"const", "compiletime"};
    inline std::vector<std::string> miscKeywords = {"end", "loop", "define", "external", "true", "false"};

#ifdef __linux
    inline std::vector<std::string> libraryPaths = {"/usr/lib/g", "/usr/local/lib/g", "./lib"};
#endif
}

#endif //G_G_H
