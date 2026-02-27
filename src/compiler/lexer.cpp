#include "lexer.h"

Lexer::Lexer(const std::string& filename) {
    // Open the file and prepare for tokenization
    readFile.open(filename);
}

Lexer::~Lexer() {
    // Close the file if it's open
    if (readFile.is_open()) {
        readFile.close();
    }
}

Token Lexer::consume() {
    Token token;
    char ch;

    // skip any leading whitespace before reading a token
    while (readFile.get(ch) && isspace(static_cast<unsigned char>(ch))) {
        // loop until non-whitespace or EOF
    }

    if (readFile.eof() || !readFile) {
        token.type = Token::ERROR; // End of file or invalid stream
        return token;
    }

    // `ch` now holds the first non‑whitespace character
    if (std::isdigit(static_cast<unsigned char>(ch))) {
        token.type = Token::NUMBER;
        token.value += ch;
        // consume remaining digits
        while (readFile.get(ch) && std::isdigit(static_cast<unsigned char>(ch))) {
            token.value += ch;
        }
        if (readFile) {
            readFile.unget(); // put back non‑digit
        }
    } else if (std::islower(static_cast<unsigned char>(ch))) {
        token.type = Token::IDENTIFIER;
        token.value += ch;
        while (readFile.get(ch) && std::islower(static_cast<unsigned char>(ch))) {
            token.value += ch;
        }
        if (readFile) {
            readFile.unget(); // put back non‑identifier char
        }
    } else {
        token.value = ch;
        switch (ch) {
            case '+': token.type = Token::ADD; break;
            case '-': token.type = Token::SUBTRACT; break;
            case '*': token.type = Token::MULTIPLY; break;
            case '/': token.type = Token::DIVIDE; break;
            case '(': token.type = Token::LPAREN; break;
            case ')': token.type = Token::RPAREN; break;
            default:
                token.type = Token::ERROR; // Unrecognized character
                break;
        }
    }

    return token;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    // Tokenize the input file and populate the tokens vector
    while (true) {
        Token token = consume();
        if (token.type == Token::ERROR) break;
        tokens.push_back(token);
    }
    tokens.push_back({Token::END, ""});
    return tokens;
}