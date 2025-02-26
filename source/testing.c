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

// Contains all of the numbers that tests keep track of.
typedef struct TestResults {
	unsigned int testsRun;
	unsigned int testsPassed;
	unsigned int testsFailed;
	unsigned int assertionsRun;
	unsigned int assertionsPassed;
	unsigned int assertionsFailed;
} TestResults;

extern FILE *output;
// Used to share test results with child processes.
static TestResults *results;

void beginTesting(void) {
	results = mmap(NULL, sizeof *results, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (results == MAP_FAILED) {
		fprintf(output, "Couldn't obtain shared memory, can't run tests. Aborting.\n");
		exit(1);
	}
}

void endTesting(void) {
	fprintf(output, "---- TEST SUMMARY ----\n");
	fprintf(output, "%u tests run.\n%u tests passed.\n%u tests failed.\n", results->testsRun, results->testsPassed, results->testsFailed);
	munmap(results, sizeof *results);
}

void runTestImpl(TestCase test, char *name) {
	unsigned int failed = results->assertionsFailed;
	
	pid_t pid = fork();
	if (pid < 0) {
		// The process failed to fork.
		fprintf(output, "Failed to fork in test '%s', aborting.\n", name);
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
		fprintf(output, "[%s] Test failed with signal '%s' and status %d.\n\n", name, strsignal(WTERMSIG(status)), WEXITSTATUS(status));
		return;
	}

	if (results->assertionsFailed > failed) {
		++results->testsFailed;
		fprintf(output, "[%s] Test failed.\n\n", name);
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

void assertImpl(bool success, char *testName, char *fileName, unsigned int lineNumber, char *expression) {
	if (!updateAssertionResults(success)) fprintf(output, "[%s:%s:%u] Assertion failed: '%s'.\n", testName, fileName, lineNumber, expression);
}

void assertEqIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a == b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s == %s (%s = %lld, %s = %lld).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertNeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a != b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s != %s (%s = %lld, %s = %lld).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertGtIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a > b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s > %s (%s = %lld, %s = %lld).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertLtIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a < b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s < %s (%s = %lld, %s = %lld).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertGeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a >= b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s >= %s (%s = %lld, %s = %lld).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertLeIntImpl(int64_t a, int64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a <= b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s <= %s (%s = %lld, %s = %lld).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertEqUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a == b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s == %s (%s = %llu, %s = %llu).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertNeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a != b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s != %s (%s = %llu, %s = %llu).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertGtUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a > b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s > %s (%s = %llu, %s = %llu).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertLtUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a < b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s < %s (%s = %llu, %s = %llu).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertGeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a >= b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s >= %s (%s = %llu, %s = %llu).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertLeUIntImpl(uint64_t a, uint64_t b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a <= b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s <= %s (%s = %llu, %s = %llu).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertEqFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a == b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s == %s (%s = %f, %s = %f).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertNeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a != b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s != %s (%s = %f, %s = %f).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertGtFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a > b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s > %s (%s = %f, %s = %f).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertLtFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a < b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s < %s (%s = %f, %s = %f).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertGeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a >= b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s >= %s (%s = %f, %s = %f).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertLeFloatImpl(double a, double b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(a <= b)) fprintf(output, "[%s:%s:%u] Assertion failed: %s <= %s (%s = %f, %s = %f).\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertEqStringImpl(char *a, char *b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(strcmp(a, b) == 0)) fprintf(output, "[%s:%s:%u] Assertion failed: strcmp(%s, %s) == 0 (%s = \"%s\", %s = \"%s\").\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertNeStringImpl(char *a, char *b, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(strcmp(a, b) != 0)) fprintf(output, "[%s:%s:%u] Assertion failed: strcmp(%s, %s) != 0 (%s = \"%s\", %s = \"%s\").\n", testName, fileName, lineNumber, expressionA, expressionB, expressionA, a, expressionB, b);
}

void assertEqNStringImpl(char *a, char *b, size_t n, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(strncmp(a, b, n) == 0)) fprintf(output, "[%s:%s:%u] Assertion failed: strcmp(%s, %s, %zu) == 0 (%s = \"%.*s\", %s = \"%.*s\").\n", testName, fileName, lineNumber, expressionA, expressionB, n, expressionA, (int)n, a, expressionB, (int)n, b);
}

void assertNeNStringImpl(char *a, char *b, size_t n, char *testName, char *fileName, unsigned int lineNumber, char *expressionA, char *expressionB) {
	if (!updateAssertionResults(strncmp(a, b, n) != 0)) fprintf(output, "[%s:%s:%u] Assertion failed: strcmp(%s, %s, %zu) != 0 (%s = \"%.*s\", %s = \"%.*s\").\n", testName, fileName, lineNumber, expressionA, expressionB, n, expressionA, (int)n, a, expressionB, (int)n, b);
}
