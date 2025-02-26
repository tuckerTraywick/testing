#include "testing.h"

void test1(void) {
	int a = -10;
	assertEqInt(a + 1, 3);
}

int main(void) {
	output = stdout;
	beginTesting();
		runTest(test1);
	endTesting();
	return 0;
}
