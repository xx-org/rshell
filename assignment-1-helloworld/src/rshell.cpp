#include "shell.h"
#include "pipe.cpp"
#include "io.cpp"
int main()
{
    Shell *newshell = new Shell();
    newshell->exe();

    return 0;
}
