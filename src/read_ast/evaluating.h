#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

void check_overflow(int64_t left, int64_t right, int operators) {
    if (operators == 1) {
        if (right > 0 && left > INT64_MAX - right) {
            throw std::runtime_error("Overflow detected!");
        };
        if (right < 0 && left < INT64_MIN - right) {
            throw std::runtime_error("Overflow detected!");
        }
    }

    else if (operators == 2) {
        if (right < 0 && left > INT64_MAX + right) {
            throw std::runtime_error("Overflow detected!");
        };
        if (right > 0 && left < INT64_MIN + right) {
            throw std::runtime_error("Overflow detected!");
        }
    }

    else if (operators == 3) {
        if (right != 0 && left > INT64_MAX / right) {
            throw std::runtime_error("Overflow detected!");
        };
        if (right != 0 && left < INT64_MIN / right) {
            throw std::runtime_error("Overflow detected!");
        }
        if (left > 0 && right < 0 && right < INT64_MIN / left) {throw std::runtime_error("Overflow detected!");}
        if (left < 0 && right > 0 && left < INT64_MIN / right) {throw std::runtime_error("Overflow detected!");}
    }

    else if (operators == 4) {
       if (right == -1 && left == INT64_MIN) {
            throw std::runtime_error("Overflow detected!");}
        }
    }

int64_t express(const std::vector<Token>& lis, int& num, std::unordered_map<std::string, int64_t> vars = {}) {

    if (lis[num].type == Token::LPAREN) {
        num++;
        return express(lis, num, vars);
    }
    else if (lis[num].type == Token::ADD) {
        num++;                            
        int64_t left  = express(lis, num, vars);
        int64_t right = express(lis, num, vars);
        num++;
        check_overflow(left,right,1); 
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
        check_overflow(left,right,2);   
        return left - right; 
    }

    else if (lis[num].type == Token::DIVIDE) {
        num++;
        int64_t left  = express(lis, num, vars);
        int64_t right = express(lis, num, vars);
        num++;  

        if (right == 0) {
            throw std::runtime_error("Cannot divide with zero!");
        }
        check_overflow(left,right,4); 
        return left / right;
    }

    else if (lis[num].type == Token::IDENTIFIER) {
        return vars.at(lis[num++].value);

    }

    else if (lis[num].type == Token::MULTIPLY) {
        num++;
        int64_t left  = express(lis, num, vars);
        int64_t right = express(lis, num, vars);
        num++;
        check_overflow(left,right,3);   
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

    if (inputFile.fail()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

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
