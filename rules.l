/******************************************************************* 
Name: Tichafa Rinomhota Student NetID: tar351
Course: CSE 4714 Assignment: Part 1
Programming Environment: Visual Studio Code 
Purpose of File: Contains the rules to write a lexical analyzer for a subset of the language TIPS
*********************************************************************/

%option yylineno
%option noyywrap
%{
#include "lexer.h"

// global variable to hold current line number being read
int line_number = 1;
%}

%%

 /* Eat any whitespace, will need to be modified to count lines */

"{"[^\n]*"}"               /* nop */
[ \t\r]+                    /* nop */

\n {line_number++; }



BEGIN                      { return TOK_BEGIN; }
BREAK                      { return TOK_BREAK; }
CONTINUE                { return TOK_CONTINUE; }
DOWNTO                     { return TOK_DOWNTO; }
ELSE                       { return TOK_ELSE; }
END                        { return TOK_END; }
FOR                        { return TOK_FOR; }
IF                         { return TOK_IF; }
LET                        { return TOK_LET; }
PROGRAM                    { return TOK_PROGRAM; }
READ                       { return TOK_READ; }
THEN                       { return TOK_THEN; }
TO                         { return TOK_TO; }
VAR                        { return TOK_VAR; }
WHILE                      { return TOK_WHILE; }
WRITE                      { return TOK_WRITE; }

INTEGER                     { return TOK_INTEGER; }
REAL                        { return TOK_REAL; }

;                           { return TOK_SEMICOLON; }
:                           { return TOK_COLON; }
"("                           { return TOK_OPENPAREN; }
")"                           { return TOK_CLOSEPAREN; }
"+"                           { return TOK_PLUS; }
"-"                           { return TOK_MINUS; }
"*"                           { return TOK_MULTIPLY; }
"/"                           { return TOK_DIVIDE; }
:=                          { return TOK_ASSIGN; }
=                           { return TOK_EQUALTO; }
"<"                           { return TOK_LESSTHAN; }
">"                           { return TOK_GREATERTHAN; }
"<>"                          { return TOK_NOTEQUALTO; }
MOD                         { return TOK_MOD; }
NOT                         { return TOK_NOT; }
OR                          { return TOK_OR; }
AND                         { return TOK_AND; }

[A-Z][A-Z0-9]{0,7}          { return TOK_IDENT; }
[A-Z][A-Z0-9]{8,}           { return TOK_UNKNOWN; }
[0-9]+                      { return TOK_INTLIT; }
[0-9]+"."[0-9]+             { return TOK_FLOATLIT; }
'[^\n]{0,80}'               { return TOK_STRINGLIT; }
'[^\n']'{81,}'              { return TOK_UNKNOWN; }

 /* Found an unknown character */

.         { return TOK_UNKNOWN; }

 /* Recognize end of file */

<<EOF>>   { return TOK_EOF; }
