#ifndef AND_H
#define AND_H

#include "operators.h"

class And : public operators
{
public:
    And():operators(){} // Constructor
    And(base* left, base* right): operators(left, right){} // Overload constructor
    bool execute() // Implement the virtual function
    {
        if(left->execute() == true)
        {
            return right->execute();
        }
        else
        {
            return false;
        }
    }
};

#endif // AND_H

