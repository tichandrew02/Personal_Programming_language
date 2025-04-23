//**************************************************************************
 
// Replace with appropriate header comment......

//**************************************************************************

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <set>
#include <iostream>
#include "parse_tree_nodes.h"

using namespace std;


extern set<string> symbolTable;

extern int nextToken;	
extern bool printParse; 

extern "C"
{
	
	extern int yylex();	 
	extern char *yytext; 
}


ProgramNode *program();


#endif /* PARSER_H */
