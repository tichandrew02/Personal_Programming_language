
// nodes.cpp
//*****************************************************************************
// purpose:  Declaration and implementation of DataNode base class and its derived classes:
//           IntegerNode, FloatNode, and StringNode. Defines constructors,
//           destructor, and printTo methods for each class. Also overloads
//           the << operator to print the contents of DataNode objects.
//
//  author:   Tichafa Andrew Rinomhota
//*****************************************************************************

#include "nodes.h"

// ---------------------------------------------------------------------
// Do NOT change this method
DataNode::~DataNode() {}

// Uses double dispatch to call the overloaded method printTo in the 
// DataNodes: StringNode, IntegerNode, and FloatNode
//
// Do NOT change this method
ostream& operator<<(ostream& os, DataNode& fn) {
    os << "Data: ";
    fn.printTo(os);
    return os;
}

// ---------------------------------------------------------------------
// Constructor, Destructor, and printTo method for StringNode
StringNode::StringNode(const string& str) {
    mystring = new string(str);
}

StringNode::~StringNode() {
    if (mystring != nullptr)
        cout << "Deleting DataNode:StringNode:" << *mystring << endl;
    delete mystring;
}

void StringNode::printTo(ostream& os) {
    os << "(string: " << *mystring << ") ";
}

// ---------------------------------------------------------------------
// Constructor, Destructor, and printTo method for IntegerNode
IntegerNode::IntegerNode(int val) : myinteger(val) {}

IntegerNode::~IntegerNode() {
    cout << "Deleting DataNode:IntegerNode:" << myinteger << endl;
}

void IntegerNode::printTo(ostream& os) {
    os << "(integer: " << myinteger << ") ";
}

// ---------------------------------------------------------------------
// Constructor, Destructor, and printTo method for FloatNode
FloatNode::FloatNode(float val) : myfloat(val) {}

FloatNode::~FloatNode() {
    cout << "Deleting DataNode:FloatNode:" << myfloat << endl;
}

void FloatNode::printTo(ostream& os) {
    os << "(float: " << myfloat << ") ";
}
