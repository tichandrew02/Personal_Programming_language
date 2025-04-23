###############################################################################
# purpose: makefile for Project Part 2
# author:  Joe Crumpton / Ed Swan
#
# 'make'        build executable file
# 'make clean'  removes all intermediate (lex.yy.c and *.o) and executable files
#
# This makefile purposely avoids macros to make the rules more clear.
# For more information about makefiles:
#      http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#      http://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
#      http://www.gnu.org/software/make/manual/make.html
#
###############################################################################

# variables used in the following rules
LEX      = flex
CXX      = g++
CC       = gcc
RM       = rm
# -g generate debug information for gdb
# -Wno-c++11-extensions silence the c++11 error warnings
# -std=c++11 assert that we are using c++11
CXXFLAGS = -g
CXXFLAGS = -g -Wno-c++11-extensions
CXXFLAGS = -g -std=c++11
CCFLAGS  = -g
# don't ever remove these files
.PRECIOUS = *.l *.h *.cpp [Mm]akefile

tips_parse: lex.yy.o driver.o parser.o parse_tree_nodes.o
	$(CXX) $(CXXFLAGS) -o tips_parse lex.yy.o driver.o parser.o parse_tree_nodes.o

#     -o flag specifies the output file
#
#     The above rule could be written with macros as
#        $(CXX) $(CXXFLAGS) -o $@ $^

driver.o: driver.cpp parser.h parse_tree_nodes.h lexer.h
	$(CXX) $(CXXFLAGS) -o driver.o -c driver.cpp
#      -c flag specifies stop after compiling, do not link

parser.o: parser.cpp parser.h lexer.h parse_tree_nodes.h
	$(CXX) $(CXXFLAGS) -o parser.o -c parser.cpp

parse_tree_nodes.o: parse_tree_nodes.cpp lexer.h
	$(CXX) $(CXXFLAGS) -o parse_tree_nodes.o -c parse_tree_nodes.cpp

lex.yy.o: lex.yy.c lexer.h
	$(CC) $(CCFLAGS) -o lex.yy.o -c lex.yy.c

lex.yy.c: rules.l lexer.h
	$(LEX) -o lex.yy.c rules.l

clean: 
	$(RM) *.o lex.yy.c tips_parse
#   delete all generated files	

ring:
	ls $(.PRECIOUS)
#   tell us what is precious here
