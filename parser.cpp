//**************************************************************************
// Name: Tichafa Rinomhota Student NetID: tar351
// Course: CSE 4714 Assignment: Part 3
// Programming Environment: Visual Studio Code 
// Purpose of File: !!!!!!!!!!!!!
//**************************************************************************


#include <stdio.h>
#include <string>
#include <set>
#include "lexer.h"
#include "parser.h"

using namespace std;

int nextToken = 0;
bool printParse = false;


static int level = 0;


set<string> symbolTable;


BlockNode *block();
StatementNode *statement();
AssignmentStmtNode *assignment_stmt();
CompoundStmtNode *compound_stmt();
IfStmtNode *if_stmt();
WhileStmtNode *while_stmt();
ReadStmtNode *read_stmt();
WriteStmtNode *write_stmt();
ExpressionNode *expression();
SimpleExpNode *simple_exp();
TermNode *term();
FactorNode *factor();


bool first_of_program();
bool first_of_block();
bool first_of_statement();
bool first_of_assignment_stmt();
bool first_of_compound_stmt();
bool first_of_if_stmt();
bool first_of_while_stmt();
bool first_of_read_stmt();
bool first_of_write_stmt();
bool first_of_expression();

string psp()
{
    string str("");
    for (int i = 0; i < level; i++)
        str += "|  ";
    return str;
}

void output(string what)
{
    //
}


ProgramNode *program()
{
    if (!first_of_program())
        throw "3: 'PROGRAM' expected";
    output("PROGRAM");
    
    ProgramNode *newProgramNode = new ProgramNode(level);
    ++level;

    nextToken = yylex();

    if (nextToken != TOK_IDENT)
        throw "2: identifier expected";
    output("IDENTIFIER");
    nextToken = yylex();

    if (nextToken != TOK_SEMICOLON)
        throw "14: ';' expected";
    output("SEMICOLON");
    nextToken = yylex();

    if (!first_of_block())
        throw "18: error in declaration part OR 17: 'BEGIN' expected";
    newProgramNode->blockPtr = block();

    --level;

   

    return newProgramNode;
}

BlockNode *block()
{
    output("BLOCK");
    BlockNode *newBlockNode = new BlockNode(level);
    ++level;

    if (nextToken == TOK_VAR)
    {
        nextToken = yylex();

        while (nextToken == TOK_IDENT)
        {
            output("IDENTIFIER");
            string varName = yytext;
            if (symbolTable.find(varName) != symbolTable.end()) {
                yytext = const_cast<char*>(";");
                throw "101: identifier declared twice";
            } else {
                symbolTable.insert(varName);
            }

            nextToken = yylex(); // Consume IDENT

            if (nextToken != TOK_COLON)
                throw "5: ':' expected";
            output("COLON");
            nextToken = yylex();

            if (nextToken != TOK_INTEGER && nextToken != TOK_REAL)
                throw "10: error in type";
            output("TYPE");
            string varType = yytext;
            nextToken = yylex();

            if (nextToken != TOK_SEMICOLON)
                throw "14: ';' expected";
            output("SEMICOLON");
            nextToken = yylex();
        }
    }

    if (nextToken != TOK_BEGIN)
        throw "17: 'BEGIN' expected";

    newBlockNode->stmtPtr = statement();

    --level;
    return newBlockNode;
}


StatementNode *statement()
{
    StatementNode *newStatementNode = nullptr;

    if (first_of_assignment_stmt())
    {
        newStatementNode = assignment_stmt();
    }
    else if (first_of_compound_stmt())
    {
        newStatementNode = compound_stmt();
    }
    else if (first_of_if_stmt())
    {
        newStatementNode = if_stmt();
    }
    else if (first_of_while_stmt())
    {
        newStatementNode = while_stmt();
    }
    else if (first_of_read_stmt())
    {
        newStatementNode = read_stmt();
    }
    else if (first_of_write_stmt())
    {
        newStatementNode = write_stmt();
    }

    return newStatementNode;
}

AssignmentStmtNode *assignment_stmt()
{
    output("STATEMENT");
    
    AssignmentStmtNode *newAssignmentStmtNode = new AssignmentStmtNode(level);
    ++level;

    string varName = yytext; 

    if (symbolTable.find(varName) == symbolTable.end())
        throw "101: identifier declared twice";

    output("IDENTIFIER");
   
    newAssignmentStmtNode->varName = new string(varName);
    nextToken = yylex(); 

    if (nextToken != TOK_ASSIGN)
        throw "51: ':=' expected";
    output("ASSIGN");
    string assignOp = yytext; 
    newAssignmentStmtNode->assignOp = new string(assignOp);
    nextToken = yylex(); 

    newAssignmentStmtNode->exprPtr = expression(); 

    --level;
   

    return newAssignmentStmtNode;
}

