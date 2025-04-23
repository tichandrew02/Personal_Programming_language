//*****************************************************************************
// purpose: Driver for Project Part 3 (parser for TIPS)
// version: Fall 2024
//*****************************************************************************

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <iostream>
#include <cstring>
#include "lexer.h"
#include "parser.h"
#include "parse_tree_nodes.h"

using namespace std;

extern "C" {
    // Instantiate global variables
    extern FILE *yyin;     // input stream
    extern FILE *yyout;    // output stream
    extern int   yyleng;   // length of current lexeme
    extern char *yytext;   // text of current lexeme
    extern int   yylineno; // line number for current lexeme
    extern int   yylex();  // the generated lexical analyzer
    extern int yylex_destroy();  //
}


// Needed global variables
extern int nextToken; // token returned from yylex

//*****************************************************************************
// The main processing loop
//
int main(int argc, char *argv[])
{
    bool printTree = true;
    printDelete = true;  // <-- add this line


    if (argc > 1)
    {
        printf("INFO: Using the %s file for input\n", argv[1]);
        yyin = fopen(argv[1], "r");
    }
    else {
        printf("INFO: Using the sample.pas file for input\n");
        yyin = fopen("sample.pas", "r");
    }


    if (!yyin)
    {
        printf("ERROR: input file not found\n");
        return EXIT_FAILURE;
    }

    // Set the output stream
    yyout = stdout;


    ProgramNode *root = nullptr;

     // Get the first token
    nextToken = yylex();

    // Fire up the parser!
    try
    {

        // Process the expected production
        root = program();
        //factor(); // Build bottom-up to <expression>
        if (nextToken != TOK_EOF)
            throw "end of file expected, but there is more here!";
    }
    catch (char const *errmsg)
    {
        cout << endl
             << "***ERROR:" << endl;
        cout << "On line number " << yylineno << ", near |" << yytext << "|, error type ";
        cout << errmsg << endl;
        return EXIT_FAILURE;
    }

    yylex_destroy();

    // Tell the world about our success!!
    cout << endl
         << "=== GO BULLDOGS! Your parse was successful! ===" << endl;

    if (printTree)
    {
        cout << endl
             << "*** Print the Tree ***" << endl;
        cout << *root << endl
             << endl;
    }

    // Print out the symbol table
    cout << endl
         << "*** User Defined Symbols ***" << endl;
    set<string>::iterator it;
    for (it = symbolTable.begin(); it != symbolTable.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << endl << "*** Delete the Tree ***" << endl;
    delete root;
    root = nullptr;

    return EXIT_SUCCESS;
}
