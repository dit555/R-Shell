#ifndef TEST_CMD_TEST
#define TEST_CMD_TEST

#include "gtest/gtest.h"
#include "../src/testcmd.cpp"

#include <string>

using std::string;

TEST(TestCmdTest, TestEvaluate){
	TestCmd a;
	
	char* argv1[] = {"test", "src/" };
	char* argv2[] = {"test" , "src/parser.cpp"};
	char* argv3[] = {"test" , "-e", "src/"};
	char* argv4[] = {"test" , "-e", "src/parser.cpp"};
	char* argv5[] = {"test" , "-d", "src/"};
	char* argv6[] = {"test" , "-d", "src/parser.cpp"};
	char* argv7[] = {"test" , "-f", "src/"};
	char* argv8[] = {"test" , "-f", "src/parser.cpp"};

	int argc = 2;
	
	testing::internal::CaptureStdout();
	a.execute(argc, argv1, true);
	string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "(True)");

	testing::internal::CaptureStdout();
        a.execute(argc, argv2, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(True)");

	argc = 3;
	testing::internal::CaptureStdout();
	a.execute(argc, argv3, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(True)");
	
	testing::internal::CaptureStdout();	
	a.execute(argc, argv4, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(True)");

	testing::internal::CaptureStdout();
	a.execute(argc, argv5, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(True)");

	testing::internal::CaptureStdout();
	a.execute(argc, argv6, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(False)");

	testing::internal::CaptureStdout();
	a.execute(argc, argv7, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(False)");

	testing::internal::CaptureStdout();
	a.execute(argc, argv8, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(True)");
	

}
	
TEST(TestCmdTest, BraketEvaluate){
	TestCmd a;
	
	char* argv1[] = {"[", "src/", "]" };
	char* argv2[] = {"[" , "src/parser.cpp", "]"};
	char* argv3[] = {"[" , "-e", "src/", "]"};
	char* argv4[] = {"[" , "-e", "src/parser.cpp", "]"};
	char* argv5[] = {"[" , "-d", "src/", "]"};
	char* argv6[] = {"[" , "-d", "src/parser.cpp", "]"};
	char* argv7[] = {"[" , "-f", "src/", "]"};
	char* argv8[] = {"[" , "-f", "src/parser.cpp", "]"};

	int argc = 3;
	
	testing::internal::CaptureStdout();
	a.execute(argc, argv1, true);
	string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "(True)");

	testing::internal::CaptureStdout();
        a.execute(argc, argv2, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(True)");

	argc = 4;
	testing::internal::CaptureStdout();
	a.execute(argc, argv3, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(True)");
	
	testing::internal::CaptureStdout();	
	a.execute(argc, argv4, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(True)");

	testing::internal::CaptureStdout();
	a.execute(argc, argv5, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(True)");

	testing::internal::CaptureStdout();
	a.execute(argc, argv6, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(False)");

	testing::internal::CaptureStdout();
	a.execute(argc, argv7, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(False)");

	testing::internal::CaptureStdout();
	a.execute(argc, argv8, true);
        output = testing::internal::GetCapturedStdout();

        EXPECT_EQ(output, "(True)");
	

	




}


#endif
