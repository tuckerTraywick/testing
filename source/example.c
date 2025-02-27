#include <stdio.h>
#include "logging.h"
#include "testing.h"

static void pass(void) {
	testAssert(1 < 2);
}

static void segfault(void) {
	*(char*)123 = 1;
}

static void fail(void) {
	int a = 1;
	testAssertEqInt(a + 1, 2 + 3);
}

int main(void) {
	logInfoOutput = logErrorOutput = stdout;
	beginTesting();
		runTest(pass);
		runTest(segfault);
		runTest(fail);
	endTesting();
	return 0;
}
