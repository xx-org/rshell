#ifndef PIPE_H
#define PIPE_H
#include "io.h"

class Put
{
public:
    Put(string input, int pipefd[2]);
    virtual bool execute(int pipefd[2]) = 0;
protected:
    char* input[30];
    string inputs;
    int pipefd[2];
    size_t size = 0;

};

class Input : public Put
{
public:
    Input(string input, int pipefd[2]) ;
    bool execute(int pipefd[2]);
};

class Output : public Put
{
public:
    Output(string input, int pipefd[2]);
    bool execute(int pipefd[2]);
};
class single : public Put
{
public:
    single(string input, int pipefd[2]);
    bool execute(int pipefd[2]);
};

class Pipe
{
public:
    Pipe(IO *left, Put *right);
    bool execute(int pipefd[2]);
protected:
    Put *right;
    IO *left;
};


#endif // PIPE_H

