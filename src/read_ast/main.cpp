#include "../compiler/lexer.h"
#include "evaluating.h"
#include <stdexcept>


int main(int argc, char* argv[]) {

    std::vector<Token> tokens2;
    std::string inputFile;
    std::string varFile;
    int number = 0;

    if (argc == 2 || argc == 3) {
        inputFile = "src/ast/" + std::string(argv[1]);
        Lexer lexer2(inputFile);
        tokens2 = lexer2.tokenize();
    }

    try {
        if (argc == 3) {
        varFile   = argv[2];
        std::unordered_map<std::string, int64_t> vars = load_variables(varFile);
        std::cout << express(tokens2, number, vars) << "\n";
    }
    else if (argc == 2) {
        std::cout << express(tokens2, number) << "\n";
    }

    else {
        std::cout << "Parameters needed" << "\n";
    } } catch (std::runtime_error& e) {
        std::cerr << e.what() << "\n";
    } catch (std::out_of_range& e) {
        std::cout << "Missing variables" << "\n";
    }
    
    

    return 0;

}