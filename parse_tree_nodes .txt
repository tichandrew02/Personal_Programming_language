#include "parse_tree_nodes.h"

bool printDelete = false;

static void indent(int level) {
    for (int i = 0; i < level; ++i)
        cout << "|  ";
}

//ProgramNode
ProgramNode::ProgramNode(int level) {
    _level = level;
}
ProgramNode::~ProgramNode() {
    if (printDelete) cout << "Deleting ProgramNode" << endl;
    delete blockPtr;
}
ostream& operator<<(ostream& os, ProgramNode& pn) {
    os << endl; indent(pn._level); os << "(program ";
    os << *(pn.blockPtr);
    os << endl; indent(pn._level); os << "program) ";
    return os;
}

//BlockNode
BlockNode::BlockNode(int level) {
    _level = level;
}
BlockNode::~BlockNode() {
    if (printDelete) cout << "Deleting BlockNode" << endl;
    delete stmtPtr;
}
ostream& operator<<(ostream& os, BlockNode& bn) {
    os << endl; indent(bn._level); os << "(block ";
    os << *(bn.stmtPtr);
    os << endl; indent(bn._level); os << "block) ";
    return os;
}

//StatementNode
StatementNode::~StatementNode() {}
ostream& operator<<(ostream& os, StatementNode& sn) {
    os << endl; indent(sn._level);
    sn.printTo(os);
    return os;
}

//AssignmentStmtNode
AssignmentStmtNode::AssignmentStmtNode(int level) {
    _level = level;
}
AssignmentStmtNode::~AssignmentStmtNode() {
    if (printDelete) cout << "Deleting StatementNode:AssignmentStmtNode" << endl;
    delete varName;
    delete assignOp;
    delete exprPtr;
}
void AssignmentStmtNode::printTo(ostream& os) {
    os << "(assignment_stmt ( " << *varName << " " << *assignOp << " ) ";
    exprPtr->_level = _level + 1;
    os << *exprPtr;
    os << endl; indent(_level); os << "assignment_stmt) ";
}

//CompoundStmtNode
CompoundStmtNode::CompoundStmtNode(int level) {
    _level = level;
}
CompoundStmtNode::~CompoundStmtNode() {
    if (printDelete) cout << "Deleting StatementNode:CompoundStmtNode" << endl;
    for (auto stmt : stmts) delete stmt;
}
void CompoundStmtNode::printTo(ostream& os) {
    os << "(compound_stmt ";
    for (auto stmt : stmts) {
        stmt->_level = _level + 1;
        os << *stmt;
    }
    os << endl; indent(_level); os << "compound_stmt) ";
}

//IfStmtNode
IfStmtNode::IfStmtNode(int level) {
    _level = level;
}
IfStmtNode::~IfStmtNode() {
    if (printDelete) cout << "Deleting StatementNode:IfStmtNode" << endl;
    delete exprPtr;
    delete thenStmtPtr;
    delete elseStmtPtr;
}
void IfStmtNode::printTo(ostream& os) {
    os << "(if_stmt ";
    os << *exprPtr;
    os << endl; indent(_level); os << "(then ";
    os << *thenStmtPtr;
    os << endl; indent(_level); os << "then) ";
    if (elseStmtPtr) {
        os << endl; indent(_level); os << "(else ";
        os << *elseStmtPtr;
        os << endl; indent(_level); os << "else) ";
    }
    os << endl; indent(_level); os << "if_stmt) ";
}

// -------------------- WhileStmtNode --------------------
WhileStmtNode::WhileStmtNode(int level) {
    _level = level;
}
WhileStmtNode::~WhileStmtNode() {
    if (printDelete) cout << "Deleting StatementNode:WhileStmtNode" << endl;
    delete exprPtr;
    delete stmtPtr;
}
void WhileStmtNode::printTo(ostream& os) {
    os << "(while_stmt ";
    os << *exprPtr;
    os << *stmtPtr;
    os << endl; indent(_level); os << "while_stmt) ";
}

//ReadStmtNode
ReadStmtNode::ReadStmtNode(int level) {
    _level = level;
}
ReadStmtNode::~ReadStmtNode() {
    if (printDelete) cout << "Deleting StatementNode:ReadStmtNode" << endl;
    delete dataPtr;
}
void ReadStmtNode::printTo(ostream& os) {
    os << "(read_stmt ( " << *dataPtr << " ) ";
    os << endl; indent(_level); os << "read_stmt) ";
}

// WriteStmtNode
WriteStmtNode::WriteStmtNode(int level) {
    _level = level;
}
WriteStmtNode::~WriteStmtNode() {
    if (printDelete) cout << "Deleting StatementNode:WriteStmtNode" << endl;
    delete dataPtr;
}
void WriteStmtNode::printTo(ostream& os) {
    os << "(write_stmt ( " << *dataPtr << " ) ";
    os << endl; indent(_level); os << "write_stmt) ";
}

