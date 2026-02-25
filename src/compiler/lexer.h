#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <string> 
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>


struct Token {
    static const int NUMBER = 1;
    static const int IDENTIFIER = 2;
    static const int ADD = 3;
    static const int SUBTRACT = 4;
    static const int MULTIPLY = 5;
    static const int DIVIDE = 6;
    static const int LPAREN = 7;
    static const int RPAREN = 8;
    static const int ERROR = 9;

    int type;
    std::string value;
};

class Lexer {
    std::ifstream readFile;
    std::vector<Token> tokens;

    public:
        Lexer(const std::string& filename);
        ~Lexer();
        std::vector<Token> tokenize();
    private:
        Token consume();
};


#endif // COMPILER_LEXER_H