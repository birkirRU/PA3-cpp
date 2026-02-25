#include <vector>
#include <string>
#include "lexer.h"

int express(const std::vector<Token>& lis, int& num, std::unordered_map<std::string, int64_t>& vars) {

    if (lis[num].type == Token::LPAREN) {
        num++;
        return express(lis, num, vars);
    }
    else if (lis[num].type == Token::ADD) {
        num++;                            
        int64_t left  = express(lis, num, vars);  
        int64_t right = express(lis, num, vars);
        num++; 
        return left + right;
    }
    else if (lis[num].type == Token::SUBTRACT) {
        num++;                            
        int64_t left = express(lis, num, vars);

        if (lis[num].type == Token::RPAREN) {
            num++;  
            return -left;       
        }

        int64_t right = express(lis, num, vars);
        num++;  
        return left - right; 
    }

    else if (lis[num].type == Token::IDENTIFIER) {
        return vars[lis[num++].value];
    }

    else if (lis[num].type == Token::MULTIPLY) {
        num++;
        int64_t left  = express(lis, num, vars);
        int64_t right = express(lis, num, vars);
        num++;  
        return left * right;
    }
    else if (lis[num].type == Token::NUMBER) {
        return std::stoll(lis[num++].value); 
    }
    return 0;
}

std::unordered_map<std::string, int64_t> load_variables(std::string filename) {
    std::unordered_map<std::string, int64_t> variables;
    std::ifstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line)) {
        int equal = line.find('=');

        std::string name  = line.substr(0, equal);
        std::string value = line.substr(equal + 1);

        int64_t val = std::stoll(value);
        variables[name] = val;
    }

    return variables;
}