//ExpressionNode
ExpressionNode::ExpressionNode(int level) {
    _level = level;
}
ExpressionNode::~ExpressionNode() {
    if (printDelete) cout << "Deleting ExpressionNode" << endl;
    delete firstSimpleExp;
    delete secondSimpleExp;
}
ostream& operator<<(ostream& os, ExpressionNode& en) {
    os << endl; indent(en._level); os << "(expression ";
    en.firstSimpleExp->_level = en._level + 1;
    os << *(en.firstSimpleExp);
    for (int i = 0; i < en.restSimpleExpOps.size(); ++i) {
        int op = en.restSimpleExpOps[i];
        os << endl; indent(en._level);
        if (op == TOK_EQUALTO) os << "= ";
        else if (op == TOK_LESSTHAN) os << "< ";
        else if (op == TOK_GREATERTHAN) os << "> ";
        else if (op == TOK_NOTEQUALTO) os << "<> ";
    }
    if (en.secondSimpleExp) {
        en.secondSimpleExp->_level = en._level + 1;
        os << *(en.secondSimpleExp);
    }
    os << endl; indent(en._level); os << "expression) ";
    return os;
}

//SimpleExpNode
SimpleExpNode::SimpleExpNode(int level) {
    _level = level;
}
SimpleExpNode::~SimpleExpNode() {
    if (printDelete) cout << "Deleting SimpleExpNode" << endl;
    delete firstTerm;
    for (auto term : restTerms) delete term;
}
ostream& operator<<(ostream& os, SimpleExpNode& sen) {
    os << endl; indent(sen._level); os << "(simple_exp ";
    sen.firstTerm->_level = sen._level + 1;
    os << *(sen.firstTerm);
    for (int i = 0; i < sen.restTermOps.size(); ++i) {
        int op = sen.restTermOps[i];
        os << endl; indent(sen._level);
        if (op == TOK_PLUS) os << "+ ";
        else if (op == TOK_MINUS) os << "- ";
        else if (op == TOK_OR) os << "or ";
        sen.restTerms[i]->_level = sen._level + 1;
        os << *(sen.restTerms[i]);
    }
    os << endl; indent(sen._level); os << "simple_exp) ";
    return os;
}

//TermNode
TermNode::TermNode(int level) {
    _level = level;
}
TermNode::~TermNode() {
    if (printDelete) cout << "Deleting TermNode" << endl;
    delete firstFactor;
    for (auto f : restFactors) delete f;
}
ostream& operator<<(ostream& os, TermNode& tn) {
    os << endl; indent(tn._level); os << "(term ";
    tn.firstFactor->_level = tn._level + 1;
    os << *(tn.firstFactor);
    for (int i = 0; i < tn.restFactorOps.size(); ++i) {
        int op = tn.restFactorOps[i];
        os << endl; indent(tn._level);
        if (op == TOK_MULTIPLY) os << "* ";
        else if (op == TOK_DIVIDE) os << "/ ";
        else if (op == TOK_AND) os << "and ";
        tn.restFactors[i]->_level = tn._level + 1;
        os << *(tn.restFactors[i]);
    }
    os << endl; indent(tn._level); os << "term) ";
    return os;
}

// FactorNode
FactorNode::~FactorNode() {}
ostream& operator<<(ostream& os, FactorNode& fn) {
    os << endl; indent(fn._level); os << "(factor ";
    fn.printTo(os);
    os << endl; indent(fn._level); os << "factor) ";
    return os;
}

//IdNode
IdNode::IdNode(int level, string name) {
    _level = level;
    id = new string(name);
}
IdNode::~IdNode() {
    if (printDelete) cout << "Deleting FactorNode:IdNode" << endl;
    delete id;
}
void IdNode::printTo(ostream& os) {
    os << "( IDENT: " << *id << " ) ";
}

// IntLitNode
IntLitNode::IntLitNode(int level, int value) {
    _level = level;
    int_literal = value;
}
IntLitNode::~IntLitNode() {
    if (printDelete) cout << "Deleting FactorNode:IntLitNode" << endl;
}
void IntLitNode::printTo(ostream& os) {
    os << "( INTLIT: " << int_literal << " ) ";
}

//FloatLitNode
FloatLitNode::FloatLitNode(int level, float value) {
    _level = level;
    float_literal = value;
}
FloatLitNode::~FloatLitNode() {
    if (printDelete) cout << "Deleting FactorNode:FloatLitNode" << endl;
}
void FloatLitNode::printTo(ostream& os) {
    os << "( FLOATLIT: " << float_literal << " ) ";
}

//NotNode
NotNode::NotNode(int level) {
    _level = level;
}
NotNode::~NotNode() {
    if (printDelete) cout << "Deleting FactorNode:NotNode" << endl;
    delete factorPtr;
}
void NotNode::printTo(ostream& os) {
    factorPtr->_level = _level + 1;
    os << "(NOT ";
    os << *factorPtr;
    os << ") ";
}

//MinusNode
MinusNode::MinusNode(int level) {
    _level = level;
}
MinusNode::~MinusNode() {
    if (printDelete) cout << "Deleting FactorNode:MinusNode" << endl;
    delete factorPtr;
}
void MinusNode::printTo(ostream& os) {
    factorPtr->_level = _level + 1;
    os << "(- ";
    os << *factorPtr;
    os << ") ";
}

// NestedExprNode
NestedExprNode::NestedExprNode(int level, ExpressionNode* en) {
    _level = level;
    exprPtr = en;
}
NestedExprNode::~NestedExprNode() {
    if (printDelete) cout << "Deleting FactorNode:NestedExprNode" << endl;
    delete exprPtr;
}
void NestedExprNode::printTo(ostream& os) {
    exprPtr->_level = _level + 1;
    os << "( ";
    os << *exprPtr;
    os << ") ";
}
