#ifndef SMCL_H
#define SMCL_H

#include "operators.h"

class SMCL :public operators
{
public:
    SMCL() : operators(){} // Constructpr
    SMCL(base* left, base* right): operators(left, right){} // Overload Constructor
    bool execute() // Implement the virtual function for semicolon
    {
        left->execute();
        return right->execute();
    }
};

#endif // SMCL_H

