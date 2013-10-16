small-unit-test
===============
This library is a unit test toolkit for C language.

I made this for coding simplest unit testcase. 

Example source codes are included.


* Assert Macros (see UnitTest.h for details...)
--------------------------------------------------------------------------------
Fatal assertion                          Nonfatal assertion             
--------------------------------------------------------------------------------
ASSERT_TRUE(condition);                  EXPECT_TRUE(condition);                 
ASSERT_FALSE(condition);                 EXPECT_FALSE(condition);                
ASSERT_EQ(actual, expected);             EXPECT_EQ(actual, expected);            
ASSERT_NE(actual, expected);             EXPECT_NE(actual, expected);            
ASSERT_PTREQ(actual, expected);          EXPECT_PTREQ(actual, expected);         
ASSERT_STREQ(actual, expected);          EXPECT_STREQ(actual, expected);         
ASSERT_STRNE(actual, expected);          EXPECT_STRNE(actual, expected);           
ASSERT_NSTREQ(actual, expected, count);  EXPECT_NSTREQ(actual, expected, count); 
ASSERT_NSTRNE(actual, expected, count);  EXPECT_NSTRNE(actual, expected, count);
