small-unit-test
===============
This library is a unit test toolkit for C language.

I made this for coding simplest unit testcase. 

Example source codes are included.


* Assert Macros (see UnitTest.h for details...)
Fatal assertion                          Nonfatal assertion                        Verifies
--------------------------------------------------------------------------------------------------------------------------
ASSERT_TRUE(condition);                  EXPECT_TRUE(condition);                   condition is true
ASSERT_FALSE(condition);                 EXPECT_FALSE(condition);                  condition is false
ASSERT_EQ(actual, expected);             EXPECT_EQ(actual, expected);              actual == expected
ASSERT_NE(actual, expected);             EXPECT_NE(actual, expected);              actual != expected
ASSERT_PTREQ(actual, expected);          EXPECT_PTREQ(actual, expected);           pointer comparison 
ASSERT_STREQ(actual, expected);          EXPECT_STREQ(actual, expected);           C string comparison
ASSERT_STRNE(actual, expected);          EXPECT_STRNE(actual, expected);           
ASSERT_NSTREQ(actual, expected, count);  EXPECT_NSTREQ(actual, expected, count);   Not null terminated string comparison
ASSERT_NSTRNE(actual, expected, count);  EXPECT_NSTRNE(actual, expected, count);