#ifndef IO_H
#define IO_H
#include "base.h"

class IO : public base
{
public:
    IO(string commandline, int pipefd[2]);
    bool execute();
    void setIN(int in);
    void setOUT(int out);
    int pipfd0();
    int pipfd1();
private:
    int pipefd[2];
    char* line[30];
    string commandline;
    size_t size;
    bool exePart(char *NewChar[]);

};

#endif // IO_H
