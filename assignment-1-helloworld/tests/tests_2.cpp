#include "gtest/gtest.h"
#include "../src/shell.h"
TEST(Precedence_Operators_Example_Test, Part_1)
{
    char* test_val[3]; test_val[0] = "./rshell";
    test_val[1] = "(echo A && echo B) || (echo C && echo D)";
    Shell* c = new Shell(test_val[1]);
    EXPECT_EQ(true,c->execute());
}

TEST(Precedence_Operators_Example_Test, Part_2)
{
    char* test_val[3]; test_val[0] = "./rshell";
    test_val[1] = "echo A && echo B || echo C && echo D";
    Shell* c = new Shell(test_val[1]);
    EXPECT_EQ(true,c->execute());
}

TEST(Precedence_Operators_Test, Part_1)
{
    char* test_val[3]; test_val[0] = "./rshell";
    test_val[1] = "(echo A && echo B || echo C && echo D)";
    Shell* c = new Shell(test_val[1]);
    EXPECT_EQ(true,c->execute());
}

TEST(Precedence_Operators_Test, Part_2)
{
    char* test_val[3]; test_val[0] = "./rshell";
    test_val[1] = "(echo A && (echo B || echo C) && echo D)";
    Shell* c = new Shell(test_val[1]);
    EXPECT_EQ(true,c->execute());
}

TEST(Precedence_Operators_Test, Part_3)
{
    char* test_val[3]; test_val[0] = "./rshell";
    test_val[1] = "(echo A && ((echo B || echo C) && echo D))";
    Shell* c = new Shell(test_val[1]);
    EXPECT_EQ(true,c->execute());
}

TEST(Precedence_Operators_Test, Part_4)
{
    char* test_val[3]; test_val[0] = "./rshell";
    test_val[1] = "((echo A && ((echo B || echo C) && echo D)))";
    Shell* c = new Shell(test_val[1]);
    EXPECT_EQ(true,c->execute());
}

TEST(Precedence_Operators_Full_Test, Part_1)
{
    char* test_val[3]; test_val[0] = "./rshell";
    test_val[1] = "(echo A ; echo B || echo C) && (echo D ; echo E)";
    Shell* c = new Shell(test_val[1]);
    EXPECT_EQ(true,c->execute());
}

TEST(Precedence_Operators_Full_Test, Part_2)
{
    char* test_val[3]; test_val[0] = "./rshell";
    test_val[1] = "echo A && (echo B ; echo C || echo D) || echo E";
    Shell* c = new Shell(test_val[1]);
    EXPECT_EQ(true,c->execute());
}

TEST(Wrong_Precedence_Operators_Test, Part_1)
{
    char* test_val[3]; test_val[0] = "./rshell";
    test_val[1] = "((echo A)";
    Shell* c = new Shell(test_val[1]);
    EXPECT_EQ(false,c->execute());
}

TEST(Wrong_Precedence_Operators_Test, Part_2)
{
    char* test_val[3]; test_val[0] = "./rshell";
    test_val[1] = ")( echo A)(";
    Shell* c = new Shell(test_val[1]);
    EXPECT_EQ(false,c->execute());
}
