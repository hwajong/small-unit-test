/*
 * usercode.c
 *
 *  Created on: 2009. 9. 3.
 */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "UnitTest.h"

int natoi(const char *s, size_t len)
{
    long n;
    char *temp = malloc(len + 1);

    assert(s != NULL);

    memcpy(temp, s, len);
    temp[len] = 0;
    n = atoi(temp);

    free(temp);
    return n;
}

static time_t dtime2caltime(const char *p)
{
	struct tm bdt;

	bdt.tm_year = natoi(p   , 4) - 1900;
	bdt.tm_mon  = natoi(p+4 , 2) -1;
	bdt.tm_mday = natoi(p+6 , 2);
	bdt.tm_hour = 0;
	bdt.tm_min  = 0;
	bdt.tm_sec  = 0;
	bdt.tm_isdst = 0;

	return mktime(&bdt);
}

// calculate inYYYYMMDD - 1
char* GetYesterDay(const char* inYYYYMMDD, char* outYYYYMMDD)
{
    struct tm bdt;                              // break down time
    time_t caltime = dtime2caltime(inYYYYMMDD); // calendar time

    if(caltime == (time_t)-1){
    	sprintf(outYYYYMMDD, "00000000");
    }else{
        caltime -= (60 * 60 * 24);              // a day in seconds
        localtime_r(&caltime, &bdt);

        sprintf(outYYYYMMDD, "%04d%02d%02d",
        		             bdt.tm_year + 1900,
        		             bdt.tm_mon + 1,
        		             bdt.tm_mday);
    }

    return outYYYYMMDD;
}

int Minus(int a, int b)
{
	return a - b;
}
//------------------------------------------------------------------------------------------------//
// Unit Test
//------------------------------------------------------------------------------------------------//

#ifndef NDEBUG
static void TestCase_GetYesterDay()
{
	char yesterday[9] = {0,};
	EXPECT_STREQ(GetYesterDay("20091011", yesterday), "20091010");
	EXPECT_STREQ(GetYesterDay("20091231", yesterday), "20091230");
	EXPECT_STREQ(GetYesterDay("20090101", yesterday), "20081231");
	EXPECT_STREQ(GetYesterDay("20100101", yesterday), "20091230");
	EXPECT_STREQ(GetYesterDay("00000000", yesterday), "00000000");
	EXPECT_STREQ(GetYesterDay("99999999", yesterday), "00000000");
}

static void TestCase_Minus()
{
	EXPECT_EQ(Minus(5,3), 2);
}

void TestSuite_DateTime()
{
	AddTestCase(TestCase_GetYesterDay);
	AddTestCase(TestCase_Minus);
}
#endif

