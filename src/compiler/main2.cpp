#include "lexer.h"
#include "ast.h"
#include "parcer.h"
#include "evaluating.h"


int main(int argc, char* argv[]) {
    std::string inputFile;
    std::string varFile;

    if (argc == 2) {
        inputFile = "src/ast/" + std::string(argv[1]);
        Lexer lexer2(inputFile);
        std::vector<Token> tokens2 = lexer2.tokenize();
        int number = 0;
        std::cout << express(tokens2, number);

    } else if (argc == 3) {
        inputFile = "src/ast/" + std::string(argv[1]);
        varFile   = argv[2];
        Lexer lexer2(inputFile);
        std::vector<Token> tokens2 = lexer2.tokenize();
        int number = 0;
        std::unordered_map<std::string, int64_t> vars = load_variables(varFile);
        std::cout << express(tokens2, number, vars);
    }
    else {
        // Yet to be implemnted
    }

    // // Clean up the AST
    // delete ast;

    return 0;

}