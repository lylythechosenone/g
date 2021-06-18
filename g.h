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
    inline std::vector<std::string> miscKeywords = {"end", "loop", "define", "external", "true", "false", "operator"};


    inline std::vector<std::string> assignmentOperators = {"=", "+=", "-=", "*=", "/=", "%=", ">>=", "<<=", "&=", "^=", "|="};
    inline std::vector<std::string> mathOperators = {"+", "-", "*", "/", "%", ">>", "<<"};
    inline std::vector<std::string> bitwiseOperators = {"&", "^", "|"};
    inline std::vector<std::string> comparisonOperators = {"==", "<=", ">=", "<", ">", "!="};
    inline std::vector<std::string> logicOperators = {"&&", "||", "!"};
    inline std::vector<std::string> incrementDecrementOperators = {"++", "--"};
    inline std::vector<std::string> ternaryOperators = {"?", ":"};

    inline std::vector<std::vector<std::string>> operators = {assignmentOperators, mathOperators, bitwiseOperators, comparisonOperators,
                                                              logicOperators, incrementDecrementOperators, ternaryOperators};


#ifdef __linux
    inline std::vector<std::string> libraryPaths = {"./lib", "/usr/lib/g", "/usr/local/lib/g"};
#endif
}

#endif //G_G_H
