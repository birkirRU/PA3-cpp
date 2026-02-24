#include <string> 
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>

#include "lexer.h"
#include "ast.h"

class Parser {
    std::unique_ptr<ASTnode> ast_root;
    std::vector<Token> tokens;
    uint curr_token;
    public:
        Parser(const std::vector<Token>& tokens);

        void buildST();
    private:
        std::unique_ptr<ASTnode> _expr();
        std::unique_ptr<ASTnode> _term();
        std::unique_ptr<ASTnode> _factor();
        void _nextToken();
};
