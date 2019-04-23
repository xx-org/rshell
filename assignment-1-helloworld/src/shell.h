#ifndef SHELL_H
#define SHELL_H

#include "command.h"
#include "io.h"

class Shell : public base
{
protected:
    base* com;
public:
    Shell():base(){} // Constructor
    Shell(string input) // Overload constructor
    {
        this->input = input;
    }

    bool execute() // Implement the virtual function for shell class
    {
        return read_Input(input);
    }
    void exe() // The Program starting from here.
    {
        while(true)
        {
            read_Input(get_input());
        }
    }

private:
    string input;
    void printsign() // Extra credit part: Print sign
    {
        char hostname[10];
        char *username;
        if(gethostname(hostname, 10))
            perror("gethostname");
        username = getlogin();
        cout << username << "@" << hostname << "$ " ;
    }

    string get_input() // Get input and check valid parentheses
    {
        printsign();
        string input;
        getline(cin, input);
        if(input.find_first_of('#') < input.size())
	{
	    int i = input.find_first_of('#');
            input = input.substr(0,i);
        }
	return input;
    }

    bool is_com(string input, string com) // Check whether the input is an command
    {
        string temp;
        for(unsigned int i = 0; i < input.length(); i++)
            if(input[i] == ' ')
            {
                temp = input.substr(i+1);
                input = input.substr(0, i);
                input += temp;
            }
        if(input == com)
            return true;
        return false;
    }

    void exiting() // Print exiting message
    {
        cout << "successfully exiting"<<endl;
    }
    bool check_parentheses(string input, bool &hsp) // Check the input has valid parentheses or not
    {
        int check_point = 0;
        hsp = false;
        for (unsigned int i = 0; i < input.length(); i++)
        {
            if(input[i] == '(')
            {
                check_point++;
                hsp = true;
            }
            else if (input[i] == ')')
            {
                check_point--;
                hsp = true;
            }

            if(check_point < 0)
            {
                return false;
            }
        }
        if(check_point != 0)
        {
            return false;
        }

        return true;
    }
    void rm_p(string &input)
    {
        for(unsigned int i = 0; i < input.length() &&(input[i] == ' ' || input[i] == '(' ); i++)
        {
            if(input[i] == '(')
            {
                input = input.substr(i+1);
                break;
            }
        }
        for(unsigned int i = input.size() - 1; i >0 &&(input[i] == ' ' || input[i] == ')' ); i--)
        {
            if(input[i] == ')')
            {
                input = input.substr(0,i);
                break;
            }
        }
    }
    bool is_command(string input, string commandname)
    {
        if(commandname == "exit")
        {
	    string temp;
            stringstream ss;
            ss.str(input);
            string Acommand;
            while(ss >> Acommand)
		temp +=Acommand;
            if(temp == "exit")
                return true;

        }
        if(commandname == "IO")
        {
            stringstream ss;
            ss.str(input);
            string Acommand;
            while(ss >> Acommand)
                if(Acommand == "<" || Acommand == ">" || Acommand == ">>" || Acommand == "|")
                    return true;
        }
        if(commandname == "test")
        {
            stringstream ss;
            ss.str(input);
            string Acommand;
            ss >> Acommand;
            if(Acommand == "test")
                return true;
            else if(Acommand == "[" )
            {
                for(size_t i = input.size() - 1; i > 0 && (input[i] == ' ' || input[i] == ']'); i--)
                {
                    if(input[i] == ']')
                        return true;
                    else return false;
                }
            }
            return false;

        }else
            return false;
    }
    bool read_Input(string input)
    {
        string lefts, rights;
        base* left, *right;
        bool hasp;
        char sim;
        string temp;
        if(check_parentheses(input,hasp))
        {
            for(size_t i = input.size()-1; i > 0; i--)
            {
                if(input[i] == ';' || (input[i] == '&' && input[i-1] == '&') || (input[i] == '|' && input[i-1] == '|'))
                {
                    temp = input;
                    sim = input[i];
                    rights = input.substr(i+1);
                    lefts = input.substr(0,i-1);
                    if(lefts.find_first_of(";") > lefts.size() && lefts.find_first_of("&") > lefts.size()&& lefts.find_first_of("|") > lefts.size() )
                        if(hasp&& !check_parentheses(rights,hasp) && !check_parentheses(lefts,hasp))
                        {
                            rm_p(input);
                            i = input.find_first_of(";&|");
                            if(input[i] == ';')
                                rights = input.substr(i+1);
                            else rights = input.substr(i+2);
                            lefts = input.substr(0,i-1);

                        }
                    if(check_parentheses(rights,hasp) )
                    {
                        if(sim == ';')
                        {
                            lefts = input.substr(0, i-1);
                            right = new Shell(rights);
                            left = new Shell(lefts);
                            com = new SMCL(left,right);

                        }else
                        {
                            right = new Shell(rights);
                            left = new Shell(lefts);
                            if(sim == '&')
                                com = new And(left,right);
                            else com = new Or(left,right);
                        }
                        return com->execute();
                    }
                    else
                    {
                        input = temp;
                        continue;
                    }
                }
            }
            if(hasp)
            {
                rm_p(input);
                com = new Shell(input);
                return com->execute();
            }
            if(is_command(input, "test"))
                com = new testcommand(input);
            else if(is_command(input, "exit"))
                exit(2);
            else if(is_command(input, "IO"))
            {
                int pipefd[2];
                pipefd[1] = 1;
                pipefd[0] = 0;
                com = new IO(input, pipefd);
            }
            else
                com = new singlecommand(input);
            return com->execute();
        }
        else
        {
            cout << "The input has an uneven amount of parentheses." <<endl;
            return false;
        }

    }

};

#endif // SHELL_H

