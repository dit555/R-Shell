#ifndef _INFO_TEST_HPP_
#define _INFO_TEST_HPP_

#include "gtest/gtest.h"
#include "../src/info.cpp"

#include <string.h>

using std::string;

TEST(InfoTest, InfoEvaluate){
	Info a;
	
	char* argv[] = {"info"};
	int argc = 1;
	
	testing::internal::CaptureStdout();
	a.execute(argc, argv, true);
	string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "poop");
}



#endif
