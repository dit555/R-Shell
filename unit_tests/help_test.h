#ifndef _HELP_TEST_HPP_
#define _HELP_TEST_HPP_

#include "gtest/gtest.h"
#include "../src/help.cpp"

#include <string>

using std::string;

TEST(HelpTest, HelpEvaluate){
	Help a;
	
	char* argv[] = {"help"};
	int argc = 1;
	
	testing::internal::CaptureStdout();
	a.execute(argc, argv, true);
	string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "poop");

}



#endif
