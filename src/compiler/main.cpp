#include "lexer.h"
#include "ast.h"
#include "parcer.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>


int main(int argc, char* argv[]) {
    std::string inputFile;
    std::string writeFile;

    if (argc <= 1) {
        // no arguments, fall back to default example file
        inputFile = "src/expressions/input.txt";
        writeFile = "output.txt";
    } else if (argc == 2) {
        // one argument: output file, read expression from stdin
        writeFile = argv[1];

        const std::string stdinName = "stdin_input.txt";
        const std::string stdinPath = "src/expressions/" + stdinName;

        std::ofstream tmp(stdinPath);
        if (!tmp) {
            std::cerr << "Could not open " << stdinPath << " for writing\n";
            return 1;
        }

        std::string line;
        bool first = true;
        while (std::getline(std::cin, line)) {
            if (!first) {
                tmp << '\n';
            }
            first = false;
            tmp << line;
        }

        inputFile = stdinName;
    } else if (argc == 3) {
        writeFile = argv[1];
        inputFile = argv[2];
    }

    else {
        // too many arguments, only input and output file needed
        std::cerr << "Too many arguments, only input and output file needed\n";
        return 1;
    }

    // The PROGRAM must be run from ROOT, where input file has to exist in 'expressions' folder
    // The name of the write file will always be written to 'ast' folder.
    inputFile = "src/expressions/" + inputFile;

    {
        std::ifstream check(inputFile);
        if (!check) {
            std::cerr << "Could not open input file: " << inputFile << "\n";
            return 1;
        }
    }

    Lexer lexer(inputFile);
    std::vector<Token> tokens = lexer.tokenize();


    std::unique_ptr<ASTnode> root;
    try {
        Parser parser(tokens);
        root = parser.buildST();
    } catch (const std::exception& e) {
        std::cerr << "Parse error: " << e.what() << "\n";
        return 1;
    }

    std::ofstream stream;
    ASTtree tree(std::move(root), stream);

    writeFile = "src/ast/" + writeFile;
    try {
        tree.outputTree(writeFile);
    } catch (const std::exception& e) {
        std::cerr << "Could not write AST file: " << e.what() << "\n";
        return 1;
    }
    return 0;

}