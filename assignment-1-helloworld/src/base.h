#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

class base
{
public:
    base(){} // Constructor
    virtual ~base() {} // Virtual destructor
    virtual bool execute() = 0; // Pure virtual function
};

#endif // BASE_H

