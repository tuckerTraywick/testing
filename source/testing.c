#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "testing.h"

extern FILE *output;
extern TestResults *results;

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
		fprintf(output, "[%s] Test failed with signal %s and status %d.\n\n", name, strsignal(WTERMSIG(status)), WEXITSTATUS(status));
		return;
	}

	if (results->assertionsFailed > failed) {
		++results->testsFailed;
		fprintf(output, "[%s] Test failed.\n\n", name);
	} else {
		++results->testsPassed;
	}
}

void assertImpl(bool success, char *testName, char *fileName, unsigned int lineNumber, char *condition) {
	++results->assertionsRun;
	if (success) {
		++results->assertionsPassed;
		return;
	}
	++results->assertionsFailed;
	fprintf(output, "[%s:%s:%u] Assertion failed: `%s`.\n", testName, fileName, lineNumber, condition);
}
