#include "io.h"
#include "pipe.h"
#include <fcntl.h>
IO::IO(string commandline, int pipefd[2])
{
    stringstream ss;
    ss.str(commandline);
    string Acommand;
    while(ss >> Acommand)
    {
        char* AnotherCommand = new char[Acommand.length() +1 ];
        strcpy(AnotherCommand, Acommand.c_str());
        line[size ++] = AnotherCommand;
        Acommand = "";
    }
    line[size] = nullptr;
    this->commandline = commandline;
    this->pipefd[0] = pipefd[0];
    this->pipefd[1] = pipefd[1];
}
int IO::pipfd0(){return pipefd[0];}
void IO::setIN(int in){ pipefd[0] = in;}
void IO::setOUT(int out){pipefd[1] = out;}
int IO::pipfd1(){return pipefd[1];}
bool IO::execute()
{
    Put* right;
    size_t pipe = commandline.size()-1;
    for(size_t i = commandline.size() -1; i > 0; i--)
    {

        if(commandline[i] == '|')
        {
            string lefts = commandline.substr(0, i);
            string rights = commandline.substr(i+1);
            IO *left = new IO(lefts,pipefd);
            if(rights.find_first_of('<') < rights.size())
                right = new Input(rights,pipefd);
            else if(rights.find_first_of('>') < rights.size())
            {
                right = new Output(rights,pipefd);
            }
            else
                right = new single(rights,pipefd);
            Pipe* newPipe = new Pipe(left,right);
            return newPipe->execute(pipefd);

        }
    }

    if(commandline.find_first_of('<') < commandline.size())
    {
        right = new Input(commandline, pipefd);
    }
    else if(commandline.find_first_of('>') < commandline.size())
    {
        right = new Output(commandline, pipefd);
    }
    else right = new single(commandline, pipefd);
    return right->execute(pipefd);

}

