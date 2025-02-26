#ifndef TESTING_H
#define TESTING_H

#include <stdbool.h>
#include <stdio.h>

#define runTest(test) (runTestImpl((test), #test))

#define assert(condition) assertImpl((condition), (char*)__func__, __FILE__, __LINE__, #condition)

#define assertEq(a, b) assertEqImpl((a), (b), (char*)__func__, __FILE__, __LINE__, #a, #b)

typedef void (*TestCase)(void);

typedef struct TestResults {
	unsigned int testsRun;
	unsigned int testsPassed;
	unsigned int testsFailed;
	unsigned int assertionsRun;
	unsigned int assertionsPassed;
	unsigned int assertionsFailed;
} TestResults;

FILE *output;
TestResults *results;

void beginTesting(void);

void endTesting(void);

void runTestImpl(TestCase test, char *name);

void assertImpl(bool success, char *testName, char *fileName, unsigned int lineNumber, char *condition);

#endif // TESTING_H