CompoundStmtNode *compound_stmt()
{
    output("BEGIN");
   
    CompoundStmtNode *newCompoundStmtNode = new CompoundStmtNode(level);
    ++level;
    nextToken = yylex(); 

    while (first_of_statement())
    {
        newCompoundStmtNode->stmts.push_back(statement());

        if (nextToken == TOK_SEMICOLON)
        {
            output("SEMICOLON");
            nextToken = yylex(); 
        }
    }

    --level;
    output("END");
 
    nextToken = yylex(); 

    return newCompoundStmtNode;
}

IfStmtNode *if_stmt()
{
    output("STATEMENT");
    
    IfStmtNode *newIfStmtNode = new IfStmtNode(level);
    ++level;
    nextToken = yylex(); 

    newIfStmtNode->exprPtr = expression();

    if (nextToken != TOK_THEN)
        throw "52: 'THEN' expected";
    --level;
    output("THEN");
    
    ++level;
    nextToken = yylex(); 

    if (nextToken == TOK_BEGIN)
        output("STATEMENT");
    newIfStmtNode->thenStmtPtr = statement();

    --level;
   

    if (nextToken == TOK_ELSE)
    {
        output("ELSE");
        
        ++level;
        nextToken = yylex(); 

        if (nextToken == TOK_BEGIN)
            output("STATEMENT");
        newIfStmtNode->elseStmtPtr = statement();

        --level;
       
    }
    else
    {
        --level;
    }

   

    if (nextToken == TOK_SEMICOLON)
    {
        output("SEMICOLON");
        nextToken = yylex(); 
    }

    return newIfStmtNode;
}

WhileStmtNode *while_stmt()
{
    output("STATEMENT");
   
    WhileStmtNode *newWhileStmtNode = new WhileStmtNode(level);
    ++level;
    nextToken = yylex(); // Consume 'WHILE'

    newWhileStmtNode->exprPtr = expression(); 

    if (nextToken == TOK_BEGIN)
        output("STATEMENT");
    newWhileStmtNode->stmtPtr = statement(); 

    --level;
   

    return newWhileStmtNode;
}

ReadStmtNode *read_stmt()
{
    output("STATEMENT");
  
    ReadStmtNode *newReadStmtNode = new ReadStmtNode(level);
    ++level;

    nextToken = yylex(); 

    if (nextToken != TOK_OPENPAREN)
        throw "9: '(' expected";
    output("OPENPAREN");
    nextToken = yylex(); 

    if (nextToken != TOK_IDENT)
        throw "2: identifier expected";
    string varName = yytext; 
    output("IDENTIFIER");
    newReadStmtNode->dataPtr = new string(varName);
    nextToken = yylex(); 

    if (nextToken != TOK_CLOSEPAREN)
        throw "4: ')' expected";
    output("CLOSEPAREN");
    nextToken = yylex(); 

    --level;
    

    if (nextToken == TOK_SEMICOLON)
    {
        output("SEMICOLON");
        nextToken = yylex(); 
    }

    return newReadStmtNode;
}

WriteStmtNode *write_stmt()
{
    output("STATEMENT");
   
    WriteStmtNode *newWriteStmtNode = new WriteStmtNode(level);
    ++level;

    nextToken = yylex(); 

    if (nextToken != TOK_OPENPAREN)
        throw "9: '(' expected";
    output("OPENPAREN");
    nextToken = yylex(); 

    if (nextToken != TOK_IDENT && nextToken != TOK_STRINGLIT)
        throw "134: illegal type of operand(s)";
    string varName = yytext; 
    output("WRITE");
   
    newWriteStmtNode->dataPtr = new string(varName);
    nextToken = yylex(); 

    if (nextToken != TOK_CLOSEPAREN)
        throw "4: ')' expected";
    output("CLOSEPAREN");
    nextToken = yylex(); 

    --level;

    return newWriteStmtNode;
}

ExpressionNode *expression()
{
    output("EXPRESSION");
   
    ExpressionNode *newExpressionNode = new ExpressionNode(level);
    ++level;

    newExpressionNode->firstSimpleExp = simple_exp();

    if (nextToken == TOK_EQUALTO || nextToken == TOK_LESSTHAN || nextToken == TOK_GREATERTHAN || nextToken == TOK_NOTEQUALTO)
    {
        if (nextToken == TOK_EQUALTO)
        {
            output("EQUAL");
           
            newExpressionNode->restSimpleExpOps.push_back(nextToken);
            nextToken = yylex(); 
        }
        else if (nextToken == TOK_LESSTHAN)
        {
            output("LESSTHAN");
            
            newExpressionNode->restSimpleExpOps.push_back(nextToken);
            nextToken = yylex(); 
        }
        else if (nextToken == TOK_GREATERTHAN)
        {
            output("GREATERTHAN");
            newExpressionNode->restSimpleExpOps.push_back(nextToken);
            nextToken = yylex(); 
        }
        else if (nextToken == TOK_NOTEQUALTO)
        {
            newExpressionNode->restSimpleExpOps.push_back(nextToken);
            
          
            nextToken = yylex(); 
        }



        newExpressionNode->secondSimpleExp = simple_exp();
    }

    --level;
   

    return newExpressionNode;
}

