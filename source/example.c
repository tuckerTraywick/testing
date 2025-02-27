#include "testing.h"

static void pass(void) {
	assert(1 < 2);
}

static void segfault(void) {
	*(char*)123 = 1;
}

static void fail(void) {
	int a = 1;
	assertEqInt(a + 1, 2 + 3);
}

int main(void) {
	testOutput = stdout;
	beginTesting();
		runTest(pass);
		runTest(segfault);
		runTest(fail);
	endTesting();
	return 0;
}
