#include "lexer.h"
#include "ast.h"
#include "parcer.h"


int main(int argc, char* argv[]) {
    std::string inputFile;
    std::string writeFile;

    if (argc <= 1) {
        // no arguments, fall back to default example file
        inputFile = "src/expressions/input.txt";
    } else if (argc == 2) {
        // Yet to be implamented 

    } else if (argc == 3) {
        writeFile = argv[1];
        inputFile = argv[2];
    }

    else {
        // Yet to be implemnted
    }

    // The PROGRAM must be run from ROOT, where input file has to exist in 'expressions' folder
    // The name of the write file will always be written to 'ast' folder.
    inputFile = "src/expressions/" + inputFile;

    Lexer lexer(inputFile);
    std::vector<Token> tokens = lexer.tokenize();

    // debug: print tokens to stdout so we can see the lexer's output
    for (const Token &t : tokens) {
        std::cout << "token type=" << t.type;
        std::cout << " value='" << t.value << "'";
        std::cout << '\n';
    }

    Parser parser(tokens);
    parser.buildST();

    

    // // Clean up the AST
    // delete ast;

    return 0;

}