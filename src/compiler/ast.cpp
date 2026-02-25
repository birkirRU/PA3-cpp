
#include "ast.h"

ASTtree::ASTtree(std::unique_ptr<ASTnode>&& root, std::ofstream& stream) : root(std::move(root)), stream(stream) {}


void ASTtree::outputTree(const std::string& ofilename) {
    stream.open(ofilename);
    _outputTree(root);
    stream.close();
}

void ASTtree::_outputTree(const std::unique_ptr<ASTnode>& current_node) const {
    current_node->output(stream);
//     if (typeid(current_node) == typeid(Number)) {
        


//     } else if (typeid(current_node) == typeid(Variable)) {

//     } else if (typeid(current_node) == typeid(BinaryOp)) {

//     } else if (typeid(current_node) == typeid(UnaryOp)) {
// }

}

ASTnode::~ASTnode() {}

void ASTnode::output(std::ofstream& s) const {}

Number::Number(Token value) : value(value) {}

void Number::output(std::ofstream& s) const {
    s << value.value;
}

Variable::Variable(Token value) : value(value) {}

void Variable::output(std::ofstream& s) const {
    s << value.value;
}

UnaryOp::UnaryOp(const Token& op, std::unique_ptr<ASTnode> operand) : op(op), operand(std::move(operand)) {}

void UnaryOp::output(std::ofstream& s) const {
    s << '(';
    s << op.value;
    operand->output(s);
    s << ')';
}

BinaryOp::BinaryOp(const Token& op, std::unique_ptr<ASTnode> l, std::unique_ptr<ASTnode> r) : op(op), left(std::move(l)), right(std::move(r)) {}

void BinaryOp::output(std::ofstream & s) const {
    s << '(';
    s << op.value;
    left->output(s);
    right->output(s);
    s << ')';
}
