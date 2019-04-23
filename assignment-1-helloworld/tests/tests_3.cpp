#include "gtest/gtest.h"
#include "../src/shell.h"
TEST(OutputRedirectionTest, Part_1) {
    string test  = "echo this is test.txt file > test.txt";
    base* c = new Shell(test);
    EXPECT_EQ(true, c->execute());
}

TEST(OutputRedirectionTest, Part_2) {
    char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echo This is text.txt file. > text.txt";
    base* c = new Shell(test_val[1]);
    EXPECT_EQ(true, c->execute());
}

TEST(Output2RedirectionTest, Part_1) {
    char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "ls >> test.txt";
    base* c = new Shell(test_val[1]);
    EXPECT_EQ(true, c->execute());
}

TEST(Output2RedirectionTest, Part_2) {
    char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "cat test.txt >> text.txt";
    base* c = new Shell(test_val[1]);
    EXPECT_EQ(true, c->execute());
}

TEST(InputRedirectionTest, Part_1_a) {
    char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "wc -l test.txt";
    base* c = new Shell(test_val[1]);
    EXPECT_EQ(true, c->execute());
}

TEST(InputRedirectionTest, Part_2_a) {
    char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echo test.txt";
    base* c = new Shell(test_val[1]);
    EXPECT_EQ(true, c->execute());
}

TEST(InputRedirectionTest, Part_2_b) {
    char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echo test > test.txt";
    base* c = new Shell(test_val[1]);
    EXPECT_EQ(true, c->execute());
}

TEST(ComplexRedirectionTest, Part_1) {
    char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "cat < text.txt | tr A-Z a-z | tee file1.txt | tr a-z A-Z > file2.txt";
    base* c = new Shell(test_val[1]);
    EXPECT_EQ(true, c->execute());
}

TEST(ComplexRedirectionTest, Part_2) {
    char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "cat < test.txt | tr a-z A-Z > file3.txt";
    base* c = new Shell(test_val[1]);
    EXPECT_EQ(true, c->execute());
}

TEST(ComplexRedirectionTest, Part_3) {
    char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "cat < file3.txt | tr A-L a-l | tee file4.txt | tr M-Z m-z >> file3.txt";
    base* c = new Shell(test_val[1]);
    EXPECT_EQ(true, c->execute());
}
