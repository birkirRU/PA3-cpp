#ifndef COMPILER_AST_H
#define COMPILER_AST_H

#include "lexer.h"
#include "memory"

class ASTtree {
    std::unique_ptr<ASTnode> root;
    std::ofstream& stream;

    public:
        ASTtree(std::unique_ptr<ASTnode>&& root, std::ofstream& stream);
        // No need for destructor since unique_ptr will automatically clean up the tree

        void outputTree(const std::string& ofilename);
        void _outputTree(const std::unique_ptr<ASTnode>& current_node) const;
};

class ASTnode {
    public:
        virtual ~ASTnode() = default;
        void virtual output(std::ofstream & s) const;
};

// Numbers and variables are always leaf nodes of syntax trees
class Number: public ASTnode {
    Token value;
    public: 
        Number(Token value);
        void output(std::ofstream & s) const override;
};

class Variable: public ASTnode {
    Token value;
    public: 
        Variable(Token value);
        void output(std::ofstream & s) const override;
};

// only '-' operator
class UnaryOp: public ASTnode {
    Token op;
    std::unique_ptr<ASTnode> operand;
    
    public: 
        UnaryOp(const Token& op, std::unique_ptr<ASTnode> operand);
        void output(std::ofstream & s) const override;
};

// ops like +, - *, /
class BinaryOp: public ASTnode {
    Token op;
    std::unique_ptr<ASTnode> left;
    std::unique_ptr<ASTnode> right;
    public: 
        BinaryOp(const Token& op, std::unique_ptr<ASTnode> l, std::unique_ptr<ASTnode> r);
        void output(std::ofstream & s) const override;
};

// No need for parenthises since, the structure of the tree cover it

#endif // COMPILER_AST_H