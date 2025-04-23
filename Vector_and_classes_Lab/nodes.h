

//*****************************************************************************
// purpose:  
//
//  author: Tichafa Andrew Rinomhota
//*****************************************************************************

#ifndef NODES_H
#define NODES_H

#include <iostream>
#include <string>

using namespace std;

// Abstract class. Base class for StringNode, IntegerNode, and FloatNode
//
// Do NOT change this class
class DataNode {
public:
    virtual void printTo(ostream &os) = 0; // pure virtual method, makes the class Abstract
    virtual ~DataNode();                   // labeling the destructor as virtual allows 
	                                       // the subclass destructors to be called
};
ostream& operator<<(ostream&, DataNode&);  // print method
// ---------------------------------------------------------------------
// For StringNode class:
class StringNode : public DataNode {
    public:
        string* mystring = nullptr;
    
        // Constructor
        StringNode(const string& s);
        
        // Destructor
        ~StringNode();
        
        // printTo method for double dispatch
        void printTo(ostream &os) override;
        
        // Get the string value for output in destructor
        string getValue() const;
    };
    
    class IntegerNode : public DataNode {
    public:
        int myinteger = 0;
    
        // Constructor
        IntegerNode(int i);
        
        // Destructor
        ~IntegerNode();
        
        // printTo method for double dispatch
        void printTo(ostream &os) override;
        
        // Get the integer value for output in destructor
        int getValue() const;
    };
    
    class FloatNode : public DataNode {
    public:
        float myfloat = 0.0;
    
        // Constructor
        FloatNode(float f);
        
        // Destructor
        ~FloatNode();
        
        // printTo method for double dispatch
        void printTo(ostream &os) override;
        
        // Get the float value for output in destructor
        float getValue() const;
    };
    #endif /* NODES_H */


    
