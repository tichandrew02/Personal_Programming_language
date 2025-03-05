#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

extern "C"
{
  extern int   yylex();      // the generated lexical analyzer
  extern char *yytext;       // text of current lexeme
}

int        nextToken = 0;    // next token to process
static int level = 0;        // current parse tree level

// Production functions
bool firstOf_sentence();
bool firstOf_noun_phrase();
bool firstOf_adjective_phrase();
bool firstOf_verb_phrase();
void  noun_phrase();
void  verb_phrase();
void  adjective_phrase();

//*****************************************************************************
// Indent to reveal tree structure
string psp( void ) { // Stands for p-space, but I want the name short
  string str("");
  for(int i = 0; i < level; i++)
    str += "|  ";
  return str;
}
//*****************************************************************************
// Get the next lexeme (word in sentence)
int lex() 
{
  char* token_str;  // point to the logical name of the token

  nextToken = yylex();
  if( nextToken == TOK_EOF ) {
    yytext[0] = 'E'; yytext[1] = 'O'; yytext[2] = 'F'; yytext[3] = 0;   
  }

  // Determine the logical name of the lexeme
  switch( nextToken )
  {
    case NOUN:            token_str = (char*)"NOUN"; break;
    case ADJECTIVE:       token_str = (char*)"ADJECTIVE"; break;
    case VERB:            token_str = (char*)"VERB"; break;
    case ADVERB:          token_str = (char*)"ADVERB"; break;
    case ARTICLE:         token_str = (char*)"ARTICLE"; break;
    case POSSESSIVE:      token_str = (char*)"POSSESSIVE"; break;

    case TOK_UNKNOWN:     token_str = (char*)"TOK_UNKNOWN"; break;

    default:              token_str = (char*)"=== unmapped token name ===";
  }

  cout << psp() << "next lexeme: |" << yytext << "|, token: " << token_str << endl;
  return nextToken;
}
//*****************************************************************************
// Report what we found
void output( string what ) {
  cout << psp() << "found " << what << ": |" << yytext << "|" << endl;
}
//*****************************************************************************
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
void sentence() 
{
  if( firstOf_sentence() == false )
    throw( "<sentence> did not start with an article or possessive." );

  cout << "enter <sentence>" << endl;
  ++level;

  /* TODO: Add code here... */ 

      noun_phrase();
  		verb_phrase();
  		noun_phrase();

  --level;
  cout << "exit <sentence>" << endl;
} 
//*****************************************************************************
bool firstOf_sentence()
{
  	if (nextToken == ARTICLE || nextToken == POSSESSIVE)
  	{
  		return true;
  	}
  	else
  	{
  		return false;
  	}
}

/*
    TODO: Add functions for the other grammar productions...
*/

void noun_phrase()
{
  static int thisCount = 1;
  int currentNoun = thisCount++;
	if (firstOf_noun_phrase() == false)
	{
		throw("<noun phrase> did not start with an article or possessive.");
	}
	
	cout << psp() << "enter <noun phrase> " << currentNoun <<endl;
  level++;
	
	if (firstOf_noun_phrase() == true)
	{
		adjective_phrase();
		output("NOUN");
		lex();
	}
	level--;
	cout << psp() << "exit <noun phrase> " <<  currentNoun << endl;
}

bool firstOf_noun_phrase()
{
	if (nextToken == ARTICLE || nextToken == POSSESSIVE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void adjective_phrase()
{
  static int thisCount = 1;
  int currentAdjective = thisCount++;
	if (firstOf_adjective_phrase() == false)
	{
		throw("<adjective phrase> did not start with an article or possessive.");
	}	
	
	cout << psp() << "enter <adjective phrase> " << currentAdjective << endl;
  level++;
	
	if (firstOf_adjective_phrase() == true)
	{
		if (nextToken == ARTICLE)
		{
			output("ARTICLE");
			lex();
		}
		else if (nextToken == POSSESSIVE)
		{
			output("POSSESSIVE");
			lex();
		}
		
	}

	output("ADJECTIVE");
	lex();

	level--;
	cout << psp() << "exit <adjective phrase> " <<  currentAdjective << endl;
}

bool firstOf_adjective_phrase()
{
	if (nextToken == ARTICLE || nextToken == POSSESSIVE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void verb_phrase()
{
  static int thisCount = 1;
  int currentVerb = thisCount++;
	if (firstOf_verb_phrase() == false)
	{
    	throw("<verb phrase> did not start with a verb or an adverb.");		
	}
	
	cout << psp() << "enter <verb phrase> " << currentVerb << endl;
  level++;
	
	if (firstOf_verb_phrase() == true)
	{
		if (nextToken == VERB)
		{
			output("VERB");
			lex();
		}
		else if (nextToken == ADVERB)
		{
			output("ADVERB");
			lex();
			verb_phrase();
		}
	}
  level--;
	cout << psp() << "exit <verb phrase> " << currentVerb << endl;
  
}

bool firstOf_verb_phrase()
{
	if (nextToken == VERB || nextToken == ADVERB)
	{
    	return true;
	}
	else
  	{
    	return false;
    }
}