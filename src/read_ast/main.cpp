#include "../compiler/lexer.h"
#include "evaluating.h"
#include <fstream>
#include <iostream>
#include <stdexcept>


int main(int argc, char* argv[]) {

    std::vector<Token> tokens2;
    std::string inputFile;
    std::string varFile;
    int number = 0;

    if (argc < 2) {
        std::cerr << "Parameters needed: give AST file (and optionally \"var\" to use read_ast/vars.txt)\n";
        return 1;
    }

    if (argc == 3 && std::string(argv[2]) != "var") {
        std::cerr << "Second argument must be \"var\" to use variables, or omit for no variables\n";
        return 1;
    }

    if (argc == 2 || argc == 3) {
        inputFile = "src/ast/" + std::string(argv[1]);
        std::ifstream check(inputFile);
        if (!check) {
            std::cerr << "Could not open AST file: " << inputFile << "\n";
            return 1;
        }
    }

    try {
        if (argc == 2 || argc == 3) {
            Lexer lexer2(inputFile);
            tokens2 = lexer2.tokenize();
        }

        if (argc == 3) {
            varFile = "src/read_ast/vars.txt";
            std::unordered_map<std::string, int64_t> vars = load_variables(varFile);
            std::cout << express(tokens2, number, vars) << "\n";
        }
        else if (argc == 2) {
            std::cout << express(tokens2, number) << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;

}