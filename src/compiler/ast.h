#include "lexer.h"
#include "memory"
class ASTnode {
    virtual ~ASTnode() = default;
};

// Numbers and variables are always leaf nodes of syntax trees
class Number: public ASTnode {
    Token value;
    public: 
        Number(Token value);
        ~Number();
};

class Variable: public ASTnode {
    Token value;
    public: 
        Variable(Token value);
        ~Variable();
};

// only '-' operator
class UnaryOp: public ASTnode {
    Token op;
    std::unique_ptr<ASTnode> operand;
    
    public: 
        UnaryOp(std::unique_ptr<ASTnode> operand);
        ~UnaryOp();
};

// ops like +, - *, /
class BinaryOp: public ASTnode {
    Token op;
    std::unique_ptr<ASTnode> left;
    std::unique_ptr<ASTnode> right;
    public: 
        BinaryOp(const Token& op, std::unique_ptr<ASTnode> l, std::unique_ptr<ASTnode> r);
        ~BinaryOp();
};

// No need for parenthises since, the structure of the tree cover it