// Example Code

#include <assert.h>

#include "UnitTest.h"

//------------------------------------------------------------------------------------------------//
// App main
//------------------------------------------------------------------------------------------------//
int main()
{
	// Initial code .....
	assert(RunUnitTest());

	// App code ...

	return 0;
}

//------------------------------------------------------------------------------------------------//
// Unit Test
//------------------------------------------------------------------------------------------------//
#ifndef NDEBUG
// must add testsuite using ADD_TESTSUITE macro.
void TestSuites()
{
	ADD_TESTSUITE(TestSuite_CommLib);
	ADD_TESTSUITE(TestSuite_DateTime);
}
#endif
