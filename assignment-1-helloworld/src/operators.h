#ifndef OPERATORS_H
#define OPERATORS_H

#include "base.h"

class operators : public base
{
public:
    operators() : base(){} // Constructor
    operators(base* left, base* right) // Overload contructor
    {
        this->left = left;
        this->right = right;
    }
    virtual bool execute() = 0; // Pure virtual function

protected:
    base* left, *right;
};


#endif // OPERATORS_H
