#include <stddef.h>
#include <stdio.h>
#include "testing.h"

extern FILE *testOutput;
extern FILE *errorOutput;

extern unsigned int testsRun;
extern unsigned int testsPassed;
extern unsigned int testsFailed;
extern unsigned int assertionsRun;
extern unsigned int assertionsPassed;
extern unsigned int assertionsFailed;

void beginTesting(void) {
	testsRun = 0;
	testsPassed = 0;
	testsFailed = 0;
}

void endTesting(void) {
	fprintf(testOutput, "%u tests run.\n%u tests passed.\n%u tests failed.\n", testsRun, testsPassed, testsFailed);
}

void runTestImpl(TestCase test, char *name) {
	unsigned int failed = assertionsFailed;
	test();
	if (assertionsFailed > failed) {
		fprintf(errorOutput, "Test `%s` failed.\n", name);
		++testsFailed;
	} else {
		++testsPassed;
	}
	++testsRun;
}
