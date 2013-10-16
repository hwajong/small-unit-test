/*
 * unittest.c
 *
 *  Created on: 2009. 9. 3.
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <setjmp.h>

#include "UnitTest.h"

#ifndef NDEBUG

typedef struct FailureRecord
{
	  uint  lineNo;
	  char* fileName;
	  char* funcName;
	  char* expression;

	  struct FailureRecord* pNext; // Failure Details List;
} FailureRecord;

typedef struct
{
	uint nSuites;
	uint nTests;
	uint nAsserts;

	uint nSuitesFailed;
	uint nTestsFailed;
	uint nAssertsFailed;

	FailureRecord* pFailureList;
} UnitTestSummary;

static UnitTestSummary UtSummary;
static jmp_buf FatalExit;
static bool IsAssertFailed;
static bool IsTestFailed;

static void InitUnitTestKit(UnitTestSummary* p)
{
	p->nTests = 0;
	p->nTestsFailed = 0;
	p->nAsserts = 0;
	p->nAssertsFailed = 0;
	p->pFailureList = NULL;
}

static void AddFailureToList(FailureRecord** list,
		                     const char fileName[],
		                     const char funcName[],
		                     uint lineNo,
		                     const char expression[])
{
	FailureRecord* pNewNode = malloc(sizeof(FailureRecord));
	pNewNode->lineNo = lineNo;
	pNewNode->fileName = strdup(fileName);
	pNewNode->funcName = strdup(funcName);
	pNewNode->expression = strdup(expression);
	pNewNode->pNext = NULL;

	FailureRecord** pLast = list;
	while(*pLast != NULL)
		pLast = &((*pLast)->pNext);

	*pLast = pNewNode;
}

static void CleanupUnitTestKit(UnitTestSummary* p)
{
	FailureRecord* pCur = p->pFailureList;

	while(pCur != NULL){
		FailureRecord* pNext = pCur->pNext;
		free(pCur->fileName);
		free(pCur->funcName);
		free(pCur->expression);
		free(pCur);
		pCur = pNext;
	}
}

static void PrintTestSummary(const UnitTestSummary* p)
{
	FailureRecord* pCur = p->pFailureList;
	char strResult[10];
	if(p->nAssertsFailed > 0)
		strcpy(strResult, "FAILED");
	else
		strcpy(strResult, "PASSED");

	fprintf(stdout, "---------------------------------\n");
	fprintf(stdout, "- Unit Test Summary             -\n");
	fprintf(stdout, "---------------------------------\n");
	fprintf(stdout, "- nSuite         : %-4d         -\n", p->nSuites);
	fprintf(stdout, "- nSuiteFailed   : %-4d         -\n", p->nSuitesFailed);
	fprintf(stdout, "---------------------------------\n");
	fprintf(stdout, "- nTests         : %-4d         -\n", p->nTests);
	fprintf(stdout, "- nTestsFailed   : %-4d         -\n", p->nTestsFailed);
	fprintf(stdout, "---------------------------------\n");
	fprintf(stdout, "- nAsserts       : %-4d         -\n", p->nAsserts);
	fprintf(stdout, "- nAssertsFailed : %-4d         -\n", p->nAssertsFailed);
	fprintf(stdout, "---------------------------------\n");
	fprintf(stdout, "- Result         : %s       -\n" , strResult);
	fprintf(stdout, "---------------------------------\n");

	if(p->nAssertsFailed > 0){
		fprintf(stdout, "- Failure Details\n");
		while(pCur != NULL){
			fprintf(stdout, "  [%s, %s(), %d line] %s Failed!\n",
					        pCur->fileName,
					        pCur->funcName,
					        pCur->lineNo,
					        pCur->expression);

			pCur = pCur->pNext;
		}
	}
}

void AssertImplementation(bool value,
		                  const char fileName[],
		                  const char funcName[],
		                  uint lineNo,
		                  const char expression[],
		                  bool isFatal)
{
	UtSummary.nAsserts++;

	if(!value){
		UtSummary.nAssertsFailed++;
		IsAssertFailed = true;
		AddFailureToList(&UtSummary.pFailureList, fileName, funcName, lineNo, expression);

		if(isFatal)
			longjmp(FatalExit, 1);
	}
}

// -----------------------------------------------------------------------------------------------//
// UNIT TEST MAIN
// This function should be called in main() function.
// -----------------------------------------------------------------------------------------------//
bool RunUnitTest()
{
	InitUnitTestKit(&UtSummary);

	if(!setjmp(FatalExit)){
		TestSuites();
	}
	else{
		UtSummary.nTestsFailed++;
		fprintf(stdout, "*Fatal Assertion Failed!\n");
		PrintTestSummary(&UtSummary);
		CleanupUnitTestKit(&UtSummary);

		return false;
	}

	PrintTestSummary(&UtSummary);
	CleanupUnitTestKit(&UtSummary);

	return true;
}

void AddTestCase(void(*func)(void))
{
	IsAssertFailed = false;
	UtSummary.nTests++;
	func();
	if(IsAssertFailed) {
		UtSummary.nTestsFailed++;
		IsTestFailed = true;
	}
}

void AddTestSuite(void(*func)(void))
{
	IsTestFailed = false;
    UtSummary.nSuites++;
    func();
    if(IsTestFailed)
    	UtSummary.nSuitesFailed++;
}
#endif