SimpleExpNode *simple_exp()
{
    output("SIMPLE_EXP");
    
    SimpleExpNode *newSimpleExpNode = new SimpleExpNode(level);
    ++level;

    newSimpleExpNode->firstTerm = term();

    while (nextToken == TOK_PLUS || nextToken == TOK_MINUS || nextToken == TOK_OR)
    {
        if (nextToken == TOK_PLUS)
        {
            output("PLUS");
           
            newSimpleExpNode->restTermOps.push_back(nextToken);
            nextToken = yylex(); 
            newSimpleExpNode->restTerms.push_back(term());
        }
        else if (nextToken == TOK_MINUS)
        {
            output("MINUS");
           
            newSimpleExpNode->restTermOps.push_back(nextToken);
            nextToken = yylex(); 
            newSimpleExpNode->restTerms.push_back(term());
        }
        else if (nextToken == TOK_OR)
        {
            output("OR");
           
            newSimpleExpNode->restTermOps.push_back(nextToken);
            nextToken = yylex(); 
            newSimpleExpNode->restTerms.push_back(term());
        }
    }

    --level;


    return newSimpleExpNode;
}

TermNode *term()
{
    output("TERM");
    
    TermNode *newTermNode = new TermNode(level);
    ++level;

    newTermNode->firstFactor = factor();

    while (nextToken == TOK_MULTIPLY || nextToken == TOK_DIVIDE || nextToken == TOK_AND)
    {
        if (nextToken == TOK_MULTIPLY)
        {
            output("MULTIPLY");
           
            newTermNode->restFactorOps.push_back(nextToken);
            nextToken = yylex(); 
            newTermNode->restFactors.push_back(factor());
        }
        else if (nextToken == TOK_DIVIDE)
        {
            output("DIVIDE");
           
            newTermNode->restFactorOps.push_back(nextToken);
            nextToken = yylex(); 
            newTermNode->restFactors.push_back(factor());
        }
        else if (nextToken == TOK_AND)
        {
            output("AND");
            
            newTermNode->restFactorOps.push_back(nextToken);
            nextToken = yylex(); 
            newTermNode->restFactors.push_back(factor());
        }
    }

    --level;
    

    return newTermNode;
}

FactorNode *factor()
{
    output("FACTOR");

    ++level;
    FactorNode *newFactorNode = nullptr;

    if (nextToken == TOK_INTLIT)
    {
        output("INTLIT");
        
        newFactorNode = new IntLitNode(level-1, atoi(yytext));
        nextToken = yylex(); 
    }
    else if (nextToken == TOK_FLOATLIT)
    {
        output("FLOATLIT");
       
        newFactorNode = new FloatLitNode(level-1, atof(yytext));
        nextToken = yylex();
    }
    else if (nextToken == TOK_IDENT)
    {
        output("IDENTIFIER");
     

        if (symbolTable.find(yytext) == symbolTable.end())
            throw "104: identifier not declared";

        newFactorNode = new IdNode(level-1, string(yytext));
        nextToken = yylex(); 
    }
    else if (nextToken == TOK_OPENPAREN)
    {
        output("OPENPAREN");
       
        nextToken = yylex(); 

        newFactorNode = new NestedExprNode(level-1, expression());

        if (nextToken != TOK_CLOSEPAREN)
            throw "4: ')' expected";
        output("CLOSEPAREN");
        nextToken = yylex(); 
    }
    else if (nextToken == TOK_NOT)
{
    output("NOT");

    NotNode* newNotNode = new NotNode(level - 1);
    nextToken = yylex(); 

    newNotNode->factorPtr = factor();
    newFactorNode = newNotNode;
}
else if (nextToken == TOK_MINUS)
{
    output("MINUS");

    MinusNode* newMinusNode = new MinusNode(level - 1);
    nextToken = yylex(); 

    newMinusNode->factorPtr = factor();
    newFactorNode = newMinusNode;
}


    --level;
 

    return newFactorNode;
}

bool first_of_program()
{
    return nextToken == TOK_PROGRAM;
}

bool first_of_block()
{
    return nextToken == TOK_VAR || nextToken == TOK_BEGIN;
}

bool first_of_statement()
{
    return nextToken == TOK_IDENT || nextToken == TOK_BEGIN ||
           nextToken == TOK_IF || nextToken == TOK_WHILE ||
           nextToken == TOK_READ || nextToken == TOK_WRITE;
}

bool first_of_assignment_stmt()
{
    return nextToken == TOK_IDENT;
}

bool first_of_compound_stmt()
{
    return nextToken == TOK_BEGIN;
}

bool first_of_if_stmt()
{
    return nextToken == TOK_IF;
}

bool first_of_while_stmt()
{
    return nextToken == TOK_WHILE;
}

bool first_of_read_stmt()
{
    return nextToken == TOK_READ;
}

bool first_of_write_stmt()
{
    
    return nextToken == TOK_WRITE;
}

bool first_of_expression()
{
    return nextToken == TOK_IDENT || nextToken == TOK_INTLIT ||
           nextToken == TOK_FLOATLIT || nextToken == TOK_OPENPAREN;
}
