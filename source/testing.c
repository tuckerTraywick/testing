#include <stdbool.h>
#include <stdio.h>
#include "testing.h"

extern FILE *output;

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
	fprintf(output, "---- TEST SUMMARY ----\n");
	fprintf(output, "%u tests run.\n%u tests passed.\n%u tests failed.\n", testsRun, testsPassed, testsFailed);
}

void runTestImpl(TestCase test, char *name) {
	unsigned int failed = assertionsFailed;
	test();
	++testsRun;
	if (assertionsFailed > failed) {
		fprintf(output, "[%s] Test failed.\n\n", name);
		++testsFailed;
	} else {
		++testsPassed;
	}
}

void assertImpl(bool success, char *testName, char *fileName, unsigned int lineNumber, char *condition) {
	++assertionsRun;
	if (success) {
		++assertionsPassed;
		return;
	}
	++assertionsFailed;
	fprintf(output, "[%s:%s:%u] Assertion failed: `%s`.\n", testName, fileName, lineNumber, condition);
}
