# Assignment 4

## Introduction
The remote shell (rshell) is a program based on command line. It can execute appropriate commands. This program was developed by Jia Xie and Xichao Wang in Fall 2018.

## Installation
$ git clone https://github.com/cs100/assignment-1-helloworld.git

$ cd assignment-1-helloworld/

$ git checkout hw2

$ make

$ ./rshell

## Function
Our program can execute multiple different commands. The user can use "||", "&&", or ";" to separate the commands. The program would wait for next command when finish the prior commands until the user input "exit". 

| && | the next command is executed only if the first one succeeds.

| || | the next command is executed only if the first one fails.

| ;  | the next command is always executed.

| #  | everything after this sigend is consider a comment

## Example
xwang296@hammer$                                // Enter your command here:

xwang296@hammer$ echo Hello && echo World       // If we enter "echo Hello && echo World".

Hello                                           // It prints "Hello" and "World".

World

xwang296@hammer$ echo one || echo two           // If we enter "echo one || echo two".

one                                             // It prints "one" only.

xwang296@hammer$ echoe one || echo two          // If we enter "echoe one || echo two". The command is invalid.

two                                             // It prints "two" only.

xwang296@hammer$ echo one; echo two; echo three // If we enter "echo one; echo two; echo three"

one                                             // It prints "one", "two", and "three" separately.

two

three

xwang296@hammer$ echo one # two                 // If we enter "echo one # two".

one                                             //It prints "one" only.

## Fixed known bugs
1. When using "&&" and "||" to separate the commands, they had the same results. 
2. When we inputed "exit" with one other command,the "exit" would not be executed.
3. If any command include "exit", such as "exit()", it would also execute "exit".
4. When we inputed "# hello", the program exied.
