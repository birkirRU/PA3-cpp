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

    readFile.get(ch);

    if (readFile.eof()) {
        token.type = Token::ERROR; // End of file
        return token;
    } else if (std::isdigit(static_cast<unsigned char>(ch))) {
        token.type = Token::NUMBER;
        token.value += ch;
        while (readFile.get(ch) && std::isdigit(static_cast<unsigned char>(ch))) {
            token.value += ch;
        }
        readFile.unget(); // Put back the last character that is not a digit
    } else if (std::islower(static_cast<unsigned char>(ch))) {
        token.type = Token::IDENTIFIER;
        token.value += ch;
        while (readFile.get(ch) && (std::islower(static_cast<unsigned char>(ch)))) {
            token.value += ch;
        }
        readFile.unget(); // Put back the last character that is not part of an identifier
    } else {
        switch (ch) {
            case '+':
                token.type = Token::ADD;
                break;
            case '-':
                token.type = Token::SUBTRACT;
                break;
            case '*':
                token.type = Token::MULTIPLY;
                break;
            case '/':
                token.type = Token::DIVIDE;
                break;
            case '(':
                token.type = Token::LPAREN;
                break;
            case ')':
                token.type = Token::RPAREN;
                break;
            default:
                token.type = Token::ERROR; // Unrecognized character
                break;
        }
    }
    // Skip whitespace
    while (readFile.get(ch) && isspace(static_cast<unsigned char>(ch))) {
        // Do nothing, just skip whitespace
        }
    readFile.unget(); // Put back the last character that is not whitespace

    return token;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    // Tokenize the input file and populate the tokens vector
    while (!readFile.eof()) {
        Token token = consume();
        if (token.type != Token::ERROR) {
            tokens.push_back(token);
        }
    }
    return tokens;
}