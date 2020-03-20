#include "gtest/gtest.h"

#include "info_test.h"
#include "help_test.h"
#include "testcmd_test.h"



int main(int argc, char **argv) {
  //I cannot test bashcmd.cpp becuase execvp
  //calls exit with also exits gtest
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
