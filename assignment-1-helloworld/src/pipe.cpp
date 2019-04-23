#include "pipe.h"
#include <sys/stat.h>
#include <fstream>
#include <fcntl.h>
Put::Put(string input, int pipefd[2])
{
    inputs = input;
    stringstream ss;
    ss.str(input);
    string Acommand;
    while(ss >> Acommand)
    {
        char* AnotherCommand = new char[Acommand.length() +1 ];
        strcpy(AnotherCommand, Acommand.c_str());
        this->input[size ++] = AnotherCommand;
        Acommand = "";
    }
    this->pipefd[0] = pipefd[0];
    this->pipefd[1] = pipefd[1];
    this->input[size] = nullptr;
}

Input::Input(string input, int pipefd[2]) : Put(input, pipefd){}
bool Input::execute(int pipefd[2])
{
    string newinput;
    struct stat info;
    for(size_t i = 0 ; i < size; i ++)
    {
        string temp = "<";
        if(input[i] == temp)
        {
            if(i+1<size&&stat(input[i+1],&info) == 0)
            {
                if(!(info.st_mode & S_IFDIR))
                {
                    pipefd[0] = open(input[i+1], O_RDONLY);
                    break;
                }else
                {
                    perror("inputfile");
                    return false;
                }
            }else
            {
                perror("inputfile");
                return false;
            }
        }
        newinput += " ";
        newinput += input[i];
    }
    Put* p = new single(newinput, pipefd);
    if(p->execute(pipefd))
    {
        return true;
    }
    else
    {
        perror("command");
        return false;
    }
}


Output::Output(string input, int pipefd[2]) : Put(input, pipefd){}
bool Output::execute(int pipefd[2])
{
    string newinput = "";
    for(size_t i = 0 ; i < size; i ++)
    {
        string temp = ">";
        string temp2 = ">>";
        if(input[i] == temp)
        {
            pipefd[1] = open(input[i+1], O_WRONLY| O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            break;
        }else if(input[i] == temp2)
        {
            pipefd[1] = open(input[i+1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            break;
        }
        newinput += " ";
        newinput += input[i];

    }
    if(newinput == "")
        return false;
    IO* p = new IO(newinput, pipefd);
    return p->execute();

}

single::single(string input, int pipefd[2]) : Put(input, pipefd){}
bool single::execute(int pipefd[2])
{
    pid_t pid, pr;
    int status;
    pid = fork();
    
    if(pid < 0)
    {
        perror("fork");
        return false;
    }

    if(pid == 0)
    {
        dup2(pipefd[0], 0);
        dup2(pipefd[1], 1);
        if(execvp(input[0],input) == -1)
            perror("perror: command failed");
        exit(1);
    }else
    {
        pr = wait(&status);
        if(status == 0)
        {
            return true;
        }
        else if(status == 256)
        {
            return false;
        }
    }
}

Pipe::Pipe(IO* left, Put* right)
{
    this->left = left;
    this->right = right;
}



bool Pipe::execute(int pipefd[2])
{
    int fd[2];
    if(pipe(fd) < 0)
    {
        perror("pipe");
        return false;
    }

    left->setIN(pipefd[0]);
    left->setOUT(fd[1]);
    if(!left->execute())
    {
        return false;
    }
    close(fd[1]);
    pipefd[0] = fd[0];
    if(!right->execute(pipefd))
        return false;
    return true;

}

