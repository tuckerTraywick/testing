#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "testing.h"
#include "logging.h"

// Contains all of the numbers that tests keep track of.
typedef struct TestResults {
	unsigned int testsRun;
	unsigned int testsPassed;
	unsigned int testsFailed;
	unsigned int assertionsRun;
	unsigned int assertionsPassed;
	unsigned int assertionsFailed;
} TestResults;

// Used to share test results with child processes.
static TestResults *results;

void beginTesting(void) {
	results = mmap(NULL, sizeof *results, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (results == MAP_FAILED) {
		logError("Couldn't obtain shared memory, can't run tests. Aborting.\n");
		exit(1);
	}
}

void endTesting(void) {
	logInfo("");
	putsInfo("---- TEST SUMMARY ----\n");
	printfInfo("%u tests run.\n%u tests passed.\n%u tests failed.\n", results->testsRun, results->testsPassed, results->testsFailed);
	munmap(results, sizeof *results);
}

void runTestImpl(TestCase test, char *name) {
	unsigned int failed = results->assertionsFailed;
	
	pid_t pid = fork();
	if (pid < 0) {
		// The process failed to fork.
		logfError("Failed to fork in test '%s', aborting.\n", name);
		return;
	} else if (pid == 0) {
		// Run the test in the child process.
		test();
		exit(0);
	}
	
	++results->testsRun;
	int status = 0;
	// Wait on the child to end and determine if it failed from a signal.
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status)) {
		++results->testsFailed;
		printfError(ERROR_PREFIX "[%s] Test failed with signal '%s' and status %d.\n\n", name, strsignal(WTERMSIG(status)), WEXITSTATUS(status));
		return;
	}

	if (results->assertionsFailed > failed) {
		++results->testsFailed;
		printfError(ERROR_PREFIX "[%s] Test failed.\n\n", name);
	} else {
		++results->testsPassed;
	}
}

static bool updateAssertionResults(bool success) {
	++results->assertionsRun;
	if (success) {
		++results->assertionsPassed;
		return true;
	}
	++results->assertionsFailed;
	return false;
}

void testAssertImpl(bool success, char *testName, char *fileName, unsigned int lineNumber, char *expression) {
	if (!updateAssertionResults(success)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: '%s'.\n", fileName, lineNumber, testName, expression);}
}

void testAssertEqIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a == b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s == %s (%s = %ld, %s = %ld).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertNeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a != b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s != %s (%s = %ld, %s = %ld).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertGtIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a > b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s > %s (%s = %ld, %s = %ld).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertLtIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a < b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s < %s (%s = %ld, %s = %ld).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertGeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a >= b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s >= %s (%s = %ld, %s = %ld).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertLeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a <= b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s <= %s (%s = %ld, %s = %ld).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertEqUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a == b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s == %s (%s = %lu, %s = %lu).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertNeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a != b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s != %s (%s = %lu, %s = %lu).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertGtUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a > b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s > %s (%s = %lu, %s = %lu).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertLtUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a < b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s < %s (%s = %lu, %s = %lu).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertGeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a >= b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s >= %s (%s = %lu, %s = %lu).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertLeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a <= b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s <= %s (%s = %lu, %s = %lu).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertEqFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a == b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s == %s (%s = %f, %s = %f).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertNeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a != b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s != %s (%s = %f, %s = %f).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertGtFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a > b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s > %s (%s = %f, %s = %f).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertLtFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a < b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s < %s (%s = %f, %s = %f).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertGeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a >= b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s >= %s (%s = %f, %s = %f).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertLeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a <= b)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: %s <= %s (%s = %f, %s = %f).\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertEqStringImpl(char *a, char *b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(strcmp(a, b) == 0)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: strcmp(%s, %s) == 0 (%s = \"%s\", %s = \"%s\").\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertNeStringImpl(char *a, char *b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(strcmp(a, b) != 0)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: strcmp(%s, %s) != 0 (%s = \"%s\", %s = \"%s\").\n", fileName, lineNumber, testName, expressionA, expressionB, expressionA, a, expressionB, b);}
}

void testAssertEqNStringImpl(char *a, char *b, size_t n, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(strncmp(a, b, n) == 0)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: strcmp(%s, %s, %zu) == 0 (%s = \"%.*s\", %s = \"%.*s\").\n", fileName, lineNumber, testName, expressionA, expressionB, n, expressionA, (int)n, a, expressionB, (int)n, b);}
}

void testAssertNeNStringImpl(char *a, char *b, size_t n, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(strncmp(a, b, n) != 0)) {printfError(ERROR_PREFIX LOG_FORMAT "Assertion failed: strcmp(%s, %s, %zu) != 0 (%s = \"%.*s\", %s = \"%.*s\").\n", fileName, lineNumber, testName, expressionA, expressionB, n, expressionA, (int)n, a, expressionB, (int)n, b);}
}
