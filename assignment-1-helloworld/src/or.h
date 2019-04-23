#ifndef OR_H
#define OR_H

#include "operators.h"

class Or: public operators
{
public:
    Or() : operators(){} // Constructor
    Or(base* left, base* right) : operators(left, right){} // Overload Constructor
    bool execute() // Implement the virtual function for Or
    {
        if(left->execute() == false)
        {
            return right->execute();
        }
        else
        {
            return true;
        }
    }
};

#endif // OR_H

