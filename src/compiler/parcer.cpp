#include "parcer.h"
#include "ast.h"
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), curr_token(0) {}


void Parser::_nextToken() {curr_token += 1;}

std::unique_ptr<ASTnode> Parser::buildST() {
    std::unique_ptr<ASTnode> ast_root = _expr();
    return ast_root;
}

std::unique_ptr<ASTnode> Parser::_expr() {
    std::unique_ptr<ASTnode> node = _term(); 
    Token currToken;

    while (tokens[curr_token].type == Token::ADD || tokens[curr_token].type == Token::SUBTRACT) {
        currToken = tokens[curr_token];
        _nextToken();
        std::unique_ptr<ASTnode> right = _term(); 
        node = std::make_unique<BinaryOp>(currToken, std::move(node), std::move(right));
    }
    return node;
}

std::unique_ptr<ASTnode> Parser::_term() {
    std::unique_ptr<ASTnode> node = _factor(); 
    Token currToken;

    while (tokens[curr_token].type == Token::MULTIPLY || tokens[curr_token].type == Token::DIVIDE) {
        currToken = tokens[curr_token];
        _nextToken();
        std::unique_ptr<ASTnode> right = _factor(); 
        node = std::make_unique<BinaryOp>(currToken, std::move(node), std::move(right));
    }
    return node;
}


std::unique_ptr<ASTnode> Parser::_factor() {
    std::unique_ptr<ASTnode> node;

    // std::make_unique initializes Class on heap, and creates unique pointer, moved to node
    Token currToken = tokens[curr_token];
    if (currToken.type == Token::NUMBER) {
        node = std::make_unique<Number>(currToken);
        _nextToken();
    }
    else if (currToken.type == Token::IDENTIFIER) {
        node = std::make_unique<Variable>(currToken);
        _nextToken();
    }
    else if (currToken.type == Token::SUBTRACT) {
        _nextToken();
        node = std::make_unique<UnaryOp>(currToken, std::move(_factor()));
    }
    else if (currToken.type == Token::LPAREN) {
        _nextToken();
        node = _expr();
        if (tokens[curr_token].type == Token::RPAREN) {
            _nextToken();
        } else {
            throw std::runtime_error("Missing ')'");
        }
    }

    return node;
}