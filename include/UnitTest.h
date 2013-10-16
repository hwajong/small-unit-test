/*
 * unittest.h
 *
 *  Created on: 2009. 9. 3.
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_

#ifndef NDEBUG

#include <stdio.h>
#include <stdbool.h>   // for bool
#include <sys/types.h> // for uint

//------------------------------------------------------------------------------------------------//
// Assertion Prefix Rule
//    ASSERT_ => Fatal assertion
//    EXPECT_ => Nonfatal assertion
//------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
// Fatal assertion
//------------------------------------------------------------------------------------------------//
#define ASSERT_TRUE(value) \
  {  AssertImplementation(value, __FILE__, __func__, __LINE__, ("ASSERT_TRUE(" #value ")"), true); }

#define ASSERT_FALSE(value) \
  {  AssertImplementation(!(value), __FILE__, __func__, __LINE__, ("ASSERT_FALSE(" #value ")"), true); }
// Equal
#define ASSERT_EQ(actual, expected) \
  {  AssertImplementation(((actual) == (expected)), __FILE__, __func__, __LINE__, ("ASSERT_EQ(" #actual "," #expected ")"), true); }
// Not Equal
#define ASSERT_NE(actual, expected) \
  {  AssertImplementation(((actual) != (expected)), __FILE__, __func__, __LINE__, ("ASSERT_NE(" #actual "," #expected ")"), true); }
// Pointer Equal
#define ASSERT_PTREQ(actual, expected) \
  {  AssertImplementation(((void*)(actual) == (void*)(expected)), __FILE__, __func__, __LINE__, ("ASSERT_PTREQ(" #actual "," #expected ")"), true); }
// String Equal
#define ASSERT_STREQ(actual, expected) \
  {  AssertImplementation(!(strcmp((const char*)(actual), (const char*)(expected))), __FILE__, __func__, __LINE__, ("ASSERT_STREQ(" #actual "," #expected ")"), true); }
// String Not Equal
#define ASSERT_STRNE(actual, expected) \
  {  AssertImplementation((strcmp((const char*)(actual), (const char*)(expected))), __FILE__, __func__, __LINE__, ("ASSERT_STRNE(" #actual "," #expected ")"), true); }
// Not Null terminated String Equal
#define ASSERT_NSTREQ(actual, expected, count) \
  {  AssertImplementation(!(strncmp((const char*)(actual), (const char*)(expected), (size_t)count)), __FILE__, __func__, __LINE__, ("ASSERT_NSTREQ(" #actual "," #expected "," #count ")"), true); }
// Not Null terminated String Not Equal
#define ASSERT_NSTRNE(actual, expected, count) \
  {  AssertImplementation((strncmp((const char*)(actual), (const char*)(expected), (size_t)count)), __FILE__, __func__, __LINE__, ("ASSERT_NSTRNE(" #actual "," #expected "," #count ")"), true); }

//------------------------------------------------------------------------------------------------//
// Nonfatal assertion
//------------------------------------------------------------------------------------------------//
#define EXPECT_TRUE(value) \
  {  AssertImplementation(value, __FILE__, __func__, __LINE__, ("EXPECT_TRUE(" #value ")"), false); }

#define EXPECT_FALSE(value) \
  {  AssertImplementation(!(value), __FILE__, __func__, __LINE__, ("EXPECT_FALSE(" #value ")"), false); }
// Equal
#define EXPECT_EQ(actual, expected) \
  {  AssertImplementation(((actual) == (expected)), __FILE__, __func__, __LINE__, ("EXPECT_EQ(" #actual "," #expected ")"), false); }
// Not Equal
#define EXPECT_NE(actual, expected) \
  {  AssertImplementation(((actual) != (expected)), __FILE__, __func__, __LINE__, ("EXPECT_NE(" #actual "," #expected ")"), false); }
// Pointer Equal
#define EXPECT_PTREQ(actual, expected) \
  {  AssertImplementation(((void*)(actual) == (void*)(expected)), __FILE__, __func__, __LINE__, ("EXPECT_PTREQ(" #actual "," #expected ")"), false); }
// String Equal
#define EXPECT_STREQ(actual, expected) \
  {  AssertImplementation(!(strcmp((const char*)(actual), (const char*)(expected))), __FILE__, __func__, __LINE__, ("EXPECT_STREQ(" #actual "," #expected ")"), false); }
// String Not Equal
#define EXPECT_STRNE(actual, expected) \
  {  AssertImplementation((strcmp((const char*)(actual), (const char*)(expected))), __FILE__, __func__, __LINE__, ("EXPECT_STRNE(" #actual "," #expected ")"), false); }
// Not Null terminated String Equal
#define EXPECT_NSTREQ(actual, expected, count) \
  {  AssertImplementation(!(strncmp((const char*)(actual), (const char*)(expected), (size_t)count)), __FILE__, __func__, __LINE__, ("EXPECT_NSTREQ(" #actual "," #expected "," #count ")"), false); }
// Not Null terminated String Not Equal
#define EXPECT_NSTRNE(actual, expected, count) \
  {  AssertImplementation((strncmp((const char*)(actual), (const char*)(expected), (size_t)count)), __FILE__, __func__, __LINE__, ("EXPECT_NSTRNE(" #actual "," #expected "," #count ")"), false); }

#define ADD_TESTSUITE(func) \
  { \
    extern void func(); \
    AddTestSuite(func); \
  }

// user must implement this function.
extern void TestSuites();

extern void AddTestCase(void(*func)(void));

// Use ADD_TESTSUITE mecro for convenience
extern void AddTestSuite(void(*func)(void));

extern void AssertImplementation(bool value, const char fileName[], const char funcName[], uint lineNo, const char expression[], bool isFatal);

extern bool RunUnitTest();

#endif

#endif /* UNITTEST_H_ */
