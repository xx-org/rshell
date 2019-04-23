#ifndef COMMAND_H
#define COMMAND_H

#include "smcl.h"
#include "or.h"
#include "and.h"
#include <sys/stat.h>

#include <fstream>

class command : public base
{
public:
    command() : base() {} // Constructor
    command(string commandline) // Overload constructor
    {
        setcommand(commandline);
    }
    ~command(){} // Destructor
    string getcommand(unsigned long i) // Return partial command
    {
        if(i<=size)
            return line[i];
        else return nullptr;
    }
    unsigned long getsize() // Return how many words in the command
    {
        return size;
    }

    virtual bool execute() = 0; // Pure virtual function
protected:
    char* line[10];
    unsigned long size = 0;
    void setcommand(string input) // Save commands separately
    {
        stringstream ss;
        ss.str(input);
        string Acommand;
        while(ss >> Acommand)
        {
            char* AnotherCommand = new char[Acommand.length() +1 ];
            strcpy(AnotherCommand, Acommand.c_str());
            line[size ++] = AnotherCommand;
            Acommand = "";
        }
        line[size] = nullptr;
    }
};


class singlecommand : public command
{
public:
    singlecommand() : command() {} // Constructor
    singlecommand(string commandline) : command(commandline) {} // Overload constructor
    bool execute() // Implement the virtual function, and run the single command.
    {

        pid_t pid, pr;
        int status;
        pid = fork();

        if(pid == 0)
        {
            if(execvp(line[0],line) == -1)
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
};

class testcommand : public command
{
public:
    testcommand() :command(){} // Constructor
    testcommand(string commandline) : command(commandline) {} // Overload contructor
    void withb() // Change '[' and ']' to "test" and "nullptr"
    {
        char *temp = new char[4];
        strcpy(temp, "test");
        line[0] = temp;
        size --;
        line[size] =  nullptr;
    }

    bool execute() // Implementthe virtual function, to check the flags of command.
    {
        if(size > 4)
        {
            cout << "wrong test command"<<endl;
            return false;
        }
        struct stat info;
         if(getcommand(1) == "-e")
         {
             if(stat(line[2], &info) == 0)
             {
                 cout << "(True)"<<endl;
                 return true;
             }else
             {
                 cout<< "(False)"<<endl;
                 return false;
             }
         }else if(getcommand(1) == "-f")
         {
             if(stat(line[2], &info) == 0)
             {
                 if(!(info.st_mode & S_IFDIR))
                 {
                     cout<< "(True)"<<endl;
                     return true;
                 }
                 else
                 {
                     cout<< "(False)"<<endl;
                     return false;
                 }
             }else
             {
                 return false;
             }
         }else if(getcommand(1) == "-d")
         {
             if(stat(line[2], &info) == 0)
             {
                 if(info.st_mode & S_IFDIR)
                 {
                     cout<< "(True)"<<endl;
                     return true;
                 }
                 else
                 {
                     cout<< "(False)"<<endl;
                     return false;
                 }
             }else
             {
                 cout<< "(False)"<<endl;
                 return false;
             }
         }else
         {
             if(size > 3)
             {
                 cout << "wrong test command"<<endl;
                 return false;
             }
             if(stat(line[1], &info) == 0)
             {
                 cout << "(True)"<<endl;
                 return true;
             }else
             {
                 cout<< "(False)"<<endl;
                 return false;
             }
         }
    }
};


#endif // COMMAND_H

