
#include "lexer.h"
#include "ast.h"
#include "parcer.h"


int main(int argc, char* argv[]) {
    std::string inputFile;
    std::string writeFile;

    // Maybe later error handling no arguments
    if (argc == 1) {
        return 0;
    }
    // if there is only one argument, read expression from standard input
    else if (argc == 2) {

    } else if (argc == 3) {
        // If there are three arguments, the first is the AST output file name and the second is the input file name
        writeFile = argv[1];
        inputFile = argv[2];
    } else {
        // If there are more than three arguments, return an error code
        return 1;
    }

    // Prepend the path to the input file, the assumption that the cwd is the root of the project
    inputFile = "src/expressions/" + inputFile;
    Lexer lexer(inputFile);
    std::vector<Token> tokens = lexer.tokenize();

    // Parser parser(tokens);
    // ASTNode* ast = parser.parse();

    // // Clean up the AST
    // delete ast;

    return 0;

}