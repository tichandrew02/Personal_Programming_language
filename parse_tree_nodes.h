#ifndef PARSE_TREE_NODES_H
#define PARSE_TREE_NODES_H

#include <iostream>
#include <vector>
#include <string>
#include "lexer.h"

using namespace std;

extern bool printDelete;

// Forward declarations
class ProgramNode;
class BlockNode;
class StatementNode;
class AssignmentStmtNode;
class CompoundStmtNode;
class IfStmtNode;
class WhileStmtNode;
class ReadStmtNode;
class WriteStmtNode;
class ExpressionNode;
class SimpleExpNode;
class TermNode;
class FactorNode;
class IdNode;
class IntLitNode;
class FloatLitNode;
class NestedExprNode;
class NotNode;
class MinusNode;

class ProgramNode {
public:
    int _level = 0;
    BlockNode* blockPtr = nullptr;

    ProgramNode(int level);
    ~ProgramNode();
};
ostream& operator<<(ostream&, ProgramNode&);

class BlockNode {
public:
    int _level = 0;
    StatementNode* stmtPtr = nullptr;

    BlockNode(int level);
    ~BlockNode();
};
ostream& operator<<(ostream&, BlockNode&);

class StatementNode {
public:
    int _level = 0;
    virtual void printTo(ostream& os) = 0;
    virtual ~StatementNode();
};
ostream& operator<<(ostream&, StatementNode&);

class AssignmentStmtNode : public StatementNode {
public:
    string* varName = nullptr;
    string* assignOp = nullptr;
    ExpressionNode* exprPtr = nullptr;

    AssignmentStmtNode(int level);
    ~AssignmentStmtNode();
    void printTo(ostream& os);
};

class CompoundStmtNode : public StatementNode {
public:
    vector<StatementNode*> stmts;

    CompoundStmtNode(int level);
    ~CompoundStmtNode();
    void printTo(ostream& os);
};

class IfStmtNode : public StatementNode {
public:
    ExpressionNode* exprPtr = nullptr;
    StatementNode* thenStmtPtr = nullptr;
    StatementNode* elseStmtPtr = nullptr;

    IfStmtNode(int level);
    ~IfStmtNode();
    void printTo(ostream& os);
};

class WhileStmtNode : public StatementNode {
public:
    ExpressionNode* exprPtr = nullptr;
    StatementNode* stmtPtr = nullptr;

    WhileStmtNode(int level);
    ~WhileStmtNode();
    void printTo(ostream& os);
};

class ReadStmtNode : public StatementNode {
public:
    string* dataPtr = nullptr;

    ReadStmtNode(int level);
    ~ReadStmtNode();
    void printTo(ostream& os);
};

class WriteStmtNode : public StatementNode {
public:
    string* dataPtr = nullptr;

    WriteStmtNode(int level);
    ~WriteStmtNode();
    void printTo(ostream& os);
};

// ===================== Expression =====================
class ExpressionNode {
public:
    int _level = 0;
    SimpleExpNode* firstSimpleExp = nullptr;
    vector<int> restSimpleExpOps;
    SimpleExpNode* secondSimpleExp = nullptr;

    ExpressionNode(int level);
    ~ExpressionNode();
};
ostream& operator<<(ostream&, ExpressionNode&);

class SimpleExpNode {
public:
    int _level = 0;
    TermNode* firstTerm = nullptr;
    vector<int> restTermOps;
    vector<TermNode*> restTerms;

    SimpleExpNode(int level);
    ~SimpleExpNode();
};
ostream& operator<<(ostream&, SimpleExpNode&);

class TermNode {
public:
    int _level = 0;
    FactorNode* firstFactor = nullptr;
    vector<int> restFactorOps;
    vector<FactorNode*> restFactors;

    TermNode(int level);
    ~TermNode();
};
ostream& operator<<(ostream&, TermNode&);

// ===================== Factor Base and Derived =====================
class FactorNode {
public:
    int _level = 0;
    virtual void printTo(ostream& os) = 0;
    virtual ~FactorNode();
};
ostream& operator<<(ostream&, FactorNode&);

class IdNode : public FactorNode {
public:
    string* id = nullptr;

    IdNode(int level, string name);
    ~IdNode();
    void printTo(ostream& os);
};

class IntLitNode : public FactorNode {
public:
    int int_literal = 0;

    IntLitNode(int level, int value);
    ~IntLitNode();
    void printTo(ostream& os);
};

class FloatLitNode : public FactorNode {
public:
    float float_literal = 0;

    FloatLitNode(int level, float value);
    ~FloatLitNode();
    void printTo(ostream& os);
};

class NotNode : public FactorNode {
public:
    FactorNode* factorPtr = nullptr;

    NotNode(int level);
    ~NotNode();
    void printTo(ostream& os);
};

class MinusNode : public FactorNode {
public:
    FactorNode* factorPtr = nullptr;

    MinusNode(int level);
    ~MinusNode();
    void printTo(ostream& os);
};

class NestedExprNode : public FactorNode {
public:
    ExpressionNode* exprPtr = nullptr;

    NestedExprNode(int level, ExpressionNode* expr);
    ~NestedExprNode();
    void printTo(ostream& os);
};

#endif // PARSE_TREE_NODES_H
