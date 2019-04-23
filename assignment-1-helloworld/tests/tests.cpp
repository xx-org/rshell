#include "gtest/gtest.h"
#include "../src/shell.h"
#include "../src/io.cpp"
#include "../src/pipe.cpp"
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

TEST(SingleCommandTest, Hello)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echo hello";
        command* c = new singlecommand(test_val[1]);
        EXPECT_EQ(true, c->execute());
	
}

TEST(SingleCommandTest, list)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "ls";
	command* c = new singlecommand(test_val[1]);
        EXPECT_EQ(true, c->execute());
}

TEST(And_Test, And_test_one)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echo hello && echo hi";
	base* c = new Shell(test_val[1]);
        EXPECT_EQ(true, c->execute());
}

TEST(And_Test, And_test_two)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "ls && echo Amazon";
	base* c = new Shell(test_val[1]);
        EXPECT_EQ(true, c->execute());
}

TEST(OR_Test, OR_test_one)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echo command_one || echo command_two";
	base* c = new Shell(test_val[1]);
        EXPECT_EQ(true, c->execute());
}

TEST(OR_Test, OR_test_two)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echoe command_one || echo command_two";
	base* c = new Shell(test_val[1]);
        EXPECT_EQ(true, c->execute());
}

TEST(SMCL_Test, SMCL_test_one)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echo hello ; echo hi";
	base* c = new Shell(test_val[1]);
        EXPECT_EQ(true, c->execute());
}

TEST(SMCL_Test, SMCL_test_two)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "ls ; echo command_two";
	base* c = new Shell(test_val[1]);
        EXPECT_EQ(true, c->execute());
}


TEST(CMENT_Test, CMENT_test)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echo command commit # This is a commit.";
	base* c = new Shell(test_val[1]);
        EXPECT_EQ(true, c->execute());
}

TEST(Exit_Test, Exit_test_one)
{
	pid_t pid;
        int status;
        pid = fork();
        if(pid == 0)
        {
        	char* test_val[3]; test_val[0] = "./test"; test_val[1] = "exit";
       	 	Shell* c = new Shell(test_val[1]);
		c->execute();
        }else{
		wait(&status);
                EXPECT_EQ(512,status);
	}
}


TEST(LongCommand_Test, Long_test_two)
{
	pid_t pid;
        int status;
        pid = fork();
        if(pid == 0)
        {
        	char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echo command one && echoe command two || echo command three ; echo ready exit && exit # commit is here";
        	Shell* c = new Shell(test_val[1]);
		c->execute();
	}else
	{
		wait(&status);
        	EXPECT_EQ(0, status);
	}
}

TEST(EXIT_vs_OR, EXIT_OR_ECHO)
{
	pid_t pid;
	int status;
	pid = fork();
	if(pid == 0)
	{
        	char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "exit|| echo not_exit_successfully";
        	Shell* c = new Shell(test_val[1]);
		c->execute();
	}else
	{
		wait(&status);
		EXPECT_LT(0,status);
	}
}

TEST(EXIT_vs_OR, EXIT_OR_EXIT)
{
	 pid_t pid;
        int status;
        pid = fork();
        if(pid == 0)
        {
        	char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "exit|| exit";
		Shell* c = new Shell(test_val[1]);
		c->execute();
	}else
	{
		wait(&status);
		EXPECT_LT(0,status);
	}
}

TEST(EXIT_vs_ECHO, EXIT_IN_ECHO)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echo exit";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}

TEST(TEST_TEST, SINGLE_DIR_without_flag)
{
        char* test_val[3]; test_val[0] = "./rshell";
	test_val[1] = "test src";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}

TEST(TEST_TEST, SINGLE_DIR_with_flag_e)
{
	char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "test -e src";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}
TEST(TEST_TEST, SINGLE_DIR_with_flag_d)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "test -d src";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}
TEST(TEST_TEST, SINGLE_DIR_with_flag_f)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "test -f src";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(false,c->execute());
}
TEST(TEST_TEST, SINGLE_FILE_without_flag)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "test CMakeLists.txt";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}
TEST(TEST_TEST, SINGLE_FILE_with_flag_e)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "test -e CMakeLists.txt";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}
TEST(TEST_TEST, SINGLE_FILE_with_flag_f)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "test -f CMakeLists.txt ";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}
TEST(TEST_TEST, SINGLE_FILE_with_flag_d)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "test -d CMakeLists.txt";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(false,c->execute());
}
TEST(TEST_TEST, symbolic_with_flag)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "[ -d CMakeLists.txt ]";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(false,c->execute());
}
TEST(TEST_TEST, symbolic_without_flag)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "[ CMakeLists.txt ]";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}
TEST(TEST_TEST, test_combo)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "[ CMakeLists.txt ] && test -d tests ; (test -e googletest && test -f src/shell.h) ||exit";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}
TEST(TEST_TEST, test_syscall_combo)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "[ CMakeLists.txt ] && (test -d tests ; echo syscall_echo && test -f src/shell.h) ||exit";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}
TEST(WRONG_COMMAND, test_combo)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "[ CMaaaa ] && test -d tests ; (test -e google && test -f src/shell.h)";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(false,c->execute());
}
TEST(WRONG_COMMAND, WRONG_AND_FIRST)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echoe hi && echo nihao";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(false,c->execute());
}

TEST(WRONG_COMMAND, WRONG_AND_SECOND)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "echo hi && echo2 nihao";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(false,c->execute());
}
TEST(WRONG_COMMAND, WRONG_OR)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "echoe hi || echo nihao";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}

TEST(WRONG_COMMAND, WRONG_SMCL)
{
        char* test_val[3]; test_val[0] = "./rshell"; test_val[1] = "echoe hi ; echo hi";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(true,c->execute());
}

TEST(WRONG_COMMAND, WRONG_SMCL_SECOND)
{
        char* test_val[3]; test_val[0] = "./rshell";
        test_val[1] = "echo hi ; echoe hi";
        Shell* c = new Shell(test_val[1]);
        EXPECT_EQ(false,c->execute());
}
