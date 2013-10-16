/*
 * CommLib.c
 *
 *  Created on: 2009. 9. 4.
 */
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "UnitTest.h"

bool IsNegative(int a)
{
	return a < 0;
}

int Sum(int a, int b)
{
	return a + b;
}

char* ToUpperString(char *s)
{
	assert(s != NULL);

	unsigned int i;
	for(i=0; i<strlen(s); i++)
		s[i] = toupper(s[i]);

	return s;
}

//------------------------------------------------------------------------------------------------//
// Unit Test
//------------------------------------------------------------------------------------------------//
#ifndef NDEBUG
static void TestCase_IsNegative()
{
	ASSERT_TRUE(IsNegative(-10));
	ASSERT_FALSE(IsNegative(0));
	ASSERT_FALSE(IsNegative(999));
}

static void TestCase_Sum()
{
	EXPECT_EQ(Sum(3,5), 8);
	EXPECT_EQ(Sum(-100,3), -97);
	EXPECT_EQ(Sum(-300,-900), -1200);
	EXPECT_EQ(Sum(0,0), 0);
	EXPECT_EQ(Sum(5,0), Sum(0,5));
	EXPECT_NE(Sum(-100,100), Sum(100,100));
}

static void TestCase_ToUpperString()
{
	char str[] = "Visual C++";
	EXPECT_STRNE(str, "VISUAL C++");
	ASSERT_STREQ(ToUpperString(str), "VISUAL C++");
}

static void TestCase_NotNullString()
{
	char str[100];
	memset(str, 0xff, sizeof(str));
	memcpy(str, "Linux", 5);
	EXPECT_NSTREQ(str, "Linux", 5);
	EXPECT_NSTRNE(str, "Linux", 6);
}

void TestSuite_CommLib()
{
	AddTestCase(TestCase_IsNegative);
	AddTestCase(TestCase_Sum);
	AddTestCase(TestCase_ToUpperString);
	AddTestCase(TestCase_NotNullString);
}
#endif
